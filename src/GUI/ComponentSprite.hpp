#pragma once

#include <gtkmm.h>
#include <string>
#include "IDrawable.hpp"
#include <iostream>
#include <vector>
//TODO: MOVE ENUM OUT OF HERE
#include "IComponentCommon.hpp"

namespace JSBEdit
{

	class ComponentSprite : public IDrawable
	{
	public:
	//TODO static load the pixel buffs for each comp type..
		ComponentSprite() = default;
		~ComponentSprite() = default;

		void Draw(const Cairo::RefPtr<Cairo::Context>& drawCont) override;
		const std::pair<int, int> GetBounds() const;
		const ComponentType GetComponentType() const;
		const std::pair<int, int> GetPosition() const;
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