#include "GeneralInformationSubsystem.hpp"
#include "XML/XMLLoad.hpp"
#include "Aircraft.hpp"
#include "User.hpp"
#include "FileMetadata.hpp"
#include "Config.hpp"
#include "XML/XMLWriter.hpp"
#include "Validation.hpp"
#include "inc/XML_api.hpp"

#include <filesystem> // For `operations
namespace fs = std::filesystem;

GeneralInformationSubsystem::GeneralInformationSubsystem()
{
    m_Name = "General Information";
}

/////////
struct ReferencesColumns : public Gtk::TreeModel::ColumnRecord {
    Gtk::TreeModelColumn<int> id;
    Gtk::TreeModelColumn<std::string> refID;
    Gtk::TreeModelColumn<std::string> author;
    Gtk::TreeModelColumn<std::string> title;
    Gtk::TreeModelColumn<std::string> date;

    ReferencesColumns() {
        add(id);
        add(refID);
        add(author);
        add(title);
        add(date);
    }
};

 // Create an instance
////////

void GeneralInformationSubsystem::Create()
{
  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  // Row tracking variable
  int row = 0;

  // Extract file path from XMLDoc
  fs::path xmlFilePath = xmlptr()->GetFilePath();
  // Extract base path
  fs::path basePath = fs::current_path();
  // Get the direct file path by combining xmlFilePath and basePath
  fs::path fullPath = basePath / xmlFilePath;
  fullPath = fs::canonical(fullPath);


  // an example of accessing the xml file
  // fetch the ptr to the open xml document
  auto node = xmlptr()->GetNode("fdm_config");
  auto node_flightModel = xmlptr()->GetNode("/fdm_config/fileheader/version");
  auto node_author = xmlptr()->GetNode("/fdm_config/fileheader/author");
  auto node_fileDate = xmlptr()->GetNode("/fdm_config/fileheader/filecreationdate");


  // Aircraft Name
  auto aircraftNameLabel = Gtk::make_managed<Gtk::Label>("Aircraft Name");
  auto aircraftNameTextbox = Gtk::make_managed<Gtk::Entry>();
  aircraftNameTextbox->set_text( node.GetAttribute("name").second );

  // File Path
  auto filePathLabel = Gtk::make_managed<Gtk::Label>("File Path");
  if (!m_FilePath.empty()) {
    m_filePathTextbox.set_text(m_FilePath);
  } else {
    std::cerr << "Warning: m_FilePath is empty in Create()" << std::endl;
    m_filePathTextbox.set_text(fullPath.string());
  }

  // Release Level (Drop-down)
  auto releaseLevelLabel = Gtk::make_managed<Gtk::Label>("Release Level");
  auto releaseLevelDropdown = Gtk::make_managed<Gtk::ComboBoxText>();
  releaseLevelDropdown->append("ALPHA"); // load release levels
  releaseLevelDropdown->append("BETA");
  releaseLevelDropdown->set_active(0); // sets ALPHA default
  m_ReleaseLevelDropdown = releaseLevelDropdown; // Save reference for later

  // Configuration Version 
  auto configVersionLabel = Gtk::make_managed<Gtk::Label>("Configuration Version");
  auto configVersionTextbox = Gtk::make_managed<Gtk::Entry>();
  configVersionTextbox->set_text( node.GetAttribute("version").second ); // Load configuration version here

  // Flight Model Version
  auto flightModelVersionLabel = Gtk::make_managed<Gtk::Label>("Flight Model Version");
  auto flightModelVersionTextbox = Gtk::make_managed<Gtk::Entry>();
  flightModelVersionTextbox->set_text(node_flightModel.GetText()); // Load flight model version here

  // Author
  auto authorLabel = Gtk::make_managed<Gtk::Label>("Author");
  auto authorTextbox = Gtk::make_managed<Gtk::Entry>();
  authorTextbox->set_text( node_author.GetText() ); // Load author name here

  //Email
  auto emailLabel = Gtk::make_managed<Gtk::Label>("Email");
  auto emailTextbox = Gtk::make_managed<Gtk::Entry>();
  emailTextbox->set_text(""); // Load email here

  // Organization
  auto organizationLabel = Gtk::make_managed<Gtk::Label>("Organization");
  auto organizationTextView = Gtk::make_managed<Gtk::TextView>();
  auto organizationScrolledWindow = Gtk::make_managed<Gtk::ScrolledWindow>();
  auto organizationFrame = Gtk::make_managed<Gtk::Frame>();

  // Set up TextView content and appearance
  organizationTextView->get_buffer()->set_text("1.\n2.\n3."); // Placeholder text

  // Configure the ScrolledWindow
  organizationScrolledWindow->set_min_content_height(100); // Set the height for the text area
  organizationScrolledWindow->set_min_content_width(300);  // Set the width for the text area
  organizationScrolledWindow->set_child(*organizationTextView);
  organizationScrolledWindow->set_policy(Gtk::PolicyType::ALWAYS, Gtk::PolicyType::ALWAYS);

  // Add the ScrolledWindow to the Frame to give it a border
  organizationFrame->set_child(*organizationScrolledWindow);
  organizationFrame->set_margin_bottom(10);

  // Set TextView wrap mode
  organizationTextView->set_wrap_mode(Gtk::WrapMode::WORD);

  // Description
  auto descriptionLabel = Gtk::make_managed<Gtk::Label>("Description");
  auto descriptionTextView = Gtk::make_managed<Gtk::TextView>();
  auto descriptionScrolledWindow = Gtk::make_managed<Gtk::ScrolledWindow>();
  auto descriptionFrame = Gtk::make_managed<Gtk::Frame>();

  // Set up TextView content and appearance
  descriptionTextView->get_buffer()->set_text("1.\n2.\n3."); // Placeholder text

  // Configure the ScrolledWindow
  descriptionScrolledWindow->set_min_content_height(100); // Set the height for the text area
  descriptionScrolledWindow->set_min_content_width(300);  // Set the width for the text area
  descriptionScrolledWindow->set_child(*descriptionTextView);
  descriptionScrolledWindow->set_policy(Gtk::PolicyType::ALWAYS, Gtk::PolicyType::ALWAYS);

  // Add the ScrolledWindow to the Frame to give it a border
  descriptionFrame->set_child(*descriptionScrolledWindow);

  // Set TextView wrap mode
  descriptionTextView->set_wrap_mode(Gtk::WrapMode::WORD);

  // File Date
  auto fileDateLabel = Gtk::make_managed<Gtk::Label>("File Date");
  auto fileDateTextbox = Gtk::make_managed<Gtk::Entry>();
  fileDateTextbox->set_text( node_fileDate.GetText() ); // Load FileDate name here

// References
ReferencesColumns referencesColumns; //Initial reference Columns Object
auto referencesLabel = Gtk::make_managed<Gtk::Label>("References");
// Create ListStore and TreeView for references
auto referencesStore = Gtk::ListStore::create(referencesColumns); // Define this model
auto referencesTreeView = Gtk::make_managed<Gtk::TreeView>(referencesStore);

// Add columns to TreeView
referencesTreeView->append_column("", referencesColumns.id);
referencesTreeView->append_column("Ref ID.", referencesColumns.refID);
referencesTreeView->append_column("Author", referencesColumns.author);
referencesTreeView->append_column("Title", referencesColumns.title);
referencesTreeView->append_column("Date", referencesColumns.date);
// Create a scrolled window for the TreeView
auto referencesScrolledWindow = Gtk::make_managed<Gtk::ScrolledWindow>();
// Create a frame to hold the table (optional)
auto referencesFrame = Gtk::make_managed<Gtk::Frame>();

referencesScrolledWindow->set_min_content_height(100); // Set the height for the table
referencesScrolledWindow->set_min_content_width(300);  // Set the width for the table
referencesScrolledWindow->set_child(*referencesTreeView);
referencesScrolledWindow->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);

