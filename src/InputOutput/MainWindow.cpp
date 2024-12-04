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
	std::cout << "IO Tab" << std::endl;
  std::cout << "-------------------------------------------------------------------\n" << std::endl;
  
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

  auto node2 = xmlptr()->GetNodes("fdm_config/output");
  std::vector<JSBEdit::XMLNode> children = node.GetChildren();

  // std::string state = children[0].GetName();
  
  // std::cout << "aa" + state + "aa"<< std::endl;

  // for (size_t i = 0; i < children.size(); ++i) 
  // {
  //   std::cout << "Child " << i << ": " << children[i].GetName() << std::endl;
  // }

  for(int i = 0; i < 13; ++i)
  {
    if(children[i].GetText() == " ON ")
    {
      for (size_t j = 0; j < checkboxes.size(); ++j)
      {
        if(j == i)
        {
          checkboxes[j]->set_active(true);
        }
      }
    }
    else if(children[i].GetText() == " OFF " )
    {
      for (size_t j = 0; j < checkboxes.size(); ++j)
      {
        if(j == i)
        {
          checkboxes[j]->set_active(false);
        }
      }
    }
  }


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

  // creates the configurations textbox next to the "add", "choose", and "delete" buttons,
	// then attaches it to the grid
	m_Grid.attach(customProperty, 0, 8); 

  children[0].SetText(" OFF "); 

  // create save button
  auto saveLabel = Glib::ustring::compose("Save");
	auto saveButton = Gtk::make_managed<Gtk::ToggleButton>(saveLabel);
	m_Grid.attach(*saveButton, 4, 8);

  // saveButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::IOSave), children, checkboxes);
  saveButton->signal_clicked().connect(
    sigc::bind(
        sigc::mem_fun(*this, &MainWindow::IOSave), 
        children, 
        checkboxes
    )
);


  std::cout << "\n\n\n" << std::endl;
  
}
// Function to set a specific checkbox on or off by its label or index
// void MainWindow::setCheckboxState(int ID, bool state, const std::vector<Gtk::CheckButton*>& checkboxes)
// {
  
// }

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
	m_Grid.attach(*chooseButton, 1, 8);
	
	// Connect the "Choose" button's signal to onChooseButtonClicked
  chooseButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onChooseButtonClicked));
    
	// creates add button
	auto addLabel = Glib::ustring::compose("Add");
	auto addButton = Gtk::make_managed<Gtk::ToggleButton>(addLabel);
	m_Grid.attach(*addButton, 2, 8);
    
	// creates delete button
	auto deleteLabel = Glib::ustring::compose("Delete");
	auto deleteButton = Gtk::make_managed<Gtk::ToggleButton>(deleteLabel);
	m_Grid.attach(*deleteButton, 3, 8);

}


// Function to handle "Choose" button click
void MainWindow::onChooseButtonClicked() 
{
  /*
  auto popUp = new Gtk::Window();
  popUp->set_title("Properties");
  popUp->set_default_size(1000, 700); //can be adjusted
  
  // Create a grid for the popup content
	auto popUpGrid = Gtk::make_managed<Gtk::Grid>();
	popUp->set_child(*popUpGrid);
  */
  auto popUpWindow = new PopUpWindow();
  popUpWindow->show(); // Show the popup window
    
    
}

void MainWindow::IOSave(std::vector<JSBEdit::XMLNode> children, std::vector<Gtk::CheckButton*> checkboxes)
{
  std::cout << "Save method called!\n" << std::endl;

  // for(int i = 0; i < 13; ++i)
  // {
  //   if(children[i].GetText() == " ON ")
  //   {
  //     for (size_t j = 0; j < checkboxes.size(); ++j)
  //     {
  //       if(j == i)
  //       {
  //         checkboxes[j]->set_active(true);
  //       }
  //     }
  //   }
  //   else if(children[i].GetText() == " OFF " )
  //   {
  //     for (size_t j = 0; j < checkboxes.size(); ++j)
  //     {
  //       if(j == i)
  //       {
  //         checkboxes[j]->set_active(false);
  //       }
  //     }
  //   }
  // }
  children[0].SetText(" OFF ");
  // for (size_t i = 0; i < 13; ++i)
  // {
  //   if(checkboxes[i]->get_active())
  //   {
  //     children[i].SetText(" ON ");
  //   }
  //   else if(!(checkboxes[i]->get_active()))
  //   {
  //     children[i].SetText(" OFF ");
  //   }
  // }



}

void MainWindow::on_checkbox_toggled(const std::string& label, Gtk::CheckButton* checkbox)
                                      // std::set<std::string>& toggledCheckboxes) 
{
  std::cout << "Checkbox [" << label << "] is now " << (checkbox->get_active() ? "ON" : "OFF") << std::endl;

  // addCheckBox(label);
  
  // toggledCheckboxes.insert(label);

  // Print out the current contents of the set
        // std::cout << "Toggled checkboxes so far: ";
        // for (const auto& lbl : toggledCheckboxes) {
        //     std::cout << lbl << " ";
        // }
        // std::cout << std::endl;
}

// void MainWindow::addCheckBox(const std::string& label)
// {
//   toggledCheckboxes.insert(label);


//   if (std::find(toggledCheckboxes.begin(), toggledCheckboxes.end(), label) == toggledCheckboxes.end()) 
//   {
//     toggledCheckboxes.push_back(label);
//   }

//   // Print out the current contents of the vector
//   std::cout << "Toggled checkboxes so far: ";
//   for (const auto& lbl : toggledCheckboxes) 
//   {
//     std::cout << lbl << " ";
//   }
//   std::cout << std::endl;
// }
