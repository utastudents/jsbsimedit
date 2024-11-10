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

  //Make grid
  Gtk::Grid g{};
  //Name layout.
  
  //the grid size is 11x9, where it starts from 0 
  g.set_row_spacing(11);
  g.set_column_spacing(9);

  //KP label and Entry =============
  Gtk::Label KPlabel{"KP:"};
  m_kpEntry = Glib::RefPtr<Gtk::Entry>(new Gtk::Entry);
  m_kpEntry->set_text(std::to_string(KP));

  g.attach(KPlabel,0,1);
  g.attach(*m_kpEntry,1,1);

  //KI label and Entry =============
  Gtk::Label KIlabel{"KI:"};
  m_kiEntry = Glib::RefPtr<Gtk::Entry>(new Gtk::Entry);
  m_kiEntry->set_text(std::to_string(KI));

  g.attach(KIlabel,0,2);
  g.attach(*m_kiEntry,1,2);

  //KD label and Entry =============
  Gtk::Label KDlabel{"KD:"};
  m_kdEntry = Glib::RefPtr<Gtk::Entry>(new Gtk::Entry);
  m_kdEntry->set_text(std::to_string(KD));

  g.attach(KDlabel,0,3);
  g.attach(*m_kdEntry,1,3);

  //Trigger label and Entry ==========
  Gtk::Label Trilabel{"Trigger:"};
  m_trigEntry = Glib::RefPtr<Gtk::Entry>(new Gtk::Entry);
  m_trigEntry->set_text(Trigger);

  g.attach(Trilabel,0,4);
  g.attach(*m_trigEntry,1,4);

  //Invert button click ===========
  Gtk::Label invertLabel{"Input: "};
  
    //Handles the click button from check mark to not a checkmark
  m_invertButton = Glib::RefPtr<Gtk::CheckButton>(new Gtk::CheckButton{"Invert Input"}); 
  m_invertButton->set_active(InputInverted);
  m_invertButton->signal_toggled().connect(sigc::mem_fun(*this, &PIDComponent::HandleInvertLogic), false);
  
  g.attach(invertLabel, 0,5);
  g.attach(*m_invertButton, 1,5);

  //Accept/Cancel button ===========
  m_acceptButton = Glib::RefPtr<Gtk::Button>(new Gtk::Button{"Accept"});
  m_acceptButton->signal_clicked().connect(sigc::mem_fun(*this, &PIDComponent::SaveVariableChanges), false);
  m_cancelButton = Glib::RefPtr<Gtk::Button>(new Gtk::Button{"Cancel"});
  m_cancelButton->signal_clicked().connect(sigc::mem_fun(*this, &PIDComponent::DeleteWidgetData), false);

  g.attach(*m_acceptButton,1,7);
  g.attach(*m_cancelButton,2,7);

  //Add grid to box
  tabContainer.append(g);
  //Add tab to notebook
  note.append_page(tabContainer, "PID");
}

//When the Inverted button is active => Do something (as of now, I have no clue what Invert does)
void PIDComponent::HandleInvertLogic()
{
  bool status = m_invertButton->get_active();
}

void PIDComponent::SaveVariableChanges()
{
  float inpFloat;
  try{ 
    inpFloat = std::stof(m_kpEntry->get_text());
    KP = inpFloat;
  }
  catch(...){}

  try{ 
    inpFloat = std::stof(m_kiEntry->get_text());
    KI = inpFloat;
  }
  catch(...){}

  try{
    inpFloat = std::stof(m_kdEntry->get_text());
    KD = inpFloat;
  }
  catch(...){}

  //Set the component trigger if not empty
  auto trigEntered = m_trigEntry->get_text();
  if(!trigEntered.empty())
    m_componentName = trigEntered;

  //Set the value of the inverted check
  InputInverted = m_invertButton->get_active();

  //Close up
  DeleteWidgetData();
}

void PIDComponent::DeleteWidgetData()
{
  if(m_invertButton)
    m_invertButton.reset();
  if(m_kpEntry)
    m_kpEntry.reset();
  if(m_kiEntry)
    m_kiEntry.reset();
  if(m_kdEntry)
    m_kdEntry.reset();
  if(m_trigEntry)
    m_trigEntry.reset();
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