#include "PIDComponent.hpp"

namespace JSBEdit{

PIDComponent::PIDComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type)
{
}

void PIDComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
    //create the window
    m_window = Glib::RefPtr<Gtk::Window>(new Gtk::Window());
    m_window->set_size_request(300, 400);
    m_window->set_title(this->m_componentName);
    //Makes its so you can't interact with other windows but this
    m_window->set_modal(true);

    //Contains window contents..
    Gtk::Box windowContainer{};
    windowContainer.set_vexpand(true);
    windowContainer.set_hexpand(true);
    //Notebook for our tabs
    Gtk::Notebook noteBook{};
    CreateCommonTab(noteBook); //Make commontab
    windowContainer.append(noteBook);
    
    //Add window container, then show the window
    m_window->set_child(windowContainer);
    app->add_window(*m_window);
    m_window->show();
}

void PIDComponent::CreateCommonTab(Gtk::Notebook& note)
{                                       
  //Tabs contents in the box
  Gtk::Box tabContainer{};
  tabContainer.set_vexpand(true);
  tabContainer.set_hexpand(true);
  //Made a grid to go in the box
  Gtk::Grid g{};
  //Name layout.

  g.set_row_spacing(10);
  g.set_column_spacing(15);


  Gtk::Label nameLabel{"KP:"};
  Gtk::Entry nameEntry{};

  Gtk::Label nameLabel1{"KI:"};
  Gtk::Entry nameEntry1{};

  Gtk::Label nameLabel2{"KD:"};
  Gtk::Entry nameEntry2{};

  Gtk::Label nameLabel3{"Trigger:"};
  Gtk::Entry nameEntry3{};


//==========================================================================
  auto check_button = Gtk::make_managed<Gtk::CheckButton>("Inverted Input");
  g.attach(*check_button, 1,5);
  Gtk::Label nameLabel4{"Input: "};
  g.attach(nameLabel4, 0,4);

//===================================================================================

  g.attach(nameLabel,0,0);// Note: (Row, Column)
  g.attach(nameEntry,1,0);

  g.attach(nameLabel1,0,1);
  g.attach(nameEntry1,1,1);

  g.attach(nameLabel2,0,2);
  g.attach(nameEntry2,1,2);

  g.attach(nameLabel3,0,3);
  g.attach(nameEntry3,1,3);


  //Add grid to box
  tabContainer.append(g);
  //Add tab to notebook
  note.append_page(tabContainer, "PID");
}

};