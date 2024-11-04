#ifndef DIALOGBOX_H
#define DIALOGBOX_H
#include <iostream>
#include "TankDialog.hpp"


TankDialog::TankDialog() {
// TODO: Initialize dialog components
    void show();
    void close();
    void onConfirm();
    void onCancel();
};

void TankDialog::onConfirm() {
    // TODO: Implement confirmation logic
    std::cout << "Confirming tank settings..." << std::endl;
}

void TankDialog::onCancel() {
    // TODO: Implement cancellation logic
    std::cout << "Cancelling tank settings..." << std::endl;
}

#endif // TANK_H

