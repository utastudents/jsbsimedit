#pragma once
#ifndef FILTER_COMPONENT_HPP
#define FILTER_COMPONENT_HPP

#include <string>
#include <optional>

class FilterComponent {
public:
    // Constructors
    FilterComponent(const std::string& name, const std::string& input, double c1);

    // Setters and Getters
    void setName(const std::string& name);
    const std::string& getName() const;

    void setInput(const std::string& input);
    const std::string& getInput() const;

    void setCoefficient(double c1);
    double getCoefficient() const;

    void setClipLimits(double min, double max);
    std::optional<std::pair<double, double>> getClipLimits() const;

    void setOutput(const std::string& output);
    const std::string& getOutput() const;

    // Methods
    double applyFilter(double inputValue);
    
private:
    std::string name;
    std::string input;
    double c1;
    std::optional<std::pair<double, double>> clipLimits;
    std::string output;

    // Helper function to clip value within the specified limits
    double clipValue(double value);
};

#endif // FILTER_COMPONENT_HPP
