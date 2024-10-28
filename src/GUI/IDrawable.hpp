#pragma once

#include <gtkmm.h>
#include <string>

namespace JSBEdit
{
	class IDrawable
	{
	public:
		virtual void Draw(Cairo::RefPtr<Cairo::Context>& drawCont) = 0;
	};
};