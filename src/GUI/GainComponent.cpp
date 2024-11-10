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
  m_nameEntry = Glib::RefPtr<Gtk::Entry>(new Gtk::Entry{});
  m_nameEntry->set_text(m_componentName);
  //Type label
  Gtk::Label typeLabel{"Component Type:" + COMPONENT_NAMES[(int)m_componentType]};
  
  //Max entrys and labels
  Gtk::Label maxLabel{"Max:"};
  m_maxEntry = Glib::RefPtr<Gtk::Entry>(new Gtk::Entry);
  m_maxEntry->set_text(std::to_string(MaxClip));
  //Disable when check box is clicked
  m_maxEntry->set_sensitive(IsClipperEnabled);
  
  //Min entrys and labels
  Gtk::Label minLabel{"Min:"};
  m_minEntry = Glib::RefPtr<Gtk::Entry>(new Gtk::Entry);
  m_minEntry->set_text(std::to_string(MinClip));
  //Disable when check box is clicked
  m_minEntry->set_sensitive(IsClipperEnabled);

  //Clipper button and label
  Gtk::Label clipperLabel{"Clipper:"};
  m_clipperButton = Glib::RefPtr<Gtk::CheckButton>(new Gtk::CheckButton{});
  m_clipperButton->set_active(IsClipperEnabled);
  m_clipperButton->signal_toggled().connect(sigc::mem_fun(*this, &GainComponent::HandleClipperLogic), false);

  //Accept/Cancel button
  m_acceptButton = Glib::RefPtr<Gtk::Button>(new Gtk::Button{"Accept"});
  m_acceptButton->signal_clicked().connect(sigc::mem_fun(*this, &GainComponent::SaveVariableChanges), false);
  m_cancelButton = Glib::RefPtr<Gtk::Button>(new Gtk::Button{"Cancel"});
  m_cancelButton->signal_clicked().connect(sigc::mem_fun(*this, &GainComponent::DeleteWidgetData), false);


  //Attaching all the widgets to the grid
  g.attach(nameLabel,1,1);
  g.attach(*m_nameEntry,1,2);
  g.attach(typeLabel,1,3);
  g.attach(clipperLabel,1,4);
  g.attach(*m_clipperButton,2,4);
  g.attach(maxLabel, 1, 5);
  g.attach(*m_maxEntry, 2, 5);
  g.attach(minLabel, 1, 6);
  g.attach(*m_minEntry, 2, 6);
  g.attach(*m_acceptButton,1,7);
  g.attach(*m_cancelButton,2,7);

  //Add grid to box
  tabContainer.append(g);
  //Add tab to notebook
  note.append_page(tabContainer, "Common");
}

void GainComponent::HandleClipperLogic()
{
  bool status = m_clipperButton->get_active();
  m_maxEntry->set_sensitive(status);
  m_minEntry->set_sensitive(status);
}

void GainComponent::SaveVariableChanges()
{
  //Set the component name if not empty
  auto nameEntered = m_nameEntry->get_text();
  if(!nameEntered.empty())
    m_componentName = nameEntered;

  //Clipper max next, convert string to float
  float inpFloat;
  try{ 
    inpFloat = std::stof(m_maxEntry->get_text());
    MaxClip = inpFloat;
  }
  catch(...){} //Do nothin on the throw
  
  //Min float next..
  try{ 
    inpFloat = std::stof(m_minEntry->get_text());
    MinClip = inpFloat;
  }
  catch(...){} ///Do nothin on the throw

  //Set the value of the clipper check
  IsClipperEnabled = m_clipperButton->get_active();

  //Close up
  DeleteWidgetData();
}

void GainComponent::DeleteWidgetData()
{
  if(m_clipperButton)
    m_clipperButton.reset();
  if(m_maxEntry)
    m_maxEntry.reset();
  if(m_minEntry)
    m_minEntry.reset();
  if(m_nameEntry)
    m_nameEntry.reset();
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