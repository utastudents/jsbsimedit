#include "AerodynamicsWidget.hpp"

// Constructor: Initializes the AerodynamicsWidget, sets up tree view and menu panel
AerodynamicsWidget::AerodynamicsWidget()
: Gtk::Paned(Gtk::Orientation::HORIZONTAL)
{
    // Create the tree model
    aerodynamicsNodes = Gtk::TreeStore::create(columns);
    fetchData();

    // Connect to the row_activated_signal from HierarchyPanel
    hierarchyPanel.row_activated_signal.connect(sigc::mem_fun(*this, &AerodynamicsWidget::on_row_activated));

    // Set the hierarchy panel
    set_start_child(hierarchyPanel);
    hierarchyPanel.populateTree(aerodynamicsNodes);

    // Set the default width of the split menu
    set_position(500);

    (void)menuPanel;  
    (void)selectedNode;
}

// Changes the menu to edit the selected node
void AerodynamicsWidget::on_row_activated(std::shared_ptr<AerodynamicsNode> node) {
    MenuPanel* newMenu;
    if (node != nullptr) {
        switch (node->getType()) {
            case AerodynamicsNode::Type::PROPERTY:
                newMenu = Gtk::make_managed<PropertyMenu>(node);
                break;
            case AerodynamicsNode::Type::VALUE:
                newMenu = Gtk::make_managed<ValueMenu>(node);
                break;
            case AerodynamicsNode::Type::FUNCTION:
                newMenu = Gtk::make_managed<FunctionMenu>(node);
                break;
            case AerodynamicsNode::Type::TABLE:
                newMenu = Gtk::make_managed<TableMenu>(node);
                break;
            case AerodynamicsNode::Type::AXIS:
                newMenu = Gtk::make_managed<AxisMenu>(node);
                break;
            default:
                break;
        }
        if (newMenu) {
            set_end_child(*newMenu);
            newMenu->update_signal.connect(sigc::mem_fun(*this, &AerodynamicsWidget::on_update));
        }
    }
}

// Fetches the aerodynamics data from XML and populates the tree
void AerodynamicsWidget::fetchData()
{
    // Retrieve the aerodynamics XML node
    JSBEdit::XMLNode aerodynamics = xmlptr()->GetNodes("fdm_config/aerodynamics")[0];

    std::vector<JSBEdit::XMLNode> children = aerodynamics.GetChildren();

    // Create the root row for the tree
    auto parent = *(aerodynamicsNodes->append());
    parent[columns.columnName] = aerodynamics.GetName();
    parent[columns.node] = nullptr;

    // Recursively append children nodes to the tree
    appendChildren(parent, children);
}

