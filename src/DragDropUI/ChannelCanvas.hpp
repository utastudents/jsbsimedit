#pragma once

#include <gtkmm.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "ComponentSprite.hpp"
#include "Channel.hpp"

namespace JSBEdit
{

	class ChannelCanvas : public Gtk::DrawingArea
	{
	public:
		ChannelCanvas(const Glib::RefPtr<Gtk::Application> &app);
		~ChannelCanvas();

		const std::string GetCurrentChannelName() const;
		void SetCurrentChannelName(const std::string& channelName);

		void Draw(const Cairo::RefPtr<Cairo::Context> &drawCont, int width, int height);
		bool OnDragEnd(const Glib::ValueBase& value, double x, double y);

	private:
		Glib::RefPtr<Gtk::Builder> m_refBuilder;
		std::string m_currentChannel {};
		std::unordered_map<std::string, Channel> m_channels{};
	};

};