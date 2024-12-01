#include "MenuPanel.hpp"

FunctionMenu::FunctionMenu(std::shared_ptr<AerodynamicsNode> node)
{
    // Make changes to this object vvv
    this->function = std::dynamic_pointer_cast<Function>(node);
    this->setHeader("Function or Operator");

    // Create and configure the grid
    auto grid = Gtk::make_managed<Gtk::Grid>();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    append(*grid);

    int index = 0;

    // Create Dropdown Label
    auto dropdownLabel = Gtk::make_managed<Gtk::Label>("Type:");
    dropdownLabel->set_halign(Gtk::Align::START);
    grid->attach(*dropdownLabel, 0, index, 1, 1);

    // Initialize the dropdown (assign to member variable)
    dropdown = Gtk::make_managed<Gtk::ComboBoxText>();

    std::vector<std::string> options = {
        "function", "product", "difference", "sum", "quotient", "pow", "abs", 
        "sin", "cos", "tan", "asin", "acos", "atan", "derivative", "integral", 
        "lt", "le", "ge", "gt", "eq", "ne", "and", "or", "not", "ifthen"
    };

    for (const auto& option : options) {
        dropdown->append(option);
    }


    // Set the active item if necessary
    dropdown->set_active(0); // Sets the first option as active

    // Attach the dropdown to the grid
    grid->attach(*dropdown, 1, index++, 1, 1);

    // Create Name Field
    auto nameLabel = Gtk::make_managed<Gtk::Label>("Name:");
    nameLabel->set_halign(Gtk::Align::START);
    grid->attach(*nameLabel, 0, index, 1, 1);

    nameEntry = Gtk::make_managed<Gtk::Entry>();
    nameEntry->set_text(function ? function->getName() : "");
    grid->attach(*nameEntry, 1, index++, 1, 1);

    // Create Description Field
    auto descriptionLabel = Gtk::make_managed<Gtk::Label>("Description:");
    descriptionLabel->set_halign(Gtk::Align::START);
    grid->attach(*descriptionLabel, 0, index, 1, 1);

    descriptionEntry = Gtk::make_managed<Gtk::Entry>();
    descriptionEntry->set_text(function ? function->getDescription() : "");
    grid->attach(*descriptionEntry, 1, index++, 1, 1);

    // Create Save Button
    auto saveButton = Gtk::make_managed<Gtk::Button>("Save");
    grid->attach(*saveButton, 1, index++, 1, 1);

    // Connect the save button's clicked signal
    saveButton->signal_clicked().connect([this](){
        if(function){
            function->setName(nameEntry->get_text());
            function->setDescription(descriptionEntry->get_text());
            auto selected_option = this->dropdown->get_active_text();

            std::cout << "Changes saved: "
                      << "Name = " << function->getName()
                      << ", Description = " << function->getDescription()
                      << ", Selected Option = " << selected_option
                      << std::endl;
        }
    });

    //To Save text changes for the Name/Description fields
    /*nameEntry->signal_changed().connect([this](){
        if(function){
            function->setName(nameEntry->get_text());
        }
    });

    descriptionEntry->signal_changed().connect([this](){
        if(function){
            function->setDescription(descriptionEntry->get_text());
        }
    });*/


}