// Recursively adds child nodes to the tree
void AerodynamicsWidget::appendChildren(Gtk::TreeRow parent, std::vector<JSBEdit::XMLNode> children)
{
    for (auto& i : children)
    {
        // Handle each type of node (function, axis, property, table, value)

        // Check if is an operator
        for(auto operation : Function::operations) {
            if(operation == i.GetName()) {
                // Create a function data object
                std::shared_ptr<Function> function = std::make_shared<Function>();

                // Set function properties
                std::string name = i.GetName();

                function->setName(name);
                function->setFunctionType(i.GetName());

                // Create a row to represent the function in the tree
                auto row = *(aerodynamicsNodes->append(parent.children()));
                row[columns.columnName] = function->getName();

                row[columns.icon] = Gdk::Pixbuf::create_from_file("../../../assets/nodeIcons/icons8-math-30.png");
                row[columns.node] = function;

                appendChildren(row, i.GetChildren());
            }
        }

        // If is a function
        if (i.GetName() == "function") {
            // Create a function data object
            std::shared_ptr<Function> function = std::make_shared<Function>();

            // Set function properties
            std::string name = i.GetAttribute("name").second;
            if (name.empty()) name = i.GetName();
            std::string description = i.FindChild("description").GetText();

            function->setName(name);
            function->setDescription(description);
            function->setFunctionType(i.GetName());

            // Create a row to represent the function in the tree
            auto row = *(aerodynamicsNodes->append(parent.children()));
            row[columns.columnName] = function->getName();
            row[columns.icon] = Gdk::Pixbuf::create_from_file("../../../assets/nodeIcons/icons8-formula-30.png");

            // Append description to name if available
            if (!function->getDescription().empty())
                row[columns.columnName] = function->getName() + " (" + function->getDescription() + ")";

            row[columns.node] = function;

            appendChildren(row, i.GetChildren());
        }

        // If is an axis
        else if (i.GetName() == "axis") {
            // Create an axis data object
            std::shared_ptr<Axis> axis = std::make_shared<Axis>();

            Axis::AxisName name = Axis::stringToAxisName[i.GetAttribute("name").second];
            Axis::UnitName unit = Axis::stringToUnitName[i.GetAttribute("unit").second];
            axis->setName(name);
            axis->setUnit(unit);

            // Create a row to represent the axis in the tree
            auto row = *(aerodynamicsNodes->append(parent.children()));
            row[columns.columnName] = Axis::axisNameToString[axis->getName()];
            row[columns.node] = axis;
            row[columns.icon] = Gdk::Pixbuf::create_from_file("../../../assets/nodeIcons/icons8-axis-30.png");

            // Append unit if available
            if (axis->getUnit() != Axis::UnitName::NONE)
                row[columns.columnName] = Axis::axisNameToString[axis->getName()] + " (" + Axis::unitNameToString[axis->getUnit()] + ")";
                
            appendChildren(row, i.GetChildren());
        }

        // If is a property
        else if (i.GetName() == "property") {
            // Create a property data object
            std::shared_ptr<AeroProperty> property = std::make_shared<AeroProperty>();

            std::string name = i.GetText();
            property->setName(name);

            // Create a row to represent the property in the tree
            auto row = *(aerodynamicsNodes->append(parent.children()));
            row[columns.columnName] = property->getName();
            row[columns.node] = property;
            row[columns.icon] = Gdk::Pixbuf::create_from_file("../../../assets/nodeIcons/icons8-p-30.png");

            // Recursively add children of the property
            appendChildren(row, i.GetChildren());
        }

        // If is a table
        else if (i.GetName() == "table") {
            // Create a table data object
            std::shared_ptr<Table> table = std::make_shared<Table>();

            std::string name = i.GetName();

            std::string rowProperty = "";
            std::string columnProperty = "";
            // Some tables have a row property and a column property
            for(auto child : i.GetChildren()) {
                if(child.GetName() == "independentVar") {
                    if(child.GetAttribute("lookup").second == "column")
                        columnProperty = child.GetText();
                    else if(child.GetAttribute("lookup").second == "row" || rowProperty == "")
                        rowProperty = child.GetText();
                }
            }
            std::string tableData = i.FindChild("tableData").GetText();
            table->setName(name);
            table->setTableData(tableData);
            table->setRowProperty(rowProperty);
            table->setColumnProperty(columnProperty);

            // Create a row to represent the table in the tree
            auto row = *(aerodynamicsNodes->append(parent.children()));
            row[columns.columnName] = table->getName();
            row[columns.node] = table;
            row[columns.icon] = Gdk::Pixbuf::create_from_file("../../../assets/nodeIcons/icons8-table-30.png");

            appendChildren(row, i.GetChildren());
        }

        // If is a value
        else if (i.GetName() == "value") {
            // Create a value data object
            std::shared_ptr<Value> value = std::make_shared<Value>();

            std::string name = i.GetText();
            double input = std::stod(name);
            value->setName(name);
            value->setInput(input);

            // Create a row to represent the value in the tree
            auto row = *(aerodynamicsNodes->append(parent.children()));
            row[columns.columnName] = value->getName();
            row[columns.node] = value;
            row[columns.icon] = Gdk::Pixbuf::create_from_file("../../../assets/nodeIcons/icons8-v-30.png");

            appendChildren(row, i.GetChildren());
        }
    }
}

void AerodynamicsWidget::on_update()
{
    updateData();
}

void AerodynamicsWidget::updateData()
{
    auto children = aerodynamicsNodes->children();
    for(auto i : children){
        updateData(i);
    }
}

void AerodynamicsWidget::updateData(Gtk::TreeRow parent)
{
    auto children = parent.children();
    for(auto i : children){
        std::shared_ptr<AerodynamicsNode> node = i[columns.node];
        if(node->getType() == AerodynamicsNode::VALUE) {
            std::shared_ptr<Value> value = std::dynamic_pointer_cast<Value>(node);
            i[columns.columnName] = std::to_string(value->getInput());
        }
        if(node->getType() == AerodynamicsNode::PROPERTY) {
            std::shared_ptr<AeroProperty> property = std::dynamic_pointer_cast<AeroProperty>(node);
            i[columns.columnName] = property->getName();
        }
        if(node->getType() == AerodynamicsNode::TABLE) {
            std::shared_ptr<Table> table = std::dynamic_pointer_cast<Table>(node);
            i[columns.columnName] = table->getName();
        }
        if(node->getType() == AerodynamicsNode::FUNCTION) {
            std::shared_ptr<Function> function = std::dynamic_pointer_cast<Function>(node);
            i[columns.columnName] = function->getName();
            // Append description to name if available
            if (!function->getDescription().empty())
                i[columns.columnName] = function->getName() + " (" + function->getDescription() + ")";
            // Change icon to operator or function
            if(function->getFunctionType() == "function") {
                i[columns.icon] = Gdk::Pixbuf::create_from_file("../../../assets/nodeIcons/icons8-formula-30.png");
            }
            else {
                i[columns.icon] = Gdk::Pixbuf::create_from_file("../../../assets/nodeIcons/icons8-math-30.png");
            }
        }
        if(node->getType() == AerodynamicsNode::AXIS) {
            std::shared_ptr<Axis> axis = std::dynamic_pointer_cast<Axis>(node);
            i[columns.columnName] = Axis::axisNameToString[axis->getName()];
            // Append unit if available
            if (axis->getUnit() != Axis::UnitName::NONE)
                i[columns.columnName] = Axis::axisNameToString[axis->getName()] + " (" + Axis::unitNameToString[axis->getUnit()] + ")";
        }
        updateData(i);
    }
}

// Function to save data
void AerodynamicsWidget::saveData()
{
    // TODO: do this
}

