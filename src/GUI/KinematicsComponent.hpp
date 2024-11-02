#pragma once
#include "IComponentCommon.hpp"
#include <vector>
#include <utility>

namespace JSBEdit{

class KinematicsComponent : public IComponentCommon
{

public:
    KinematicsComponent(const std::string& name, ComponentType& type)
        : IComponentCommon(name, type), table(40) {}
    ~KinematicsComponent() = default;

    void LoadGUI(Glib::RefPtr<Gtk::Box>& uiBox) override;

    //Member Variables, better practice to have getters/setters but lifes short to do this for all values.
    std::string Description {};
    bool IsClipperEnabled = false;
    float MaxClip { 0.0f };
    float MinClip { 0.0f };
    bool IsInputInverted = false;
    std::vector<std::pair<float, float>> table;
    bool IsInputScale = false;
};

};