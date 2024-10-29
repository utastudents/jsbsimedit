#pragma once

#include <gtkmm.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "PIDComponent.hpp"
#include "ComponentSprite.hpp"

namespace JSBEdit
{
	///@brief This is a vector of components that a channel has.
	typedef	std::vector<IComponentCommon*> ComponentChannel;
	
	///@brief This is a map of component names to sprites.
	typedef	std::unordered_map<std::string, ComponentSprite> NameSpriteMap;

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
		std::unordered_map<std::string, ComponentChannel> m_componentChannels{};
        std::unordered_map<std::string, NameSpriteMap> m_spriteChannels{};
	};

};