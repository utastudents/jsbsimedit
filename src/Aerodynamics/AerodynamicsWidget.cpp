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
        if (i.GetName() == "function" || i.GetName() == "product") {
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

            // Append description to name if available
            if (!function->getDescription().empty())
                row[columns.columnName] = function->getName() + " (" + function->getDescription() + ")";

            row[columns.node] = function;

            appendChildren(row, i.GetChildren());
        }
        else if (i.GetName() == "axis") {
            // Create an axis data object
            std::shared_ptr<Axis> axis = std::make_shared<Axis>();

            Axis::AxisName name = Axis::stringToAxisName[i.GetAttribute("name").second];
            Axis::UnitName unit = Axis::stringToUnitName[i.GetAttribute("unit").second];
            axis->setName(name);
            axis->setUnit(unit);
            std::cout << "The unit for " << Axis::axisNameToString[axis->getName()] << " is " << axis->getUnit() << std::endl;

            // Create a row to represent the axis in the tree
            auto row = *(aerodynamicsNodes->append(parent.children()));
            row[columns.columnName] = Axis::axisNameToString[axis->getName()];
            row[columns.node] = axis;

            // Append unit if available
            if (axis->getUnit() != Axis::UnitName::NONE)
                row[columns.columnName] = Axis::axisNameToString[axis->getName()] + " (" + Axis::unitNameToString[axis->getUnit()] + ")";
                
            appendChildren(row, i.GetChildren());
        }
        else if (i.GetName() == "property") {
            // Create a property data object
            std::shared_ptr<AeroProperty> property = std::make_shared<AeroProperty>();

            std::string name = i.GetText();
            property->setName(name);

            // Create a row to represent the property in the tree
            auto row = *(aerodynamicsNodes->append(parent.children()));
            row[columns.columnName] = property->getName();
            row[columns.node] = property;

            // Recursively add children of the property
            appendChildren(row, i.GetChildren());
        }
        else if (i.GetName() == "table") {
            // Create a table data object
            std::shared_ptr<Table> table = std::make_shared<Table>();

            std::string name = i.GetName();
            std::string tableData = i.FindChild("tableData").GetText();
            table->setName(name);
            table->setTableData(tableData);

            // Create a row to represent the table in the tree
            auto row = *(aerodynamicsNodes->append(parent.children()));
            row[columns.columnName] = table->getName();
            row[columns.node] = table;

            appendChildren(row, i.GetChildren());
        }
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
        }
        if(node->getType() == AerodynamicsNode::PROPERTY) {
        }
        if(node->getType() == AerodynamicsNode::TABLE) {
        }
        if(node->getType() == AerodynamicsNode::FUNCTION) {
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
