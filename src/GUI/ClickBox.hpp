#pragma once

#include <string>
#include <iostream>
#include <vector>

namespace JSBEdit
{
    //Could template this so it can be extended to floats/doubles etc..
    //But for this is fine.
	class ClickBox
	{
	public:
		ClickBox(int x = 0, int y = 0, int width = 0, int height = 0);
		~ClickBox() = default;

		bool ContainsPoint(int x, int y) const;
		std::pair<int, int> GetBounds() const;
		std::pair<int, int> GetPosition() const;
		void SetBounds(int width, int height);
		void SetPosition(int x, int y);

    private:
		int m_x = 0;
		int m_y = 0;
		int	m_width = 0;
		int m_height = 0;
	};

};