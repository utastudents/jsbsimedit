#pragma once

#include "ComponentWindowCommon.hpp"

namespace DragDrop {

    class SwitchComponentWindow : public ComponentWindowCommon {
    public:
        SwitchComponentWindow(std::shared_ptr<IComponentCommon> comp,
                              std::shared_ptr<std::set<std::string>> setOfNames);

    private:
        void CreateSwitchTab();
        void SaveInfo(); // Saves user inputs
    };

};
