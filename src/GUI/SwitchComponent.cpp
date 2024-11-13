#include "SwitchComponent.hpp"
#include <algorithm>

namespace DragDrop{

// Constructor
SwitchComponent::SwitchComponent(const std::string& name)
    : name(name), defaultValue(std::nullopt), clipLimits(std::nullopt) {}

// Setters and Getters
void SwitchComponent::setName(const std::string& name) {
    this->name = name;
}

const std::string& SwitchComponent::getName() const {
    return name;
}

void SwitchComponent::setInput(const std::string& input) {
    this->input = input;
}

const std::string& SwitchComponent::getInput() const {
    return input;
}

void SwitchComponent::setDefault(double defaultValue) {
    this->defaultValue = defaultValue;
}

std::optional<double> SwitchComponent::getDefault() const {
    return defaultValue;
}

void SwitchComponent::addTestCondition(double testValue, double resultValue) {
    testConditions.emplace_back(testValue, resultValue);
}

const std::vector<std::pair<double, double>>& SwitchComponent::getTestConditions() const {
    return testConditions;
}

void SwitchComponent::setClipLimits(double min, double max) {
    clipLimits = std::make_pair(min, max);
}

std::optional<std::pair<double, double>> SwitchComponent::getClipLimits() const {
    return clipLimits;
}

void SwitchComponent::setOutput(const std::string& output) {
    this->output = output;
}

const std::string& SwitchComponent::getOutput() const {
    return output;
}

// Apply switch logic based on test conditions
double SwitchComponent::applySwitch(double inputValue) {
    for (const auto& condition : testConditions) {
        if (inputValue == condition.first) {
            return clipValue(condition.second);
        }
    }
    // Return default if no condition is met
    return defaultValue.has_value() ? clipValue(defaultValue.value()) : 0.0;
}

// Clip value within limits
double SwitchComponent::clipValue(double value) {
    if (clipLimits) {
        return std::clamp(value, clipLimits->first, clipLimits->second);
    }
    return value;
}

};