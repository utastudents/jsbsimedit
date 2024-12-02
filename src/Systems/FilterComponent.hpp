#pragma once

#include "IComponentCommon.hpp"
#include <string>
#include <vector>

namespace DragDrop {

class FilterComponent : public IComponentCommon {
public:
    FilterComponent(const std::string& name);
    ~FilterComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Application>& app) override;
    void LoadFromXml(JSBEdit::XMLNode& node) override;

    // Member variables for filter configuration
    std::string ComponentName;
    std::string Type;
    int Order;
    float MaxValue;
    float MinValue;

    std::vector<std::string> DropdownOptions;
    std::vector<float> Coefficients;
    bool IsEnabled;
};

} // namespace DragDrop