#pragma once

#include <gtkmm.h>
#include <string>

namespace JSBEdit
{
	class IDrawable
	{
	public:
		virtual void Draw(const Cairo::RefPtr<Cairo::Context>& drawCont) = 0;
	};
};