#pragma once

#include <gtkmm.h>

namespace JSBEdit
{

	class ExampleTab : public Gtk::Box
	{
	public:
		ExampleTab(const Glib::RefPtr<Gtk::Application> &app, const std::string& buttonName);
		~ExampleTab() override;

	protected:
		// Signal handlers:
        //NONE
		Gtk::Label l;
		Glib::RefPtr<Gtk::Builder> m_refBuilder;
	};

};