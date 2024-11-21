#pragma once

#include <gtkmm.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "ComponentSprite.hpp"
#include "Channel.hpp"

namespace DragDrop
{

	class ChannelCanvas : public Gtk::DrawingArea
	{
	public:
		ChannelCanvas(const Glib::RefPtr<Gtk::Application> &app);
		~ChannelCanvas();

		bool CurrentChannelExists();
		const std::string GetCurrentChannelName() const;
		void SetCurrentChannelName(const std::string& channelName);

		void Draw(const Cairo::RefPtr<Cairo::Context> &drawCont, int width, int height);

		//Signal Handlers that should probably be private
		bool OnDropEnd(const Glib::ValueBase& value, double x, double y);
		void OnClickRelease(int numClick, double x, double y);
		void OnClickDown(int numClick, double x, double y);
		void OnDragBegin(double x, double y);
		void OnDragUpdate(double x, double y);
		void OnDragEnd(double x, double y);

	private:
		Glib::RefPtr<Gtk::Builder> m_refBuilder;
		Glib::RefPtr<Gtk::Application> m_refApp;
		std::string m_currentChannel {};
		std::unordered_map<std::string, Channel> m_channels{};
	};

};