#include "GasCell.hpp"

int GasCell::ballonetCount = 0;

// GasCell constructor
GasCell::GasCell() : Component() {
    name = "Gas Cell";
}

GasCell::~GasCell() {
}

void GasCell::addBallonet(Ballonet newBallonet) {
    ballonets.push_back(newBallonet);
    ballonetCount++;
}

void GasCell::removeLastBallonet() {
    ballonets.pop_back();
    ballonetCount--;
}

Ballonet GasCell::getBallonet(int index) {
    return ballonets.at(index);
}

std::vector<Ballonet> GasCell::getBallonets() {
    return ballonets;
}


void GasCell::setBallonetCount(int count) {
    ballonetCount = count;
}

int GasCell::getBallonetCount() { 
    return ballonetCount; 
}