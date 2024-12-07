#pragma once
#include <gtkmm.h>
#include <unordered_map>
#include "ComponentSprite.hpp"

namespace DragDrop
{

    class Connection
    {
    public:
        Connection(int inputUID, int outputUID);
        bool ContainsUID(int UID) const;
        bool ContainsPoint(const std::unordered_map<int, ComponentSprite>& spriteSet);
		
        void Draw(const Cairo::RefPtr<Cairo::Context>& drawCont, 
            const std::unordered_map<int, ComponentSprite>& spriteSet);
    
        int GetInputUID() const;
        int GetOutputUID() const;

    private:
        int m_inputUID;
        int m_outputUID;
    };

};