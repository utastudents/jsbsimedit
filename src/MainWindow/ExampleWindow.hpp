#pragma once

#include <gtkmm.h>
#include "ExampleTab.hpp"
#include "Systems/FlightControlDemo.hpp"


#include "inc/Subsystem.hpp"


namespace JSBEdit
{

	class ExampleWindow : public Gtk::Window
	{
	public:
		ExampleWindow(const Glib::RefPtr<Gtk::Application> &app);
		~ExampleWindow() = default;
 
	protected:
		// Signal handlers:
		bool load_stack(const Glib::RefPtr<Gtk::Application> &app);
		void on_menu_file_files_dialog();
		void on_menu_file_quit();
		void on_menu_file_new();
		void on_menu_file_save(); //save


		void on_dialog_finish(Glib::RefPtr<Gio::AsyncResult> &result);
        void on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num);

		// Child widgets:
		Gtk::Box m_Box;
		Gtk::Stack m_stack{};
		Gtk::StackSwitcher m_stackSwitcher{};
		ExampleTab m_tab1;
		ExampleTab m_tab2;
		DragDrop::FlightControlDemo m_fcDemo;

		Glib::RefPtr<Gtk::Builder> m_refBuilder;
		Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;

		Glib::RefPtr<Gtk::RecentManager> m_refRecentManager;
		Glib::RefPtr<Gtk::FileDialog> m_refFileDialog;


         Gtk::Notebook* m_Notebook {nullptr};

        // Subsystems
        std::vector<Subsystem*> m_Subsystems;

	};

};
