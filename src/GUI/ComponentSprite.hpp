#pragma once

#include <gtkmm.h>
#include <string>
#include "IDrawable.hpp"
#include <iostream>
#include <vector>
#include "ComponentTypeEnum.hpp"

namespace JSBEdit
{

	class ComponentSprite : public IDrawable
	{
	public:
	//TODO static load the pixel buffs for each comp type..
		ComponentSprite(const ComponentType& comp = ComponentType::Actuator, int x = 0, int y = 0);
		~ComponentSprite() = default;

		void Draw(const Cairo::RefPtr<Cairo::Context>& drawCont) override;
		std::pair<int, int> GetBounds() const;
		ComponentType GetComponentType() const;
		std::pair<int, int> GetPosition() const;
		void SetBounds(int width, int height);
		void SetComponentType(const ComponentType& compType);
		void SetPosition(int x, int y);

		static void LoadSpriteComponents();

    private:
		int m_x = 0;
		int m_y = 0;
		int	m_width = 16;
		int m_height = 16;
		int m_fontSize = 8;
		ComponentType m_componentType {ComponentType::ACTUATOR};
		
		static std::vector<Glib::RefPtr<Gdk::Pixbuf>> spriteTable;
	};

};