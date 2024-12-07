#include "PopUpWindow.hpp"
#include "MainWindow.hpp"
#include "inc/XML_api.hpp"
#include "XML/XMLDoc.hpp"
#include "XML/XMLNode.hpp"
#include "XML/XMLLoad.hpp"
#include "XML/XMLParser.hpp"

#include <pugixml.hpp>
#include <vector>
#include <string>
#include <algorithm>


// constructor - manage main window
MainWindow::MainWindow(Gtk::Grid& m_Grid) 
{
	textboxesAndLists(m_Grid);
	onButtonClicked(m_Grid);

  // toggledCheckboxes = std::set<std::string>();
	
}

// create and manage textboxes and drop down lists
void MainWindow::textboxesAndLists(Gtk::Grid& m_Grid) 
{
	//std::cout << "IO Tab" << std::endl;
  //std::cout << "-------------------------------------------------------------------\n" << std::endl;
    
    

  // Load the xml file and get the starting node
  auto node = xmlptr()->GetNode("fdm_config/output");


	// creates name label and text box, then attaches them to the grid
  name.set_text("Name(*) : ");
  m_Grid.attach(name, 0, 0);
  // Get the attribute from the XML File
  auto nameField = node.GetAttribute("name");
   

  nameTextBox.set_text(nameField.second);
  m_Grid.attach(nameTextBox, 1, 0);
    

    
	// creates type label and drop down list, then attaches them to the grid
	type.set_text("Type(*) : ");
	typeDropDownList.append("CSV");
	typeDropDownList.append("TABULAR");
    

  // Get the attribute from the XML File
  auto typeField = node.GetAttribute("type");
	// Choose default based on what's in the XML File
  // If TABULAR, put that or else CSV is default
	if(typeField.second == "TABULAR")
  {
    typeDropDownList.set_active(1);
  }
  else
  {
    typeDropDownList.set_active(0);
  }
	m_Grid.attach(type, 0, 1);
	m_Grid.attach(typeDropDownList, 1, 1);
   
    
	// creates rate label and text box, then attaches them to the grid
  rate.set_text("Rate(*) : ");
	// Get the attribute from the XML File
  auto rateFiled = node.GetAttribute("rate");
  rateTextBox.set_text(rateFiled.second);
	m_Grid.attach(rate, 0, 2);
	m_Grid.attach(rateTextBox, 1, 2);


  // Vector to store labels for each checkbox
  std::vector<std::string> checkboxLabels = 
  {
    "simulation", "atmosphere", "massprops", "aerosurfaces", 
    "rates", "velocities", "forces", "moments", 
    "position", "coefficients", "ground_reactions", 
    "fcs", "propulsion"
  };

  // Vector to store the CheckButtons
  std::vector<Gtk::CheckButton*> checkboxes;

  int row = 3; // Start row for checkboxes
  int col = 0; // Start column for checkboxes

  // Create and attach labels and checkboxes
  for (const auto& labelText : checkboxLabels) 
  {
    // Create and manage a label
    auto label = Gtk::make_managed<Gtk::Label>(labelText);
    m_Grid.attach(*label, col * 2, row); // Place label in the column

    // Create and manage a checkbox
    auto checkbox = Gtk::make_managed<Gtk::CheckButton>();
    checkboxes.push_back(checkbox); // Store checkbox pointer if needed for later access
    m_Grid.attach(*checkbox, col * 2 + 1, row); // Place checkbox next to label

    // Update column and row counters
    col++;
    if (col >= 4) 
    { // Move to the next row after 4 columns
      col = 0;
      row++;
    }
  }
    

  // Get the XML node for output & get its children
  auto node2 = xmlptr()->GetNodes("fdm_config/output");
  std::vector<JSBEdit::XMLNode> children = node.GetChildren();

  
  // DEBUG: Do not remove
  // std::string state = children[0].GetName();
  
  // std::cout << "aa" + state + "aa"<< std::endl;

  // for (size_t i = 0; i < children.size(); ++i) 
  // {
  //   if(children[i].GetName() == "property")
  //   {
  //     std::cout << "Child " << i << ": " << children[i].GetText() << std::endl;
  //   }
  // }
    
  for (size_t i = 0; i < children.size() && i < checkboxes.size(); ++i) 
  {
    if (children[i].GetText() == " ON ") 
    {
      checkboxes[i]->set_active(true);
    } 
    else if (children[i].GetText() == " OFF ") 
    {
      checkboxes[i]->set_active(false);
    }
    
  }

  for (size_t i = 0; i < children.size(); ++i) 
  {
    if(children[i].GetName() == "property")
    {
      //std::cout << "Checking child: " << children[i].GetName() << " Text: " << children[i].GetText() << std::endl;
      properties.push_back(children[i].GetText());
    }
  }

  // Add a property display area and show the properties
  addPropertiesTextBox(m_Grid, properties);

  // Connecting each checkbox with a signal handler using sigc::bind
  checkboxes[0]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "Simulation", checkboxes[0]));
  checkboxes[1]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "Atmosphere", checkboxes[1]));
  checkboxes[2]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "Massprops", checkboxes[2]));
  checkboxes[3]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "Aerosurfaces", checkboxes[3]));
  checkboxes[4]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "Rates", checkboxes[4]));
  checkboxes[5]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "Velocities", checkboxes[5]));
  checkboxes[6]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "Forces", checkboxes[6]));
  checkboxes[7]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "Moments", checkboxes[7]));
  checkboxes[8]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "Position", checkboxes[8]));
  checkboxes[9]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "Coefficients", checkboxes[9]));
  checkboxes[10]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "Ground Reactions", checkboxes[10]));
  checkboxes[11]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "FCS", checkboxes[11]));
  checkboxes[12]->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_checkbox_toggled), "Propulsion", checkboxes[12]));
    
  // Spearator to Distinguish between the different GUI sections
  Gtk::Separator* separator = Gtk::make_managed<Gtk::Separator>(Gtk::Orientation::HORIZONTAL);
  // Add the separator to the grid
  m_Grid.attach(*separator, 0, 7, 10, 1);  

  propertyName.set_text("Property Names: ");
  m_Grid.attach(propertyName, 0, 8);

  // creates the configurations textbox next to the "add", "choose", and "delete" buttons,
	// then attaches it to the grid
  Gtk::Entry customProperty;
	m_Grid.attach(customProperty, 0, 25);

  // children[0].SetText(" OFF ");
    if (children.size() > 0) {
      children[0].SetText(" OFF ");
    }

    


  // create save button
  auto saveLabel = Glib::ustring::compose("Save");
	auto saveButton = Gtk::make_managed<Gtk::ToggleButton>(saveLabel);
	m_Grid.attach(*saveButton, 4, 25);
    


  // saveButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::IOSave), children, checkboxes);
  saveButton->signal_clicked().connect  
  (
    sigc::bind
    (
      sigc::mem_fun(*this, &MainWindow::IOSave), 
      children, 
      checkboxes,
      checkboxLabels
    )
  );
 
  //std::cout << "\n\n\n" << std::endl;
  
}