referencesFrame->set_child(*referencesScrolledWindow);

referencesTreeView->get_column(0)->set_fixed_width(50); // ID column
referencesTreeView->get_column(1)->set_fixed_width(150); // Ref ID column
referencesTreeView->get_column(2)->set_fixed_width(150); // Author column
referencesTreeView->get_column(3)->set_fixed_width(300); // Title column
referencesTreeView->get_column(4)->set_fixed_width(100); // Date column

// Get the parent node
auto parentNode = xmlptr()->GetNode("/fdm_config/fileheader");
// Get all child nodes
auto references = parentNode.GetChildren();

int i = 1; // Row ID
for (const auto& reference : references) {
    // Create a mutable copy of the reference node
    auto mutableReference = const_cast<JSBEdit::XMLNode&>(reference);

    if (mutableReference.GetName() == "reference") { // Check if the node is a <reference>
        auto tableRow = *(referencesStore->append());
        
        tableRow[referencesColumns.refID] = mutableReference.GetAttribute("refID").second;  // Extract ref ID
        tableRow[referencesColumns.author] = mutableReference.GetAttribute("author").second;  // Extract author
        tableRow[referencesColumns.title] = mutableReference.GetAttribute("title").second;  // Extract title
        tableRow[referencesColumns.date] = mutableReference.GetAttribute("date").second;  // Extract date

        tableRow[referencesColumns.id] = i++; // Increase index table by 1
    }
}

  // Limitations
  auto limitationsLabel = Gtk::make_managed<Gtk::Label>("Limitations");
  auto limitationsTextView = Gtk::make_managed<Gtk::TextView>();
  auto limitationsScrolledWindow = Gtk::make_managed<Gtk::ScrolledWindow>();
  auto limitationsFrame = Gtk::make_managed<Gtk::Frame>();

  // Set up TextView content and appearance for Limitations
  limitationsTextView->get_buffer()->set_text("1.\n2.\n3"); // Placeholder text
  
  // Configure the ScrolledWindow
  limitationsScrolledWindow->set_min_content_height(100); // Set the height for the text area
  limitationsScrolledWindow->set_min_content_width(300); // Set the height for the text area  
  limitationsScrolledWindow->set_child(*limitationsTextView);
  limitationsScrolledWindow->set_policy(Gtk::PolicyType::ALWAYS, Gtk::PolicyType::ALWAYS);

  // Add the ScrolledWindow to the Frame to give it a border
  limitationsFrame->set_child(*limitationsScrolledWindow);

  // Set TextView wrap mode
  limitationsTextView->set_wrap_mode(Gtk::WrapMode::WORD);

  // Notes
  auto notesLabel = Gtk::make_managed<Gtk::Label>("Notes");
  auto notesTextView = Gtk::make_managed<Gtk::TextView>();
  auto notesScrolledWindow = Gtk::make_managed<Gtk::ScrolledWindow>();
  auto notesFrame = Gtk::make_managed<Gtk::Frame>();

  // Set up TextView content and appearance for Notes
  notesTextView->get_buffer()->set_text("1.\n2.\n3"); // Placeholder text
  
  // Configure the ScrolledWindow
  notesScrolledWindow->set_min_content_height(100); // Set the height for the text area
  notesScrolledWindow->set_min_content_width(300); // Set the height for the text area  
  notesScrolledWindow->set_child(*notesTextView);
  notesScrolledWindow->set_policy(Gtk::PolicyType::ALWAYS, Gtk::PolicyType::ALWAYS);

  // Add the ScrolledWindow to the Frame to give it a border
  notesFrame->set_child(*notesScrolledWindow);

  // Set TextView wrap mode
  notesTextView->set_wrap_mode(Gtk::WrapMode::WORD);

  // Attach widgets to the grid
  m_Grid.attach(*aircraftNameLabel, 0, row);
  m_Grid.attach(*aircraftNameTextbox, 1, row, 2);
  m_Grid.attach(*filePathLabel, 3, row);
  m_Grid.attach(m_filePathTextbox, 4, row++, 40);

  m_Grid.attach(*releaseLevelLabel, 0, row);
  m_Grid.attach(*releaseLevelDropdown, 1, row, 1);
  m_Grid.attach(*configVersionLabel, 3, row);
  m_Grid.attach(*configVersionTextbox, 4, row);
  m_Grid.attach(*flightModelVersionLabel, 9, row);
  m_Grid.attach(*flightModelVersionTextbox, 10, row++, 20);
  
  m_Grid.attach(*authorLabel, 0, row);
  m_Grid.attach(*authorTextbox, 1, row, 3);
  m_Grid.attach(*emailLabel, 4, row, 1);
  m_Grid.attach(*emailTextbox, 5, row++, 39);

  m_Grid.attach(*organizationLabel, 0, row);
  m_Grid.attach(*organizationFrame, 1, row, 3, 1); // Spans multiple columns for the text area

  m_Grid.attach(*descriptionLabel, 4, row);
  m_Grid.attach(*descriptionFrame, 5, row++, 39, 2);

  m_Grid.attach(*fileDateLabel, 0, row);
  m_Grid.attach(*fileDateTextbox, 1, row, 3);

  auto spacer = Gtk::make_managed<Gtk::Label>();
  spacer->set_size_request(-1, 10);  // Set height to 10 pixels
  m_Grid.attach(*spacer, 0, row++);

