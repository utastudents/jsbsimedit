#include <iostream>
#include "GeneralInformationSubsystem.hpp"

GeneralInformationSubsystem::GeneralInformationSubsystem()
{
    m_Name = "GeneralInformation";
    std::cout << "In GeneralInformationSubsystem constructor" << std::endl; 
}

void GeneralInformationSubsystem::Create()
{
  std::cout << "in GeneralInformationSubsystem::Create" << std::endl;

  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  // Row tracking variable
  int row = 0;

  // Aircraft Name
  auto aircraftNameLabel = Gtk::make_managed<Gtk::Label>("Aircraft Name");
  auto aircraftNameTextbox = Gtk::make_managed<Gtk::Entry>();
  aircraftNameTextbox->set_text("Place holder."); // load aircraft name here

  // File Path
  auto filePathLabel = Gtk::make_managed<Gtk::Label>("File Path");
  auto filePathTextbox = Gtk::make_managed<Gtk::Entry>();
  filePathTextbox->set_text("Place holder."); // load file path here

  // Release Level (Drop-down)
  auto releaseLevelLabel = Gtk::make_managed<Gtk::Label>("Release Level");
  auto releaseLevelDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
  releaseLevelDropDown->append("ALPHA"); // load release levels
  releaseLevelDropDown->append("BETA");
  releaseLevelDropDown->set_active(0); // sets ALPHA default

  // Configuration Version
  auto configVersionLabel = Gtk::make_managed<Gtk::Label>("Configuration Version");
  auto configVersionTextbox = Gtk::make_managed<Gtk::Entry>();
  configVersionTextbox->set_text(""); // Load configuration version here

  // Flight Model Version
  auto flightModelVersionLabel = Gtk::make_managed<Gtk::Label>("Flight Model Version");
  auto flightModelVersionTextbox = Gtk::make_managed<Gtk::Entry>();
  configVersionTextbox->set_text(""); // Load flight model version here

  // Author
  auto authorLabel = Gtk::make_managed<Gtk::Label>("Author");
  auto authorTextbox = Gtk::make_managed<Gtk::Entry>();
  authorTextbox->set_text(""); // Load author name here

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
auto descriptionLabel = Gtk::make_managed<Gtk::Label>("description");
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
  auto fileDateLabel = Gtk::make_managed<Gtk::Label>("FileDate");
  auto fileDateTextbox = Gtk::make_managed<Gtk::Entry>();
  fileDateTextbox->set_text(""); // Load FileDate name here

  // References
  auto referencesLabel = Gtk::make_managed<Gtk::Label>("References");
  auto referencesTextView = Gtk::make_managed<Gtk::TextView>();
  auto referencesScrolledWindow = Gtk::make_managed<Gtk::ScrolledWindow>();
  auto referencesFrame = Gtk::make_managed<Gtk::Frame>();

  // Set up TextView content and appearance
  referencesTextView->get_buffer()->set_text(""); // Placeholder text

  // Configure the ScrolledWindow
  referencesScrolledWindow->set_min_content_height(100); // Set the height for the text area
  referencesScrolledWindow->set_min_content_width(300);  // Set the width for the text area
  referencesScrolledWindow->set_child(*referencesTextView);
  referencesScrolledWindow->set_policy(Gtk::PolicyType::ALWAYS, Gtk::PolicyType::ALWAYS);

  // Add the ScrolledWindow to the Frame to give it a border
  referencesFrame->set_child(*referencesScrolledWindow);

  // Set TextView wrap mode
  referencesTextView->set_wrap_mode(Gtk::WrapMode::WORD);

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
  m_Grid.attach(*aircraftNameTextbox, 1, row);
  m_Grid.attach(*filePathLabel, 3, row);
  m_Grid.attach(*filePathTextbox, 4, row++, 5);

  m_Grid.attach(*releaseLevelLabel, 0, row);
  m_Grid.attach(*releaseLevelDropDown, 1, row);
  m_Grid.attach(*configVersionLabel, 3, row);
  m_Grid.attach(*configVersionTextbox, 4, row);
  m_Grid.attach(*flightModelVersionLabel, 5, row);
  m_Grid.attach(*flightModelVersionTextbox, 6, row++);
  
  m_Grid.attach(*authorLabel, 0, row);
  m_Grid.attach(*authorTextbox, 1, row);
  m_Grid.attach(*emailLabel, 3, row);
  m_Grid.attach(*emailTextbox, 4, row++);

  m_Grid.attach(*organizationLabel, 0, row);
  m_Grid.attach(*organizationFrame, 1, row, 1, 1); // Spans multiple columns for the text area



  m_Grid.attach(*descriptionLabel, 3, row);
  m_Grid.attach(*descriptionFrame, 4, row++, 1, 2);

  m_Grid.attach(*fileDateLabel, 0, row);
  m_Grid.attach(*fileDateTextbox, 1, row);

  auto spacer = Gtk::make_managed<Gtk::Label>();
  spacer->set_size_request(-1, 10);  // Set height to 10 pixels
  m_Grid.attach(*spacer, 0, row++);

  m_Grid.attach(*referencesLabel, 0, row);
  m_Grid.attach(*referencesFrame, 1, row++, 8, 2);
  m_Grid.attach(*spacer, 0, row++);

  m_Grid.attach(*limitationsLabel, 0, row);
  m_Grid.attach(*limitationsFrame, 1, row++, 8, 2);
  m_Grid.attach(*spacer, 0, row++);

  m_Grid.attach(*notesLabel, 0, row);
  m_Grid.attach(*notesFrame, 1, row++, 8, 2);
  m_Grid.attach(*spacer, 0, row++);

}