// create and manage checkboxes
void MainWindow::onCheckBoxToggle() 
{



}

// Manage buttons when clicked
void MainWindow::onButtonClicked(Gtk::Grid& m_Grid)
{
  // creates choose button
	auto chooseLabel = Glib::ustring::compose("Choose");
	auto chooseButton = Gtk::make_managed<Gtk::ToggleButton>(chooseLabel);
	m_Grid.attach(*chooseButton, 1, 25);
	
	// Connect the "Choose" button's signal to onChooseButtonClicked
  chooseButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onChooseButtonClicked));
    
	// creates add button
	auto addLabel = Glib::ustring::compose("Add");
	auto addButton = Gtk::make_managed<Gtk::ToggleButton>(addLabel);
	m_Grid.attach(*addButton, 2, 25);
    
	// creates delete button
	auto deleteLabel = Glib::ustring::compose("Delete");
	auto deleteButton = Gtk::make_managed<Gtk::ToggleButton>(deleteLabel);
	m_Grid.attach(*deleteButton, 3, 25);

}


// Function to handle "Choose" button click
void MainWindow::onChooseButtonClicked() 
{
  auto popUpWindow = new PopUpWindow();
  popUpWindow->show(); // Show the popup window
}

void MainWindow::IOSave(std::vector<JSBEdit::XMLNode> children, std::vector<Gtk::CheckButton*> checkboxes, const std::vector<std::string> checkboxLabels)
{
  //std::cout << "Save method called!\n" << std::endl;
  
  // Set the updated checkbox values
  for (size_t i = 0; i < checkboxes.size(); ++i) 
  {
    // Get the status of the checkbox
    bool isActive = checkboxes[i]->get_active();

    // Loop Over the Children and find the XMLNode 
    for (size_t j = 0; j < children.size(); ++j) 
    {
      // Match the children with the corresponding checkboxLabel
      if (children[j].GetText() == checkboxLabels[i]) 
      {
        // Set the updated states
        if(isActive)
        {
          children[j].SetText(" ON ");
        }
        else
        {
          children[j].SetText(" OFF ");
        }
      }
    }
    //std::cout << "Checkbox " << i << " is " << (isActive ? "active" : "inactive") << std::endl;
  }



}

void MainWindow::on_checkbox_toggled(const std::string& label, Gtk::CheckButton* checkbox)
                                      // std::set<std::string>& toggledCheckboxes) 
{
  std::cout << "Checkbox [" << label << "] is now " << (checkbox->get_active() ? "ON" : "OFF") << std::endl;
}

void MainWindow::addPropertiesTextBox(Gtk::Grid& grid, const std::vector<std::string>& properties)
{
  // Create a ListBox to display the properties
  auto listBox = Gtk::make_managed<Gtk::ListBox>();

  // Populate the ListBox with the strings from the vector
  for (const auto& property : properties) {
      listBox->append(*Gtk::make_managed<Gtk::Label>(property));
  }

  // Optional: Add spacing and margins for better visuals
  listBox->set_margin(10);
  listBox->set_opacity(5);

  // Create a ScrolledWindow to make the ListBox scrollable
  auto scrolledWindow = Gtk::make_managed<Gtk::ScrolledWindow>();
  scrolledWindow->set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  scrolledWindow->set_child(*listBox); // Attach the ListBox to the ScrolledWindow
  scrolledWindow->set_margin(5);

  // Attach the ScrolledWindow containing the ListBox to the grid
  grid.attach(*scrolledWindow, 0, 9, 7, 10);
}
