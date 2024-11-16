#include "AerodynamicsWidget.hpp"

AerodynamicsWidget::AerodynamicsWidget()
: Gtk::Paned(Gtk::Orientation::HORIZONTAL)
{
    aerodynamicsNodes = Gtk::TreeStore::create(columns);
    fetchData();

    set_start_child(hierarchyPanel);
    hierarchyPanel.populateTree(aerodynamicsNodes);

    set_end_child(menuPanel);
}

void AerodynamicsWidget::fetchData()
{
    JSBEdit::XMLDoc doc;
    //TODO: change to the program's working file
    doc.LoadFileAndParse({"../../../data/aircraft/737/737.xml"});
    JSBEdit::XMLNode aerodynamics = doc.GetNodes("fdm_config/aerodynamics")[0];

    std::vector<JSBEdit::XMLNode> children = aerodynamics.GetChildren();

    auto parent = *(aerodynamicsNodes->append());
    parent[columns.columnName] = aerodynamics.GetName();

    appendChildren(parent, children);
}

void AerodynamicsWidget::appendChildren(Gtk::TreeRow parent, std::vector<JSBEdit::XMLNode> children)
{
    for(auto i:children)
    {
        if(i.GetName() == "function" || i.GetName() == "product") {
            //Creates a function data object
            std::shared_ptr<Function> function = std::make_shared<Function>();

            std::string name = i.GetAttribute("name").second;
            if(name == "")
                name = i.GetName();
            std::string description = i.FindChild("description").GetText();

            function->setName(name);
            function->setDescription(description);
            function->setFunctionType(i.GetName());

            //Creates a row to represent the function in the list
            auto row = *(aerodynamicsNodes->append(parent.children()));

            row[columns.columnName] = function->getName();
            if(function->getDescription() != "")
                row[columns.columnName] = function->getName() + " (" + function->getDescription() + ")";

            row[columns.node] = function;

            std::vector<JSBEdit::XMLNode> newChildren = i.GetChildren();
            appendChildren(row, newChildren);
        }
        else if(i.GetName() == "axis")
        {
            //Creates an axis data object
            std::shared_ptr<Axis> axis = std::make_shared<Axis>();

            Axis::AxisName name = Axis::stringToAxisName[i.GetAttribute("name").second];
            Axis::UnitName unit = Axis::stringToUnitName[i.GetAttribute("unit").second];
            axis->setName(name);
            axis->setUnit(unit);

            //Creates a row to represent the axis in the list
            auto row = *(aerodynamicsNodes->append(parent.children()));

            row[columns.columnName] = Axis::axisNameToString[axis->getName()];

            row[columns.node] = axis;

            std::vector<JSBEdit::XMLNode> newChildren = i.GetChildren();
            appendChildren(row, newChildren);
        }
        else if(i.GetName() == "property")
        {
            //Creates a property data object
            std::shared_ptr<AeroProperty> property = std::make_shared<AeroProperty>();

            std::string name = i.GetText();
            property->setName(name);

            //Creates a row to represent the property in the list
            auto row = *(aerodynamicsNodes->append(parent.children()));

            row[columns.columnName] = property->getName();

            row[columns.node] = property;

            std::vector<JSBEdit::XMLNode> newChildren = i.GetChildren();
            appendChildren(row, newChildren);
        }
        else if(i.GetName() == "table")
        {
            //Creates a table data object
            std::shared_ptr<Table> table = std::make_shared<Table>();

            std::string name = i.GetName();
            std::string tableData = i.FindChild("tableData").GetText();
            table->setName(name);
            table->setTableData(tableData);

            //Creates a row to represent the table in the list
            auto row = *(aerodynamicsNodes->append(parent.children()));

            row[columns.columnName] = table->getName();

            row[columns.node] = table;

            std::vector<JSBEdit::XMLNode> newChildren = i.GetChildren();
            appendChildren(row, newChildren);
        }
        else if(i.GetName() == "value")
        {
            //Creates a value data object
            std::shared_ptr<Value> value = std::make_shared<Value>();

            std::string name = i.GetText();
            double input = std::stod(name);
            value->setName(name);
            value->setInput(input);

            //Creates a row to represent the value in the list
            auto row = *(aerodynamicsNodes->append(parent.children()));

            row[columns.columnName] = value->getName();

            row[columns.node] = value;

            std::vector<JSBEdit::XMLNode> newChildren = i.GetChildren();
            appendChildren(row, newChildren);
        }
    }
}

void AerodynamicsWidget::saveData()
{

}