#pragma once

#include <gtkmm.h>

namespace JSBEdit {

class ExampleWindow : public Gtk::Window
{
public:
	ExampleWindow(const Glib::RefPtr<Gtk::Application>& app);
	~ExampleWindow() override;

protected:
	//Signal handlers:
	void on_menu_file_files_dialog();
	void on_menu_file_quit();
	void on_menu_file_new();
	void on_dialog_finish(Glib::RefPtr<Gio::AsyncResult>& result);

	//Child widgets:
	Gtk::Box m_Box;

	Glib::RefPtr<Gtk::Builder> m_refBuilder;
	Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;

	Glib::RefPtr<Gtk::RecentManager> m_refRecentManager;
	Glib::RefPtr<Gtk::FileDialog> m_refFileDialog;
};

};