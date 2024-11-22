#pragma once
#ifndef SWITCH_COMPONENT_HPP
#define SWITCH_COMPONENT_HPP

#include <string>
#include <vector>
#include <optional>
#include <utility>

class SwitchComponent {
public:
    // Constructors
    SwitchComponent(const std::string& name);

    // Setters and Getters
    void setName(const std::string& name);
    const std::string& getName() const;

    void setInput(const std::string& input);
    const std::string& getInput() const;

    void setDefault(double defaultValue);
    std::optional<double> getDefault() const;

    void addTestCondition(double testValue, double resultValue);
    const std::vector<std::pair<double, double>>& getTestConditions() const;

    void setClipLimits(double min, double max);
    std::optional<std::pair<double, double>> getClipLimits() const;

    void setOutput(const std::string& output);
    const std::string& getOutput() const;

    // Method to apply switch logic based on conditions
    double applySwitch(double inputValue);

private:
    std::string name;
    std::string input;
    std::optional<double> defaultValue;
    std::vector<std::pair<double, double>> testConditions;
    std::optional<std::pair<double, double>> clipLimits;
    std::string output;

    // Helper function to clip value within the specified limits
    double clipValue(double value);
};

#endif // SWITCH_COMPONENT_HPP
