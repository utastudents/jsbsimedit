#include "SwitchComponentWindow.hpp"

namespace DragDrop
{

SwitchComponentWindow::SwitchComponentWindow(std::shared_ptr<IComponentCommon> comp, 
    std::shared_ptr<std::set<std::string>> setOfNames)
        : ComponentWindowCommon(comp, setOfNames)
{
    CreateCommonTab();
    Switch();
}

void SwitchComponentWindow::Switch()
{
  Gtk::Grid g{};
  //Name layout.
  
  //the grid size is 11x9, where it starts from 0 
  g.set_margin_top(75);
  g.set_margin_start(50);
  g.set_hexpand(true);
  g.set_vexpand(true);

  Gtk::Label width{"Width: "};
  Gtk::Entry m_widthEntry;

  width.set_margin_bottom(15); 
  m_widthEntry.set_margin_bottom(15); 

  g.attach(width,0,1);
  g.attach(m_widthEntry,1,1);

  Gtk::Label gain{"Gain: "};
  Gtk::Entry m_gainEntry;

  g.attach(gain,0,2);
  g.attach(m_gainEntry,1,2);

  m_noteBook.append_page(g, "Switch");
}

void SwitchComponentWindow::SaveInfo()
{
}

};