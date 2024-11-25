#pragma once

#include "DeadbandComponent.hpp"
#include "ComponentWindowCommon.hpp"

namespace DragDrop{

class DeadbandComponentWindow : public ComponentWindowCommon
{
    public:
        DeadbandComponentWindow(std::shared_ptr<IComponentCommon> comp, 
            std::shared_ptr<std::set<std::string>> setOfNames);
    private:
        void Deadband();
        void SaveInfo(); //xml must store info here to show options
};

};