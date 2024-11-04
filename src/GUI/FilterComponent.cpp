#include "FilterComponent.hpp"
#include <algorithm>

// Constructor
FilterComponent::FilterComponent(const std::string& name, const std::string& input, double c1)
    : name(name), input(input), c1(c1), clipLimits(std::nullopt) {}

// Setters and Getters
void FilterComponent::setName(const std::string& name) {
    this->name = name;
}

const std::string& FilterComponent::getName() const {
    return name;
}

void FilterComponent::setInput(const std::string& input) {
    this->input = input;
}

const std::string& FilterComponent::getInput() const {
    return input;
}

void FilterComponent::setCoefficient(double c1) {
    this->c1 = c1;
}

double FilterComponent::getCoefficient() const {
    return c1;
}

void FilterComponent::setClipLimits(double min, double max) {
    clipLimits = std::make_pair(min, max);
}

std::optional<std::pair<double, double>> FilterComponent::getClipLimits() const {
    return clipLimits;
}

void FilterComponent::setOutput(const std::string& output) {
    this->output = output;
}

const std::string& FilterComponent::getOutput() const {
    return output;
}

// Apply filter logic
double FilterComponent::applyFilter(double inputValue) {
    double filteredValue = c1 * inputValue;
    return clipValue(filteredValue);
}

// Clip value within limits
double FilterComponent::clipValue(double value) {
    if (clipLimits) {
        return std::clamp(value, clipLimits->first, clipLimits->second);
    }
    return value;
}
