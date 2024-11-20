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
        void CreateOtherTabs();
        void SaveInfo();
        void AeroSurface();
        void Scheduled();
};

};