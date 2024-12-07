#include "Connection.hpp"

namespace DragDrop
{

Connection::Connection(int inputUID, int outputUID)
    : m_inputUID(inputUID), m_outputUID(outputUID)
{
}

bool Connection::ContainsUID(int UID) const
{
    return (UID == m_inputUID || UID == m_outputUID);
}

bool Connection::ContainsPoint(const std::unordered_map<int, ComponentSprite>& spriteSet)
{
    return false;
}
		
void Connection::Draw(const Cairo::RefPtr<Cairo::Context>& drawCont, const std::unordered_map<int, ComponentSprite>& spriteSet)
{
    drawCont->set_line_width(2);
    drawCont->set_source_rgb(0,0,0);
    auto startLoc = spriteSet.at(m_outputUID).GetInputBoxPosition();
    auto endLoc = spriteSet.at(m_inputUID).GetOutputBoxPosition();
    drawCont->move_to(startLoc.first, startLoc.second);
    drawCont->line_to(endLoc.first, endLoc.second);
    drawCont->stroke();
}
    
int Connection::GetInputUID() const
{
    return m_inputUID;
}

int Connection::GetOutputUID() const
{
    return m_outputUID;
}

};