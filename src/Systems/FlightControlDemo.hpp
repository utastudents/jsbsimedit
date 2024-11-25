#pragma once

#include <gtkmm.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "Systems/ChannelCanvas.hpp"
#include "inc/XML_api.hpp"

namespace DragDrop
{

	class FlightControlDemo : public Gtk::Box
	{
	public:
		FlightControlDemo(const Glib::RefPtr<Gtk::Application> &app, const std::string& systemName);
		~FlightControlDemo() = default;

        void CreateNewTab(const std::string& name);
		void LoadXMLData();

	private:
		// Signal handlers
		Glib::RefPtr<Gdk::ContentProvider> SetDragData(int data);
		void on_notebook_switch_page(Gtk::Widget* wid, guint page_num);

		//Member vars
		ChannelCanvas m_canvas;
		Glib::RefPtr<Gtk::Builder> m_refBuilder;
		std::string m_systemName;
		Gtk::Notebook m_notebook;

	};

};
