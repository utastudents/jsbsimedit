#include "MainWindow.hpp"

// constructor - manage main window
MainWindow::MainWindow(Gtk::Grid& m_Grid) {
	textboxesAndLists(m_Grid);
	onButtonClicked(m_Grid);
}

// create and manage textboxes and drop down lists
void MainWindow::textboxesAndLists(Gtk::Grid& m_Grid) {
	// creates name label and text box, then attaches them to the grid
	auto nameLabel = Gtk::make_managed<Gtk::Label>("Name(*)");
	auto nameTextbox = Gtk::make_managed<Gtk::Entry>();
	m_Grid.attach(*nameLabel, 0, 0);
	m_Grid.attach(*nameTextbox, 1, 0);
    
	// creates type label and drop down list, then attaches them to the grid
	auto typeLabel = Gtk::make_managed<Gtk::Label>("Type(*)");
	auto typeDropDownList = Gtk::make_managed<Gtk::ComboBoxText>();
	// adds "CSV" and "Tabular" options to the drop down list
	typeDropDownList->append("CSV");
	typeDropDownList->append("Tabular");
	// defaults to "CSV" for the drop down list
	typeDropDownList->set_active(0);
	m_Grid.attach(*typeLabel, 0, 1);
	m_Grid.attach(*typeDropDownList, 1, 1);
    
	// creates rate label and text box, then attaches them to the grid
	auto rateLabel = Gtk::make_managed<Gtk::Label>("Rate(*)");
	auto rateTextbox = Gtk::make_managed<Gtk::Entry>();
	// set rate default to 60 (seconds)
	rateTextbox->set_text("60");
	m_Grid.attach(*rateLabel, 0, 2);
	m_Grid.attach(*rateTextbox, 1, 2);
    
	// creates the configurations textbox next to the "add", "choose", and "delete" buttons,
	// then attaches it to the grid
	auto configTextbox = Gtk::make_managed<Gtk::Entry>();
	m_Grid.attach(*configTextbox, 0, 3);
}

// create and manage checkboxes
void MainWindow::onCheckBoxToggle() {}

// create and manage buttons
void MainWindow::onButtonClicked(Gtk::Grid& m_Grid) {
	// creates choose button
	auto chooseLabel = Glib::ustring::compose("Choose");
	auto chooseButton = Gtk::make_managed<Gtk::ToggleButton>(chooseLabel);
	m_Grid.attach(*chooseButton, 1, 3);
	
	// Connect the "Choose" button's signal to onChooseButtonClicked
    chooseButton->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::onChooseButtonClicked));
    
	// creates add button
	auto addLabel = Glib::ustring::compose("Add");
	auto addButton = Gtk::make_managed<Gtk::ToggleButton>(addLabel);
	m_Grid.attach(*addButton, 2, 3);
    
	// creates delete button
	auto deleteLabel = Glib::ustring::compose("Delete");
	auto deleteButton = Gtk::make_managed<Gtk::ToggleButton>(deleteLabel);
	m_Grid.attach(*deleteButton, 3, 3);
}


// Function to handle "Choose" button click
void MainWindow::onChooseButtonClicked() {
    auto popUp = new Gtk::Window();
    popUp->set_title("Properties");
    popUp->set_default_size(1000, 700); //can be adjusted
    
      // Create a grid for the popup content
	auto popUpGrid = Gtk::make_managed<Gtk::Grid>();
	popUp->set_child(*popUpGrid);

    popUp->show(); // Show the popup window
}
