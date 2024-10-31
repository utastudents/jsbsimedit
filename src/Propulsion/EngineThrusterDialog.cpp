#ifndef ENGINE_THRUSTER_DIALOG_H
#define ENGINE_THRUSTER_DIALOG_H
#include <map>
#include <string>
#include <iostream>


class EngineThrusterDialog {
public:
    // Constructor
    EngineThrusterDialog();

    // Method to handle confirmation action
    void onConfirm();

    // Method to handle cancellation action
    void onCancel();
};

void EngineThrusterDialog::onConfirm() {
    // TODO: Implement confirmation logic
    std::cout << "Confirming tank settings..." << std::endl;
}

void EngineThrusterDialog::onCancel() {
    // TODO: Implement cancellation logic
    std::cout << "Cancelling tank settings..." << std::endl;
}

#endif // ENGINE_THRUSTER_DIALOG_H
