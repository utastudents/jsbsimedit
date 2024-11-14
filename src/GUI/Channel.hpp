#pragma once

#include <gtkmm.h>
#include <string>
#include "IDrawable.hpp"
#include <iostream>
#include <unordered_map>
#include "IComponentCommon.hpp"
#include "ComponentSprite.hpp"
#include "GainComponent.hpp"
#include "PIDComponent.hpp"
#include "KinematicsComponent.hpp"
#include <random>

namespace DragDrop
{

	class Channel : public IDrawable
	{
	public:
		Channel(const Glib::RefPtr<Gtk::Application> &app, const std::string & channelName);
		~Channel() = default;

		bool ComponentNameExists(const std::string& name);
        void CreateDroppedComponent(ComponentType type, int x, int y);
		void Draw(const Cairo::RefPtr<Cairo::Context>& drawCont) override;
		std::string GetChannelName() const;
		void HandleClickRelease(int x, int y);
		void HandleDoubleClick(int x, int y);
		void SetChannelName(const std::string channelName);

    private:
		//Member Functions
		std::string createName(ComponentType type);
		void addDefaultComponent(ComponentType type, const std::string& name);

		//Member Variables
		std::string m_channelName {};
        std::unordered_map<std::string, IComponentCommon*> m_components {};
		std::unordered_map<std::string, ComponentSprite> m_spriteComponents{};
		Glib::RefPtr<Gtk::Application> m_appRef;

	};

};