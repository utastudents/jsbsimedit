#include "Engine.h"
#include <iostream>

Engine::Engine(const std::string& name, int engineOrThruster, float locationX, float locationY, float orientation, int power, int augmented)
    : EngineThruster(name, engineOrThruster, locationX, locationY, orientation), power(power), augmented(augmented) {}

void Engine::loadEngineFromXML() {
    // TODO: Implement XML loading logic for engine data
    std::cout << "Loading engine data from XML..." << std::endl;
}

int Engine::getPower() const {
    return power;
}

int Engine::getAugmented() const {
    return augmented;
}
