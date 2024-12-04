#pragma once

#include "FilterComponent.hpp"
#include "ComponentWindowCommon.hpp"
#include <gtkmm.h>

namespace DragDrop {

class FilterComponentWindow : public ComponentWindowCommon {
public:
    FilterComponentWindow(std::shared_ptr<IComponentCommon> comp, 
                          std::shared_ptr<std::set<std::string>> setOfNames);

private:
    void FilterTab(); // Tab with filter-specific configurations
    void SaveInfo();  // Saves component data
    void CancelInfo(); // Cancels changes and closes the window
};

} // namespace DragDrop