#include "Contact.hpp"

Contact::Contact(const std::string& name, const std::string& type)
    : name(name), type(type), location(0.0, 0.0, 0.0),
      staticFriction(0.0), dynamicFriction(0.0),
      rollingFriction(0.0), wheelSlipFilter(0.0f) {

}

Contact::~Contact() {

}
