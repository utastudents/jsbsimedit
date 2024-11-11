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
  organizationTextView->get_buffer()->set_text("1. Still need to add a scroll bar and add a frame?\n2.\n3"); // Placeholder text
  
  // Configure the ScrolledWindow
  organizationScrolledWindow->set_min_content_height(100); // Set the height for the text area
  organizationScrolledWindow->set_min_content_width(300); // Set the height for the text area  
  organizationScrolledWindow->set_child(*organizationTextView);

  // Description

  // File Date

  // References

  // Limitations
  auto limitationsLabel = Gtk::make_managed<Gtk::Label>("limitations");
  auto limitationsTextView = Gtk::make_managed<Gtk::TextView>();
  auto limitationsScrolledWindow = Gtk::make_managed<Gtk::ScrolledWindow>();
  auto limitationsFrame = Gtk::make_managed<Gtk::Frame>();

  // Set up TextView content and appearance for Limitations
  limitationsTextView->get_buffer()->set_text("1.\n2.\n3"); // Placeholder text
  
  // Configure the ScrolledWindow
  limitationsScrolledWindow->set_min_content_height(100); // Set the height for the text area
  limitationsScrolledWindow->set_min_content_width(300); // Set the height for the text area  
  limitationsScrolledWindow->set_child(*limitationsTextView);

  // Notes
  auto notesLabel = Gtk::make_managed<Gtk::Label>("notes");
  auto notesTextView = Gtk::make_managed<Gtk::TextView>();
  auto notesScrolledWindow = Gtk::make_managed<Gtk::ScrolledWindow>();
  auto notesFrame = Gtk::make_managed<Gtk::Frame>();

  // Set up TextView content and appearance for Notes
  notesTextView->get_buffer()->set_text("1.\n2.\n3"); // Placeholder text
  
  // Configure the ScrolledWindow
  notesScrolledWindow->set_min_content_height(100); // Set the height for the text area
  notesScrolledWindow->set_min_content_width(300); // Set the height for the text area  
  notesScrolledWindow->set_child(*notesTextView);

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
  m_Grid.attach(*organizationScrolledWindow, 1, row++, 5, 2); // Spans multiple columns for the text area

  m_Grid.attach(*limitationsLabel, 0, row);
  m_Grid.attach(*limitationsScrolledWindow, 1, row++, 8, 2);

  m_Grid.attach(*notesLabel, 0, row);
  m_Grid.attach(*notesScrolledWindow, 1, row++, 8, 2);
}