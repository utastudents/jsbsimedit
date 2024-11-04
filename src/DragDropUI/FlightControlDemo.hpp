#pragma once

#include <gtkmm.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "IComponentCommon.hpp"
#include "PIDComponent.hpp"
#include "ChannelCanvas.hpp"


namespace JSBEdit
{

	typedef	std::vector<IComponentCommon*> ComponentChannel;

	class FlightControlDemo : public Gtk::Box
	{
	public:
		FlightControlDemo(const Glib::RefPtr<Gtk::Application> &app);
		~FlightControlDemo() = default;

	private:
		// Signal handlers
		Glib::RefPtr<Gdk::ContentProvider> SetDragData(int data);

		ChannelCanvas m_canvas;
		Glib::RefPtr<Gtk::Builder> m_refBuilder;
		std::unordered_map<std::string, ComponentChannel> m_componentChannels{};

	};

};