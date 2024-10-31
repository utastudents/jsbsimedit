#ifndef ENGINE_H
#define ENGINE_H
#include "EngineThruster.hpp"

class Engine : public EngineThruster {
public:
    // Constructor
    Engine(const std::string& name, int engineOrThruster, float locationX, float locationY, float orientation, int power, int augmented);

    // Method to load engine data from an XML file
    void loadEngineFromXML();

    // Getters for the new attributes
    int getPower() const;
    int getAugmented() const;

private:
    int power;      // Power of the engine
    int augmented;  // Augmented value (could represent additional capabilities or features)
};

#endif // ENGINE_H
