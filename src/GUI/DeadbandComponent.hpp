#pragma once
#ifndef DEADBAND_COMPONENT_HPP
#define DEADBAND_COMPONENT_HPP

#include <string>
#include <optional>

class DeadbandComponent {
public:
    // Constructors
    DeadbandComponent(const std::string& name, const std::string& input, double width);

    // Setters and Getters
    void setName(const std::string& name);
    const std::string& getName() const;

    void setInput(const std::string& input);
    const std::string& getInput() const;

    void setWidth(double width);
    double getWidth() const;

    void setClipLimits(double min, double max);
    std::optional<std::pair<double, double>> getClipLimits() const;

    void setOutput(const std::string& output);
    const std::string& getOutput() const;

    // Methods
    double applyDeadband(double inputValue);

private:
    std::string name;
    std::string input;
    double width;
    std::optional<std::pair<double, double>> clipLimits;
    std::string output;

    // Helper function to clip value within the specified limits
    double clipValue(double value);
};

#endif // DEADBAND_COMPONENT_HPP
