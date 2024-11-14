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
    doc.LoadFileAndParse({"../../../reference/JSBSimCommander/f16.xml"});
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
            auto row = *(aerodynamicsNodes->append(parent.children()));
            if(i.GetName() != "")
                row[columns.columnName] = i.GetName();
            else
                row[columns.columnName] = i.GetText();
            std::vector<JSBEdit::XMLNode> newChildren = i.GetChildren();
            appendChildren(row, newChildren);
    }
}

void AerodynamicsWidget::saveData()
{

}