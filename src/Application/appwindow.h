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

#ifndef GTKMM_JSBWINDOW_
#define GTKMM_JSBWINDOW_
#include <map>

#include <gtkmm.h>


#include "inc/Subsystem.hpp"  

#define HAS_SEARCH_ENTRY2 GTKMM_CHECK_VERSION(4,13,2)

class AppWindow : public Gtk::ApplicationWindow
{
public:
  AppWindow(BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder);

  static AppWindow* create();

  void open_file_view(const Glib::RefPtr<Gio::File>& file);

protected:
  // Signal handlers
  void on_search_text_changed();
  void on_visible_child_changed();
  void on_find_word(const Gtk::Button* button);
  void on_reveal_child_changed();
  void on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num);
  void update_words();
  void update_lines();

  Glib::RefPtr<Gtk::Builder> m_refBuilder;
  Glib::RefPtr<Gio::Settings> m_settings;
  Gtk::Stack* m_stack {nullptr};
  Gtk::ToggleButton* m_search {nullptr};
  Gtk::SearchBar* m_searchbar {nullptr};
#if HAS_SEARCH_ENTRY2
  Gtk::SearchEntry2* m_searchentry {nullptr};
#else
  Gtk::SearchEntry* m_searchentry {nullptr};
#endif
  Gtk::MenuButton* m_gears {nullptr};
  Gtk::Revealer* m_sidebar {nullptr};
  Gtk::ListBox* m_words {nullptr};
  Gtk::Label* m_lines {nullptr};
  Gtk::Label* m_lines_label {nullptr};
  Gtk::Notebook* m_Notebook {nullptr};
  Glib::RefPtr<Glib::Binding> m_binding_search_enabled;
  Glib::RefPtr<Glib::Binding> m_binding_lines_visible;

  // Subsystems
  std::vector<Subsystem*> m_Subsystems;
};

#endif  GTKMM_JSBWINDOW_ 
