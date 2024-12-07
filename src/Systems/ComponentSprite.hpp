#pragma once

#include <gtkmm.h>
#include <string>
#include "IDrawable.hpp"
#include <iostream>
#include <vector>
#include "ComponentTypeEnum.hpp"
#include "ClickBox.hpp"

namespace DragDrop
{
	/*
		Warning to those who edit, there are magic numbers thrown around here
		Mostly because i was in a rush, constants are 32x32 for the sprite size
		2x2 for the input/output box.
		Theres also conversions from centerpoint position to top left position being the position
		This is because GTK wants to draw top left, but I feel that center position helped
		But probably caused more harm then good. This also makes resizing a pain due to the assumptions above.
		Static pixbuf is to load the image files once and not per instance of this class.
	*/

	class ComponentSprite : public IDrawable
	{
	public:
		ComponentSprite(const ComponentType& comp = ComponentType::ACTUATOR, int x = 0, int y = 0);
		~ComponentSprite() = default;

		bool ContainsPoint(int x, int y);
		void Draw(const Cairo::RefPtr<Cairo::Context>& drawCont) override;
		bool IsInputBoxClicked(int x, int y) const;
		bool IsOutputBoxClicked(int x, int y) const;
		std::pair<int, int> GetBounds() const;
		ComponentType GetComponentType() const;
		std::pair<int, int> GetInputBoxPosition() const;
		std::pair<int, int> GetOutputBoxPosition() const;
		std::pair<int, int> GetPosition() const;
		void SetComponentType(const ComponentType& compType);
		void SetPosition(int x, int y);

		static void LoadSpriteComponents();

    private:
		ClickBox m_spriteBox{};
		ClickBox m_inputBox{};
		ClickBox m_outputBox{};

		bool m_selected = false;
		ComponentType m_componentType {ComponentType::ACTUATOR};
		
		static std::vector<Glib::RefPtr<Gdk::Pixbuf>> spriteTable;
	};

};