//////////////

  // m_Grid.attach(*referencesLabel, 0, row);
  // m_Grid.attach(*referencesFrame, 1, row++, 43, 2);

  // Attach to grid
m_Grid.attach(*referencesLabel, 0, row);
m_Grid.attach(*referencesFrame, 1, row++, 43, 2);
  m_Grid.attach(*spacer, 0, row++);

/////////////

  m_Grid.attach(*limitationsLabel, 0, row);
  m_Grid.attach(*limitationsFrame, 1, row++, 43, 2);
  m_Grid.attach(*spacer, 0, row++);

  m_Grid.attach(*notesLabel, 0, row);
  m_Grid.attach(*notesFrame, 1, row++, 43, 2);
  m_Grid.attach(*spacer, 0, row++);

}


void GeneralInformationSubsystem::LoadFromXML(const std::string& filePath) {
  JSBEdit::XMLLoad xmlLoader;

  try {
    auto xmlDoc = xmlLoader.Load(filePath);

    Aircraft aircraft;
    User user;
    FileMetadata metadata;
    Config config;

    // Check for nodes and set values
    if (auto node = xmlDoc.GetNode("/GeneralInfo/AircraftName"))
      aircraft.setName(node.GetText());
    if (auto node = xmlDoc.GetNode("/GeneralInfo/Author"))
      user.setAuthorName(node.GetText());
    if (auto node = xmlDoc.GetNode("/GeneralInfo/Email"))
      user.setEmail(node.GetText());
    if (auto node = xmlDoc.GetNode("/GeneralInfo/Organization"))
      user.setOrganization(node.GetText());
    if (auto node = xmlDoc.GetNode("/GeneralInfo/ReleaseLevel"))
      config.setReleaseLevel(node.GetText());
    
    // Populate GUI
    m_AircraftNameEntry.set_text(aircraft.getName());
    m_AuthorEntry.set_text(user.getAuthorName());
    m_EmailEntry.set_text(user.getEmail());
    m_OrganizationEntry.get_buffer()->set_text(user.getOrganization());
    m_ReleaseLevelEntry.set_text(config.getReleaseLevel());

    // Populate Release Level dropdown
    auto fdmNode = xmlDoc.GetNode("fdm_config");
    if (fdmNode) {
      // Extract release level
      std::string release = fdmNode.GetAttribute("release").second;
      if (release == "ALPHA")
        m_ReleaseLevelDropdown->set_active(0);
      else if (release == "BETA")
        m_ReleaseLevelDropdown->set_active(1);
      else
        std::cerr << "Unknown release level: " << release << std::endl;
      // Extract and set file path from XML
      auto filePathAttr = fdmNode.GetAttribute("filePath");
      if (!filePathAttr.first.empty()) {
        //std::cout << "File path found in XML: " << filePathAttr.second << std::endl;
        SetFilePath(filePathAttr.second); // Update m_FilePath and GUI
      } else {
        std::cerr << "No file path attribute found in XML!" << std::endl;
        SetFilePath(filePath); // Use the argument as fallback
      }
      } else {
        std::cerr << "fdm_config node not found in XML!" << std::endl;
        SetFilePath(filePath); // Use the argument as fallback
      }
  } catch (const std::exception& e) {
    std::cerr << "Error loading XML: " << e.what() << std::endl;
  }
}

