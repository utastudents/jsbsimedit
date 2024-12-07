#include "MenuPanel.hpp"

FunctionMenu::FunctionMenu(std::shared_ptr<AerodynamicsNode> node)
{
    // Make changes to this object vvv
    this->function = std::dynamic_pointer_cast<Function>(node);
    this->setHeader("Function or Operator");

    // Create and configure the grid
    grid = Gtk::make_managed<Gtk::Grid>();
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);
    append(*grid);

    int index = 0;

    // Create Dropdown Label
    dropdownLabel = Gtk::make_managed<Gtk::Label>("Type:");
    dropdownLabel->set_halign(Gtk::Align::START);
    grid->attach(*dropdownLabel, 0, index, 1, 1);

    // Initialize the dropdown (assign to member variable)
    dropdown = Gtk::make_managed<Gtk::ComboBoxText>();
    dropdown->set_tooltip_text("Change to either a function or operator");

    std::vector<std::string> options = {
        "function", "product", "difference", "sum", "quotient", "pow", "abs", 
        "sin", "cos", "tan", "asin", "acos", "atan", "derivative", "integral", 
        "lt", "le", "ge", "gt", "eq", "ne", "and", "or", "not", "ifthen"
    };

    for (const auto& option : options) {
        dropdown->append(option);
    }

    // Attach the dropdown to the grid
    grid->attach(*dropdown, 1, index++, 1, 1);

    // Create Name Field
    nameLabel = Gtk::make_managed<Gtk::Label>("Name:");
    nameLabel->set_halign(Gtk::Align::START);
    grid->attach(*nameLabel, 0, index, 1, 1);

    nameEntry = Gtk::make_managed<Gtk::Entry>();
    nameEntry->set_text(function ? function->getName() : "");
    nameEntry->set_tooltip_text("Change this function's name");
    grid->attach(*nameEntry, 1, index++, 1, 1);

    // Create Description Field
    descriptionLabel = Gtk::make_managed<Gtk::Label>("Description:");
    descriptionLabel->set_halign(Gtk::Align::START);
    grid->attach(*descriptionLabel, 0, index, 1, 1);

    descriptionEntry = Gtk::make_managed<Gtk::Entry>();
    descriptionEntry->set_text(function ? function->getDescription() : "");
    descriptionEntry->set_tooltip_text("Change this function's description");
    grid->attach(*descriptionEntry, 1, index++, 1, 1);

    // Create Save Button
    saveButton = Gtk::make_managed<Gtk::Button>("Save");
    saveButton->set_tooltip_text("Save changes to this function/operator");
    grid->attach(*saveButton, 1, index++, 1, 1);

    // Connect the save button's clicked signal
    saveButton->signal_clicked().connect([this](){
        if(function){
            function->setFunctionType(dropdown->get_active_text());
            if(function->getFunctionType() == "function") {
                function->setName(nameEntry->get_text());
                function->setDescription(descriptionEntry->get_text());
            }
            // Operators dont have names/descriptions
            else {
                function->setName(function->getFunctionType());
                function->setDescription("");
            }

            // std::cout << "Changes saved: "
            //           << "Name = " << function->getName()
            //           << ", Description = " << function->getDescription()
            //           << ", Selected Option = " << function->getFunctionType()
            //           << std::endl;
        }
        update_signal.emit();
    });

    dropdown->property_active().signal_changed().connect([this](){
        if(dropdown->get_active_text() == "function") {
            nameLabel->show();
            descriptionLabel->show();
            nameEntry->show();
            descriptionEntry->show();
        }
        else {
            nameLabel->hide();
            descriptionLabel->hide();
            nameEntry->hide();
            descriptionEntry->hide();
        }
    });

    // Set the active item if necessary
    for(int i = 0; i < options.size(); i++) {
        if(options[i] == function->getFunctionType())
            dropdown->set_active(i);
    }

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
