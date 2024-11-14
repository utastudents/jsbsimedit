#include "ClickBox.hpp"

namespace DragDrop
{

ClickBox::ClickBox(int x, int y, int width, int height)
    : m_x(x), m_y(y), m_width(width), m_height(height)
{
}

bool ClickBox::ContainsPoint(int x, int y) const
{
    //This was a fun memory exercize
    bool withinXBounds = ((m_x + m_width) >= x && (m_x <= x));
    bool withinYBounds = ((m_y + m_height) >= y && (m_y <= y));
    return (withinXBounds && withinYBounds);
}

std::pair<int, int> ClickBox::GetBounds() const
{
    return std::pair<int, int>(m_width, m_height);
}

std::pair<int, int> ClickBox::GetPosition() const
{
    return std::pair<int, int>(m_x, m_y);
}

void ClickBox::SetBounds(int width, int height)
{
    m_width = width;
    m_height = height;
}

void ClickBox::SetPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

};