void GeneralInformationSubsystem::SaveToXML(const std::string& filePath, const Aircraft& aircraft, const User& user, const Config& config) {
  JSBEdit::XMLDoc xmlDoc;                // Create a new XMLDoc instance
  JSBEdit::XMLWriter xmlWriter(xmlDoc);  // Pass xmlDoc to XMLWriter

  xmlDoc.GetNode("/GeneralInfo/AircraftName").SetText(aircraft.getName());
  xmlDoc.GetNode("/GeneralInfo/Author").SetText(user.getAuthorName());
  xmlDoc.GetNode("/GeneralInfo/Email").SetText(user.getEmail());
  xmlDoc.GetNode("/GeneralInfo/Organization").SetText(user.getOrganization());
  xmlDoc.GetNode("/GeneralInfo/ReleaseLevel").SetText(config.getReleaseLevel());

  auto fdmNode = xmlDoc.GetNode("fdm_config");
  if (fdmNode) {
    // Create an AttributeKV object for the release attribute
    AttributeKV releaseAttr;  
    int activeIndex = m_ReleaseLevelDropdown->get_active_row_number();

    if (activeIndex == 0)
      releaseAttr = std::make_pair("release", "ALPHA");
    else if (activeIndex == 1)
      releaseAttr = std::make_pair("release", "BETA");

    fdmNode.SetAttribute(releaseAttr); // Pass AttributeKV object
  }

  xmlWriter.Write(filePath);
}

