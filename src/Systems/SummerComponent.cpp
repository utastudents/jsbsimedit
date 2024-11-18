#include "SummerComponent.hpp"

namespace DragDrop{

SummerComponent::SummerComponent(const std::string &name)
    : IComponentCommon(name, ComponentType::SUMMER)
{
}

void SummerComponent::LoadGUI(Glib::RefPtr<Gtk::Application>& app)
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

void SummerComponent::CreateCommonTab(Gtk::Notebook& note)
{
  //Tabs contents in the box
  Gtk::Box tabContainer{};
  tabContainer.set_vexpand(true);
  tabContainer.set_hexpand(true);

  //Make grid
  Gtk::Grid g{};
  //Name layout.
  
  g.set_margin_top(15);
  g.set_row_spacing(12);
  g.set_column_spacing(10);

  Gtk::Label display{"INPUT Table:"};
  g.attach(display,0,0);

  // == This box dispays the input and output 
  Gtk::TextView textBox;
  // The list will be filled if any input was previously saved
  listInput = savedInput;
  // the TextBuffer plays the role as the communicator
  textBuffer = Gtk::TextBuffer::create(); 
  textBox.set_buffer(textBuffer);
  textBox.set_editable(false);// <= might become useful later for XML implementation!
  textBox.set_vexpand(true);
  textBox.set_hexpand(true);

  g.attach(textBox,0,1,2,5);

  m_positive = Glib::RefPtr<Gtk::CheckButton>(new Gtk::CheckButton{"Positive"});  
  m_positive->signal_toggled().connect(sigc::mem_fun(*this, &SummerComponent::positiveToggled));

  m_negative = Glib::RefPtr<Gtk::CheckButton>(new Gtk::CheckButton{"Negative"});  
  m_negative->signal_toggled().connect(sigc::mem_fun(*this, &SummerComponent::negativeToggled));

  g.attach(*m_positive,0,5);
  g.attach(*m_negative,1,5);
  //tabContainer.append(g);

  buttonAdd = Glib::RefPtr<Gtk::Button>(new Gtk::Button{"Add"});
  buttonAdd->signal_clicked().connect(sigc::mem_fun(*this, &SummerComponent::AddInput), false);

  buttonRemove = Glib::RefPtr<Gtk::Button>(new Gtk::Button{"Remove"});
  buttonRemove->signal_clicked().connect(sigc::mem_fun(*this, &SummerComponent::RemoveInput), false);

  g.attach(*buttonAdd,0,7);
  g.attach(*buttonRemove,1,7);

  m_acceptButton = Glib::RefPtr<Gtk::Button>(new Gtk::Button{"Accept"});
  m_acceptButton->signal_clicked().connect(sigc::mem_fun(*this, &SummerComponent::SaveVariableChanges), false);
  m_cancelButton = Glib::RefPtr<Gtk::Button>(new Gtk::Button{"Cancel"});
  m_cancelButton->signal_clicked().connect(sigc::mem_fun(*this, &SummerComponent::DeleteWidgetData), false);

  g.attach(*m_acceptButton,0,8);
  g.attach(*m_cancelButton,1,8);

  tabContainer.append(g);

  note.append_page(tabContainer, "Summer");
}

void SummerComponent::positiveToggled()
{
  if (m_positive->get_active())
  {
    m_negative->set_active(false); // Uncheck the other button, nothing crazy
  }
}

void SummerComponent::negativeToggled()
{
  if (m_negative->get_active())
  {
    m_positive->set_active(false);
  }
}

void SummerComponent::AddInput() {
    // Add selected type to list
    if (m_positive->get_active()) {
        listInput.push_back("positive(+)");
    } else if (m_negative->get_active()) {
        listInput.push_back("negative(-)");
    } else {
        return; // Neither button is active, do nothing
    }

    // Update text view
    
    textBuffer->set_text("");
    for (const auto& item : listInput) {
        textBuffer->insert_at_cursor(item + "\n");
    }
}
// NOTE: removes anything from the list No matter what!
void SummerComponent::RemoveInput(){
    if (!listInput.empty()) {
        listInput.pop_back();
        textBuffer->set_text("");
        for (const auto& input : listInput) {
            textBuffer->insert_at_cursor(input + "\n");
        }
    }
}

void SummerComponent::SaveVariableChanges()
{
  // The only variables to save are from the list of input(postive or negative)
  savedInput.clear();
  if(!listInput.empty()){
    savedInput = listInput;
  }

  //Close up
  DeleteWidgetData();
}

void SummerComponent::DeleteWidgetData()
{
  if(!listInput.empty())
    listInput.clear();
  if(textBuffer)
    textBuffer.reset();
  if(m_positive)
    m_positive.reset();
  if(m_negative)
    m_negative.reset();
  if(buttonAdd)
    buttonAdd.reset();
  if(buttonRemove)
    buttonRemove.reset();
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