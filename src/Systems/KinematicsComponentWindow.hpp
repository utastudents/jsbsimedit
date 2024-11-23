#pragma once

#include "ComponentWindowCommon.hpp"
#include "KinematicsComponent.hpp"

namespace DragDrop{

class KinematicsComponentWindow : public ComponentWindowCommon
{
    public:
        KinematicsComponentWindow(std::shared_ptr<IComponentCommon> comp, 
            std::shared_ptr<std::set<std::string>> setOfNames);
    private:
        bool ScaleEnable = false;
        
        void Kinematic();
        void HandleScaleLogic();
        void SaveInfo();
};

};