// Method to set file path from the GUI
void GeneralInformationSubsystem::SetFilePath(const std::string& filePath) {
  //std::cout << "Setting file path: " << filePath << std::endl;
    if (filePath.empty()) {
        std::cerr << "Warning: File path is empty!" << std::endl;
    }
    m_FilePath = filePath;
    m_filePathTextbox.set_text(filePath);
}

void GeneralInformationSubsystem::UpdateDataFromGUI(Aircraft& aircraft, User& user, Config& config) {
  // Validate input
  std::string newFilePath = m_filePathTextbox.get_text();
  if (newFilePath.empty()) {
      std::cerr << "Error: File path cannot be empty!" << std::endl;
      return;
  }

  // Update data
  aircraft.setName(m_AircraftNameEntry.get_text());
  user.setAuthorName(m_AuthorEntry.get_text());
  user.setEmail(m_EmailEntry.get_text());
  user.setOrganization(m_OrganizationEntry.get_buffer()->get_text());
  config.setReleaseLevel(m_ReleaseLevelEntry.get_text());
  SetFilePath(newFilePath);
}

void GeneralInformationSubsystem::ValidateAndSave() {
  std::string newFilePath = m_filePathTextbox.get_text();
  if (newFilePath.empty()) {
    std::cerr << "Error: File path is empty! Please provide a valid path." << std::endl;
    return;
  }

  if (!Validation::validateAuthor(m_AuthorEntry.get_text())) {
    std::cerr << "Invalid author name. Please ensure the name field is correctly filled." << std::endl;
    return;
  }

  if (!Validation::validateEmail(m_EmailEntry.get_text())) {
    std::cerr << "Invalid email format. Please enter a valid email address." << std::endl;
    return;
  }
  // Additional validations for each field
}