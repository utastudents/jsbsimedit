#ifndef TANK_DIALOGBOX_H
#define TANK_DIALOGBOX_H
#include <map>
#include <string>
#include <iostream>
#include "TankDialog.hpp"


TankDialog::TankDialog() {
// TODO: Initialize dialog components
    void show();
    void close();
    void onConfirm();
    void onCancel();
    void defaultValueFill();
};

void TankDialog::onConfirm() {
    // TODO: Implement confirmation logic
    std::cout << "Confirming tank settings..." << std::endl;
}

void TankDialog::onCancel() {
    // TODO: Implement cancellation logic
    std::cout << "Cancelling tank settings..." << std::endl;
}

void TankDialog::defaultValueFill(){
    // TODO: Implement defaultValueFill logic
    std::cout << "Unable to fill tank dialog box..." << std::endl;
}

#endif // TANK_DIALOG_H
