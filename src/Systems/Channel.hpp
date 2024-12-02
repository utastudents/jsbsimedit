#pragma once

#include <gtkmm.h>
#include <string>
#include "IDrawable.hpp"
#include <iostream>
#include <unordered_map>
#include "ComponentSprite.hpp"
#include "inc/XML_api.hpp"
#include "DragStateEnum.hpp"

#include "IComponentCommon.hpp"
#include "GainComponent.hpp"
#include "PIDComponent.hpp"
#include "KinematicsComponent.hpp"
#include "SummerComponent.hpp"
#include "DeadbandComponent.hpp"
#include "FilterComponent.hpp"

#include "PIDComponentWindow.hpp"
#include "GainComponentWindow.hpp"
#include "KinematicsComponentWindow.hpp"
#include "DeadbandComponentWindow.hpp"
#include "SummerComponentWindow.hpp"
#include "FilterComponentWindow.hpp"

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
		void LoadFromXmlFile(JSBEdit::XMLNode& node);
		void SetChannelName(const std::string channelName);
		void OnDragBegin(int x, int y);
		void OnDragUpdate(int x, int y);
		void OnDragEnd(int x, int y);

    private:
		//Member Functions
		std::shared_ptr<IComponentCommon> createComponentFromType(ComponentType type, const std::string& name);
		std::string createName(ComponentType type);
		int generateUniqueId();
		void populateStringComponentMap();

		//Member Variables=================
		//Component/Unique id/Sprite/name relational maps and sets
		std::string m_channelName {};
        std::unordered_map<int, std::shared_ptr<IComponentCommon>> m_components {};
		std::unordered_map<int, ComponentSprite> m_spriteComponents{};
		std::unordered_map<std::string, ComponentType> m_stringToComponentMap{};
		std::shared_ptr<std::set<std::string>> m_componentNameSet{};
		std::set<int> m_uniqueIDSet{};
		
		//Dragging and Selection related
		DragState m_dragState = DragState::NONE;
		std::pair<int, int> m_currentDragPos{};
		int m_selectedId {};

		//Random number generation vars
		std::mt19937 m_rng{ std::random_device{}() };
		std::uniform_int_distribution<> m_distribuition{1,1000};
		
		//GTK app related
		Glib::RefPtr<Gtk::Application> m_appRef;
		std::shared_ptr<Gtk::Window> m_winPtr;

	};

};