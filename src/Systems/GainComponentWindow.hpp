#pragma once

#include "GainComponent.hpp"
#include "ComponentWindowCommon.hpp"

namespace DragDrop{

class GainComponentWindow : public ComponentWindowCommon
{
    public:
        GainComponentWindow(std::shared_ptr<IComponentCommon> comp, 
            std::shared_ptr<std::set<std::string>> setOfNames);
    private:
        void AeroSurface();
        void Scheduled();
        void SaveInfo();
        std::string selectedOption{}; //xml must store info here to show options
};

};