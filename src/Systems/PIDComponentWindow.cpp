#include "PIDComponentWindow.hpp"

namespace DragDrop
{
PIDComponentWindow::PIDComponentWindow(std::shared_ptr<IComponentCommon> comp, 
    std::shared_ptr<std::set<std::string>> setOfNames)
        : ComponentWindowCommon(comp, setOfNames)
{
    CreateCommonTab();
    Pid();
}

void PIDComponentWindow::Pid()
{
  // This box is used to Scroll and contain the grid
  Gtk::Box ContainAll;
  ContainAll.set_vexpand(true);
  ContainAll.set_hexpand(true);
  
  Gtk::Grid g{};
  g.set_margin_top(15);
  g.set_hexpand(true);
  g.set_vexpand(true);

  // === KP 
  Gtk::Label kplabel{"KP:"};
  Gtk::Entry kpEntry;
  g.attach(kplabel,0,1);
  g.attach(kpEntry,1,1);

  kplabel.set_margin_bottom(10);
  kpEntry.set_margin_bottom(10);

  // === KI
  Gtk::Label kilabel{"KI:"};
  Gtk::Entry kiEntry;
  g.attach(kilabel,0,2);
  g.attach(kiEntry,1,2);

  kilabel.set_margin_bottom(10);
  kiEntry.set_margin_bottom(10);

  // === KD
  Gtk::Label kdlabel{"KD:"};
  Gtk::Entry kdEntry;
  g.attach(kdlabel,0,3);
  g.attach(kdEntry,1,3);

  kdlabel.set_margin_bottom(10);
  kdEntry.set_margin_bottom(10);

  // === Trigger 
  Gtk::Label Trilabel{"Trigger: "};
  Gtk::Entry trigEntry;
  g.attach(Trilabel,0,4);
  g.attach(trigEntry,1,4);

  Trilabel.set_margin_bottom(20);
  trigEntry.set_margin_bottom(20);

  // === Inverted Logic 
  Gtk::Label invertLabel{"Input: "};
  //Handles the click button from check mark to not a checkmark
  Gtk::CheckButton m_invertButton{"invert input"};
  m_invertButton.set_active(InputInverted);
  m_invertButton.signal_toggled().connect(sigc::mem_fun(*this, &PIDComponentWindow::HandleInvertLogic), false);
  
  g.attach(invertLabel, 0,5);
  g.attach(m_invertButton, 1,5);

  m_noteBook.append_page(g, "Pid");
}

void PIDComponentWindow::HandleInvertLogic()
{
}

void PIDComponentWindow::SaveInfo()
{
}

};