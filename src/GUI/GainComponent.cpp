#include "GainComponent.hpp"

namespace JSBEdit{

GainComponent::GainComponent(const std::string &name, ComponentType &type)
    : IComponentCommon(name, type)
{
}

void GainComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
    
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

void GainComponent::CreateCommonTab(Gtk::Notebook& note)
{
  //Tabs contents in the box
  Gtk::Box tabContainer{};
  tabContainer.set_vexpand(true);
  tabContainer.set_hexpand(true);
  //Made a grid to go in the box
  Gtk::Grid g{};
  //Name layout.
  Gtk::Label nameLabel{"Name:"};
  Gtk::Entry nameEntry{};
  nameEntry.set_text(m_componentName);
  //Type dropdown box
  //Gtk::Label typeLabel{"Component Type:"};

  //Gtk::Label l{"testingggg"};
  g.attach(nameLabel,1,1);
  g.attach(nameEntry,1,2);



  //Add grid to box
  tabContainer.append(g);
  //Add tab to notebook
  note.append_page(tabContainer, "Common");
}

};