#include "SummerComponentWindow.hpp"

namespace DragDrop
{
SummerComponentWindow::SummerComponentWindow(std::shared_ptr<IComponentCommon> comp, 
    std::shared_ptr<std::set<std::string>> setOfNames)
        : ComponentWindowCommon(comp, setOfNames)
{
    CreateCommonTab();
    Summer();
    positiveToggled();
    negativeToggled();
    AddInput();
    RemoveInput();
}

void SummerComponentWindow::Summer()
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

  // The list will be filled if any input was previously saved
  //listInput = savedInput;

  // the TextBuffer plays the role as the communicator
  textBuffer = Gtk::TextBuffer::create(); 
  textBox.set_buffer(textBuffer);
  textBox.set_editable(false);// <= might become useful later for XML implementation!
  textBox.set_vexpand(true);
  textBox.set_hexpand(true);

  g.attach(textBox,0,1,2,5);

  positive.signal_toggled().connect(sigc::mem_fun(*this, &SummerComponentWindow::positiveToggled));
 
  negative.signal_toggled().connect(sigc::mem_fun(*this, &SummerComponentWindow::negativeToggled));

  g.attach(positive,0,5);
  g.attach(negative,1,5);

  Gtk::Button buttonAdd{"Add"};
  buttonAdd.signal_clicked().connect(sigc::mem_fun(*this, &SummerComponentWindow::AddInput), false);

  Gtk::Button buttonRemove{"Remove"};
  buttonRemove.signal_clicked().connect(sigc::mem_fun(*this, &SummerComponentWindow::RemoveInput), false);

  g.attach(buttonAdd,0,7);
  g.attach(buttonRemove,1,7);

  m_noteBook.append_page(g, "Summer");
  
}

void SummerComponentWindow::positiveToggled()
{
  if (positive.get_active())
  {
    negative.set_active(false); // Uncheck the other button, nothing crazy
  }
}

void SummerComponentWindow::negativeToggled()
{
  if (negative.get_active())
  {
    positive.set_active(false);
  }
}

void SummerComponentWindow::AddInput() {
    // Add selected type to list
    if (positive.get_active()) {
        listInput.push_back("positive(+)");
    } else if (negative.get_active()) {
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
void SummerComponentWindow::RemoveInput(){
    if (!listInput.empty()) {
        listInput.pop_back();
        textBuffer->set_text("");
        for (const auto& input : listInput) {
            textBuffer->insert_at_cursor(input + "\n");
        }
    }
}

void SummerComponentWindow::SaveInfo()
{
}

};