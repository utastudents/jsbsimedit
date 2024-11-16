#include "DeadbandComponent.hpp"
#include <cmath>
#include <algorithm>

namespace DragDrop{

// Constructor
DeadbandComponent::DeadbandComponent(const std::string& name, const std::string& input, double width)
    : name(name), input(input), width(width), clipLimits(std::nullopt) {}

// Setters and Getters
void DeadbandComponent::setName(const std::string& name) {
    this->name = name;
}

const std::string& DeadbandComponent::getName() const {
    return name;
}

void DeadbandComponent::setInput(const std::string& input) {
    this->input = input;
}

const std::string& DeadbandComponent::getInput() const {
    return input;
}

void DeadbandComponent::setWidth(double width) {
    this->width = width;
}

double DeadbandComponent::getWidth() const {
    return width;
}

void DeadbandComponent::setClipLimits(double min, double max) {
    clipLimits = std::make_pair(min, max);
}

std::optional<std::pair<double, double>> DeadbandComponent::getClipLimits() const {
    return clipLimits;
}

void DeadbandComponent::setOutput(const std::string& output) {
    this->output = output;
}

const std::string& DeadbandComponent::getOutput() const {
    return output;
}

// Apply deadband filter logic
double DeadbandComponent::applyDeadband(double inputValue) {
    double filteredValue = std::abs(inputValue) < width ? 0.0 : inputValue;
    return clipValue(filteredValue);
}

// Clip value within limits
double DeadbandComponent::clipValue(double value) {
    if (clipLimits) {
        return std::clamp(value, clipLimits->first, clipLimits->second);
    }
    return value;
}

};