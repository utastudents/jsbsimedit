#include "DeadbandComponent.hpp"

namespace DragDrop{

DeadbandComponent::DeadbandComponent(const std::string& name)
    : IComponentCommon(name, ComponentType::DEADBAND)
{
}

void DeadbandComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
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

void DeadbandComponent::CreateCommonTab(Gtk::Notebook& note)
{                                       
  //Tabs contents in the box
  Gtk::Box tabContainer{};
  tabContainer.set_vexpand(true);
  tabContainer.set_hexpand(true);

  //Make grid
  Gtk::Grid g{};
  //Name layout.
  
  //the grid size is 11x9, where it starts from 0 
  g.set_margin_top(25);
  g.set_hexpand(true);
  g.set_vexpand(true);

  Gtk::Label width{"Width: "};
  Gtk::Label gain{"Gain: "};

  m_widthEntry = Glib::RefPtr<Gtk::Entry>(new Gtk::Entry);
  m_widthEntry->set_text(std::to_string(WIDTH));
  
  g.attach(width,0,1);
  g.attach(*m_widthEntry,1,1);


  m_gainEntry = Glib::RefPtr<Gtk::Entry>(new Gtk::Entry);
  m_gainEntry->set_text(std::to_string(GAIN));

  g.attach(gain,0,2);
  g.attach(*m_gainEntry,1,2);
  
  
  m_acceptButton = Glib::RefPtr<Gtk::Button>(new Gtk::Button{"Accept"});
  m_acceptButton->signal_clicked().connect(sigc::mem_fun(*this, &DeadbandComponent::SaveVariableChanges), false);
  m_cancelButton = Glib::RefPtr<Gtk::Button>(new Gtk::Button{"Cancel"});
  m_cancelButton->signal_clicked().connect(sigc::mem_fun(*this, &DeadbandComponent::DeleteWidgetData), false);
  
  g.attach(*m_acceptButton,0,7);
  g.attach(*m_cancelButton,1,7);
  
  m_acceptButton->set_margin_top(20); // Adds spacing above the Accept button
  m_cancelButton->set_margin_top(20);

  //Add grid to box
  tabContainer.append(g);
  //Add tab to notebook
  note.append_page(tabContainer, "Deadband");
}

void DeadbandComponent::SaveVariableChanges()
{
  //Close up
  DeleteWidgetData();
}

void DeadbandComponent::DeleteWidgetData()
{
  if(m_acceptButton)
    m_acceptButton.reset();
  if(m_cancelButton)
    m_cancelButton.reset();
  if(m_window)
  {
    m_window->close();
    m_window.reset();
  }
}

};