#include "KinematicsComponentWindow.hpp"

namespace DragDrop
{
KinematicsComponentWindow::KinematicsComponentWindow(std::shared_ptr<IComponentCommon> comp, 
    std::shared_ptr<std::set<std::string>> setOfNames)
        : ComponentWindowCommon(comp, setOfNames)
{
    CreateCommonTab();
    Kinematic();
}

void KinematicsComponentWindow::Kinematic()
{
  // This box is used to Scroll and contain the grid
  Gtk::Box ContainAll;
  ContainAll.set_vexpand(true);
  ContainAll.set_hexpand(true);
  
  Gtk::Grid g{};
  g.set_margin_top(15);
  g.set_hexpand(true);
  g.set_vexpand(true);


  // The scroll need a box and any other container(eg. another box, grid, etc...)
  // Box(parent) => Scroll => Grid
  Gtk::ScrolledWindow scrolled;
  scrolled.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  scrolled.set_child(g); // Grid
  ContainAll.append(scrolled); // Box

  // Making the table
  Gtk::Label Column1{"#"};
  Gtk::Label Column2{"Position"};
  Gtk::Label Column3{"Time"};
  g.attach(Column1,0,0);
  g.attach(Column2,1,0);
  g.attach(Column3,2,0);

  int row;

  for(row = 1; row < 100; row++)
  {
    // Only creates Number values
    Gtk::Label rowNum {std::to_string(row)};
    g.attach(rowNum,0,row);

    Gtk::Entry entry_pos{};
    Gtk::Entry entry_time{};
    /*
        CODE HERE TO SAVE USER INPUT
    */
    g.attach(entry_pos, 1, row);
    g.attach(entry_time, 2, row);
  }

  // Handles the click button from check mark to not a checkmark
  Gtk::CheckButton scaleButton{"input scale"}; 
  scaleButton.set_active(ScaleEnable);
  scaleButton.signal_toggled().connect(sigc::mem_fun(*this, &KinematicsComponentWindow::HandleScaleLogic), false);

  g.attach(scaleButton,0,row+1);

  m_noteBook.append_page(ContainAll, "Kinematics");

}

void KinematicsComponentWindow::HandleScaleLogic()
{
    //Do something when scale is activated
}


void KinematicsComponentWindow::SaveInfo()
{
}

};