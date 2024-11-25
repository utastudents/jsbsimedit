#pragma once

#include "ComponentWindowCommon.hpp"
#include "PIDComponent.hpp"

namespace DragDrop{

class PIDComponentWindow : public ComponentWindowCommon
{
    public:
        PIDComponentWindow(std::shared_ptr<IComponentCommon> comp, 
            std::shared_ptr<std::set<std::string>> setOfNames);
    private:
        void Pid();
        void SaveInfo();
        void HandleInvertLogic();
        bool InputInverted = false;
};

};