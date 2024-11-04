#pragma once

#include <gtkmm.h>
#include "ExampleTab.hpp"
<<<<<<< HEAD
#include <DragDropUI/FlightControlDemo.hpp>
=======
#include "FlightControlDemo.hpp"
>>>>>>> b0ae439c7d59c774dedac7b91a2e4b425f79ff2f

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
		void on_dialog_finish(Glib::RefPtr<Gio::AsyncResult> &result);

		// Child widgets:
		Gtk::Box m_Box;
		Gtk::Stack m_stack{};
		Gtk::StackSwitcher m_stackSwitcher{};
		ExampleTab m_tab1;
		ExampleTab m_tab2;
		FlightControlDemo m_fcDemo;

		Glib::RefPtr<Gtk::Builder> m_refBuilder;
		Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;

		Glib::RefPtr<Gtk::RecentManager> m_refRecentManager;
		Glib::RefPtr<Gtk::FileDialog> m_refFileDialog;
	};

};