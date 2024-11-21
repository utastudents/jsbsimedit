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
#include "SummerComponent.hpp"
#include "DeadbandComponent.hpp"
#include "GainComponentWindow.hpp"
#include "KinematicsComponentWindow.hpp"
#include <random>
#include <set>
#include <memory>

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
		int generateUniqueId();
		void addDefaultComponent(ComponentType type, const std::string& name, int uId);

		//Member Variables
		std::string m_channelName {};
        std::unordered_map<int, std::shared_ptr<IComponentCommon>> m_components {};
		std::unordered_map<int, ComponentSprite> m_spriteComponents{};
		std::shared_ptr<std::set<std::string>> m_componentNameSet{};
		std::set<int> m_uniqueIDSet{};
		Glib::RefPtr<Gtk::Application> m_appRef;
		std::mt19937 m_rng{ std::random_device{}() };
		std::uniform_int_distribution<> m_distribuition{1,1000};
		std::shared_ptr<Gtk::Window> m_winPtr;

	};

};