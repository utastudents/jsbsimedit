#include "GainComponentWindow.hpp"

namespace DragDrop
{

GainComponentWindow::GainComponentWindow(std::shared_ptr<IComponentCommon> comp, 
    std::shared_ptr<std::set<std::string>> setOfNames)
        : ComponentWindowCommon(comp, setOfNames)
{
    CreateCommonTab();
    CreateOtherTabs();
}

void GainComponentWindow::CreateOtherTabs()
{
    std::vector<std::string> m_tabsToMake{"Scheduled", "Aerosomething"};
    for(auto& i : m_tabsToMake)
    {
        Gtk::Box box;        
        box.set_vexpand(true);
        box.set_hexpand(true);
        Gtk::Label labelT{"Sorry this tab has not been implemented yet.."};
        box.append(labelT);
        m_noteBook.append_page(box, i);
    }
}

void GainComponentWindow::SaveInfo()
{
}

};