#include "KinematicsComponent.hpp"

namespace DragDrop{

KinematicsComponent::KinematicsComponent(const std::string &name)
    : IComponentCommon(name, ComponentType::KINEMATIC), table(42)
{
}

void KinematicsComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
{
    //Load GUI here, add signal handlers and callbacks to uiBox.
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

void KinematicsComponent::CreateCommonTab(Gtk::Notebook& note)
{                                       
  //Tabs contents in the box
  Gtk::Box tabContainer;
  tabContainer.set_vexpand(true);
  tabContainer.set_hexpand(true);

  //Make grid, the hexpand allowes the scroll to work
  Gtk::Grid g{};
  g.set_hexpand(true);
  g.set_vexpand(true);

//============================== making the table
  Gtk::Label Column1{"#"};
  Gtk::Label Column2{"Position"};
  Gtk::Label Column3{"Time"};
  g.attach(Column1,0,0);
  g.attach(Column2,1,0);
  g.attach(Column3,2,0);

  int row;
  //float a =0;

  for(row = 1; row < 41; row++)
  {
    Gtk::Label rowNum {std::to_string(row)};

    m_positionEntry = Glib::RefPtr<Gtk::Entry>(new Gtk::Entry);
    m_timeEntry = Glib::RefPtr<Gtk::Entry>(new Gtk::Entry);
    
    g.attach(rowNum,0,row); // Only creates Number values
    g.attach(*m_positionEntry, 1, row);
    g.attach(*m_timeEntry, 2, row);
    /*
    SOMETHING MUST BE POITING TO USER ENTRY to SAVE USER INPUT
    a = std::stof(m_positionEntry->get_text());
    positionsHold.push_back(a);
    a = std::stof(m_timeEntry->get_text());
    timesHold.push_back(a);
    */
  }

  //============== Handles the click button from check mark to not a checkmark
  m_scaleButton = Glib::RefPtr<Gtk::CheckButton>(new Gtk::CheckButton{"input scale"}); 
  m_scaleButton->set_active(IsInputScale);
  m_scaleButton->signal_toggled().connect(sigc::mem_fun(*this, &KinematicsComponent::HandleScaleLogic), false);

  g.attach(*m_scaleButton,0,row+1);

  //Accept/Cancel button ===========
  m_acceptButton = Glib::RefPtr<Gtk::Button>(new Gtk::Button{"Accept"});
  m_acceptButton->signal_clicked().connect(sigc::mem_fun(*this, &KinematicsComponent::SaveVariableChanges), false);
  m_cancelButton = Glib::RefPtr<Gtk::Button>(new Gtk::Button{"Cancel"});
  m_cancelButton->signal_clicked().connect(sigc::mem_fun(*this, &KinematicsComponent::DeleteWidgetData), false);

  g.attach(*m_acceptButton,1,row+2);
  g.attach(*m_cancelButton,2,row+2);

  // To scroll
  Gtk::ScrolledWindow scrolled;
  scrolled.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  scrolled.set_child(g);
  tabContainer.append(scrolled);
  
  //Add grid to box
  tabContainer.append(g);
  //Add tab to notebook
  note.append_page(tabContainer, "Kinematic");
}
void KinematicsComponent::HandleScaleLogic()
{
    //Do something when scale is activated
}
void KinematicsComponent::SaveVariableChanges()
{
    /* => HOW DO I SAVE ALL USER INPUT???
  int row;
  for(row=1; row<100; row++)
  {
    if(positionsHold.empty() && timesHold.empty()){
    }
    else{
        try{
            float Position = positionsHold[row];
            float Time =timesHold[row];

            table.push_back(std::make_pair(Position,Time));
        }
        catch(...){}

    }
  }*/
  //Set the value of the inverted check
  IsInputScale = m_scaleButton->get_active();

  //Close up
  DeleteWidgetData();
}

void KinematicsComponent::DeleteWidgetData()
{
  positionsHold.clear();
  timesHold.clear();
  // One last time, wiping everything completely
  table.clear();

  if(m_timeEntry)
    m_timeEntry.reset();
  if(m_positionEntry)
    m_positionEntry.reset();
  if(m_scaleButton)
    m_scaleButton.reset();
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