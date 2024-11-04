#pragma once

#include <gtkmm.h>
#include <string>
#include "IDrawable.hpp"
#include <iostream>
#include <unordered_map>
#include "IComponentCommon.hpp"
#include "ComponentSprite.hpp"
#include <random>

namespace JSBEdit
{

	class Channel : public IDrawable
	{
	public:
		Channel(const std::string& channelName);
		~Channel() = default;

		bool ComponentNameExists(const std::string& name);
        void CreateDroppedComponent(ComponentType type, int x, int y);
		void Draw(const Cairo::RefPtr<Cairo::Context>& drawCont) override;
		std::string GetChannelName() const;
		void SetChannelName(const std::string channelName);

    private:
		//Member Functions
		std::string createName(ComponentType type);

		//Member Variables
		std::string m_channelName {};
        std::unordered_map<std::string, IComponentCommon*> m_components {};
		std::unordered_map<std::string, ComponentSprite> m_spriteComponents{};

	};

};