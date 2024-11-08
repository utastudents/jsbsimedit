/* gtkmm example Copyright (C) 2016 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "exampleappwindow.h"
#include <iostream>
#include <stdexcept>
#include <set>


#include "Aerodynamics/AeroDynamicsSubsystem.hpp"
#include "BuoyantForces/BuoyantForcesSubsystem.hpp"
#include "Metrics/MetricsSubsystem.hpp"
#include "GeneralInformation/GeneralInformationSubsystem.hpp"


ExampleAppWindow::ExampleAppWindow(BaseObjectType* cobject,
  const Glib::RefPtr<Gtk::Builder>& refBuilder)
: Gtk::ApplicationWindow(cobject),
  m_refBuilder(refBuilder)
{
  // Get widgets from the Gtk::Builder file.
  m_stack = m_refBuilder->get_widget<Gtk::Stack>("stack");
  if (!m_stack)
    throw std::runtime_error("No \"stack\" object in window.ui");

  m_search = m_refBuilder->get_widget<Gtk::ToggleButton>("search");
  if (!m_search)
    throw std::runtime_error("No \"search\" object in window.ui");

  m_searchbar = m_refBuilder->get_widget<Gtk::SearchBar>("searchbar");
  if (!m_searchbar)
    throw std::runtime_error("No \"searchbar\" object in window.ui");

#if HAS_SEARCH_ENTRY2
  m_searchentry = m_refBuilder->get_widget<Gtk::SearchEntry2>("searchentry");
#else
  m_searchentry = m_refBuilder->get_widget<Gtk::SearchEntry>("searchentry");
#endif
  if (!m_searchentry)
    throw std::runtime_error("No \"searchentry\" object in window.ui");

  m_gears = m_refBuilder->get_widget<Gtk::MenuButton>("gears");
  if (!m_gears)
    throw std::runtime_error("No \"gears\" object in window.ui");

  m_sidebar = m_refBuilder->get_widget<Gtk::Revealer>("sidebar");
  if (!m_sidebar)
    throw std::runtime_error("No \"sidebar\" object in window.ui");

  m_words = m_refBuilder->get_widget<Gtk::ListBox>("words");
  if (!m_words)
    throw std::runtime_error("No \"words\" object in window.ui");

  m_lines = m_refBuilder->get_widget<Gtk::Label>("lines");
  if (!m_lines)
    throw std::runtime_error("No \"lines\" object in window.ui");

  m_lines_label = m_refBuilder->get_widget<Gtk::Label>("lines_label");
  if (!m_lines_label)
    throw std::runtime_error("No \"lines_label\" object in window.ui");

  // Bind settings.
  m_settings = Gio::Settings::create("org.gtkmm.exampleapp");
  m_settings->bind("transition", m_stack->property_transition_type());
  m_settings->bind("show-words", m_sidebar->property_reveal_child());

  // Bind properties of the search button to the search bar.
  m_binding_search_enabled = Glib::Binding::bind_property(m_search->property_active(),
    m_searchbar->property_search_mode_enabled(), Glib::Binding::Flags::BIDIRECTIONAL);

  // Connect signal handlers.
  m_searchentry->signal_search_changed().connect(
    sigc::mem_fun(*this, &ExampleAppWindow::on_search_text_changed));
  m_stack->property_visible_child().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleAppWindow::on_visible_child_changed));
  m_sidebar->property_reveal_child().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleAppWindow::on_reveal_child_changed));

  // Connect the menu to the MenuButton m_gears, and bind the show-words setting
  // to the win.show-words action and the "Words" menu item.
  // (The connection between action and menu item is specified in gears_menu.ui.)
  auto menu_builder = Gtk::Builder::create_from_resource("/org/gtkmm/exampleapp/gears_menu.ui");
  auto menu = menu_builder->get_object<Gio::MenuModel>("menu");
  if (!menu)
    throw std::runtime_error("No \"menu\" object in gears_menu.ui");

  m_gears->set_menu_model(menu);
  add_action(m_settings->create_action("show-words"));

  // Bind the "visible" property of m_lines to the win.show-lines action, to
  // the "Lines" menu item and to the "visible" property of m_lines_label.
  add_action(Gio::PropertyAction::create("show-lines", m_lines->property_visible()));
  m_binding_lines_visible = Glib::Binding::bind_property(m_lines->property_visible(),
    m_lines_label->property_visible());

  // Set the window icon.
  Gtk::IconTheme::get_for_display(get_display())->add_resource_path("/org/gtkmm/exampleapp");
  set_icon_name("exampleapp");

  // may need to move this to be a class member variable.
  m_Notebook = new Gtk::Notebook();
  set_child(*m_Notebook);

  m_Notebook->set_margin(10);
  m_Notebook->set_expand();

  // create the Subsystems objects
  //    The key is the title used in the tab. 
  //    Maybe a better way to get the name, perhaps add it to Subsystem?
  m_Subsystems.push_back(new GeneralInformationSubsystem());
  m_Subsystems.push_back(new AeroDynamicsSubsystem());
  m_Subsystems.push_back(new BuoyantForcesSubsystem());
  m_Subsystems.push_back(new MetricsSubsystem());
#if 0
  Subsystem* m_AeroDynSub {nullptr};
  Subsystem* m_BouySub {nullptr};
  Subsystem* m_ExtReactSub {nullptr};
  Subsystem* m_GenInfoSub {nullptr};
  Subsystem* m_GroundReactSub {nullptr};
  Subsystem* m_InOutSub {nullptr};
  Subsystem* m_MassBalSub {nullptr};
  Subsystem* m_MetricsSub {nullptr};
  Subsystem* m_PropSub {nullptr};
#endif
  // create the gtk objects inside
  for (const auto &i : m_Subsystems)
  {
      i->Create();
  }

  // make the pages part of the notebook
  for (const auto &i : m_Subsystems)
  {
      m_Notebook->append_page(i->m_Grid,i->m_Name);
  }
  
  // connect the switch page callbook 
  m_Notebook->signal_switch_page().connect(sigc::mem_fun(*this,
              &ExampleAppWindow::on_notebook_switch_page) );

}

//static
ExampleAppWindow* ExampleAppWindow::create()
{
  // Load the Builder file and instantiate its widgets.
  auto refBuilder = Gtk::Builder::create_from_resource("/org/gtkmm/exampleapp/window.ui");

  auto window = Gtk::Builder::get_widget_derived<ExampleAppWindow>(refBuilder, "app_window");
  if (!window)
    throw std::runtime_error("No \"app_window\" object in window.ui");

  return window;
}

void ExampleAppWindow::open_file_view(const Glib::RefPtr<Gio::File>& file)
{
#if 0
  const Glib::ustring basename = file->get_basename();

  auto scrolled = Gtk::make_managed<Gtk::ScrolledWindow>();
  scrolled->set_expand(true);
  auto view = Gtk::make_managed<Gtk::TextView>();
  view->set_editable(false);
  view->set_cursor_visible(false);
  scrolled->set_child(*view);
  m_stack->add(*scrolled, basename, basename);

  auto buffer = view->get_buffer();
  try
  {
    char* contents = nullptr;
    gsize length = 0;
    
    file->load_contents(contents, length);
    buffer->set_text(contents, contents+length);
    g_free(contents);
  }
  catch (const Glib::Error& ex)
  {
    std::cout << "ExampleAppWindow::open_file_view(\"" << file->get_parse_name()
      << "\"):\n  " << ex.what() << std::endl;
    return;
  }

  auto tag = buffer->create_tag();
  m_settings->bind("font", tag->property_font());
  buffer->apply_tag(tag, buffer->begin(), buffer->end());

  m_search->set_sensitive(true);
  update_words();
  update_lines();
#endif
}

void ExampleAppWindow::on_search_text_changed()
{
#if 0
  const auto text = m_searchentry->get_text();
  if (text.empty())
    return;

  auto tab = dynamic_cast<Gtk::ScrolledWindow*>(m_stack->get_visible_child());
  if (!tab)
  {
    std::cout << "ExampleAppWindow::on_search_text_changed(): No visible child." << std::endl;
    return;
  }

  auto view = dynamic_cast<Gtk::TextView*>(tab->get_child());
  if (!view)
  {
    std::cout << "ExampleAppWindow::on_search_text_changed(): No visible text view." << std::endl;
    return;
  }

  // Very simple-minded search implementation.
  auto buffer = view->get_buffer();
  Gtk::TextIter match_start;
  Gtk::TextIter match_end;
  if (buffer->begin().forward_search(text, Gtk::TextSearchFlags::CASE_INSENSITIVE,
      match_start, match_end))
  {
    buffer->select_range(match_start, match_end);
    view->scroll_to(match_start);
  }
#endif
}

void ExampleAppWindow::on_visible_child_changed()
{
  m_searchbar->set_search_mode(false);
  update_words();
  update_lines();  
}

void ExampleAppWindow::on_find_word(const Gtk::Button* button)
{
  m_searchentry->set_text(button->get_label());
}

void ExampleAppWindow::on_reveal_child_changed()
{
  update_words();
}

void ExampleAppWindow::update_words()
{
#if 0
  auto tab = dynamic_cast<Gtk::ScrolledWindow*>(m_stack->get_visible_child());
  if (!tab)
    return;

  auto view = dynamic_cast<Gtk::TextView*>(tab->get_child());
  if (!view)
  {
    std::cout << "ExampleAppWindow::update_words(): No visible text view." << std::endl;
    return;
  }
  auto buffer = view->get_buffer();

  // Find all words in the text buffer.
  std::set<Glib::ustring> words;
  auto start = buffer->begin();
  Gtk::TextIter end;
  while (start)
  {
    while (start && !start.starts_word())
      ++start;

    if (!start)
      break;

    end = start;
    end.forward_word_end();
    if (start == end)
      break;

    auto word = buffer->get_text(start, end, false);
    words.insert(word.lowercase());
    start = end;
  }

  // Remove old children from the ListBox.
  while (auto child = m_words->get_first_child())
    m_words->remove(*child);

  // Add new child buttons, one per unique word.
  for (const auto& word : words)
  {
    auto row = Gtk::make_managed<Gtk::Button>(word);
    row->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
      &ExampleAppWindow::on_find_word), row));
    m_words->append(*row);
  }
#endif
}

void ExampleAppWindow::update_lines()
{
#if 0
  auto tab = dynamic_cast<Gtk::ScrolledWindow*>(m_stack->get_visible_child());
  if (!tab)
    return;

  auto view = dynamic_cast<Gtk::TextView*>(tab->get_child());
  if (!view)
  {
    std::cout << "ExampleAppWindow::update_lines(): No visible text view." << std::endl;
    return;
  }
  auto buffer = view->get_buffer();

  int count = 0;
  auto iter = buffer->begin();
  while (iter)
  {
    ++count;
    if (!iter.forward_line())
      break;
  }
  m_lines->set_text(Glib::ustring::format(count));
#endif
}

void ExampleAppWindow::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num)
{
  std::cout << "Switched to tab with index " << page_num << std::endl;

  //You can also use m_Notebook.get_current_page() to get this index.
}

