#ifndef ENGINE_THRUSTER_DIALOG_H
#define ENGINE_THRUSTER_DIALOG_H
#include <map>
#include <string>
#include <iostream>
#include "EngineThrusterDialog.hpp"

class EngineThrusterDialog {
public:
    // Constructor
    EngineThrusterDialog();

    void show();
    void close();

    // Method to handle confirmation action
    void onConfirm();

    // Method to handle cancellation action
    void onCancel();

    // Method to fill default values of dialog box
    void defaultValueFill();
};

void EngineThrusterDialog::onConfirm() {
    // TODO: Implement confirmation logic
    std::cout << "Confirming Engine/Thruster settings..." << std::endl;
}

void EngineThrusterDialog::onCancel() {
    // TODO: Implement cancellation logic
    std::cout << "Cancelling Engine/Thruster settings..." << std::endl;
}

void EngineThrusterDialog::defaultValueFill(){
    // TODO: Implement defaultValueFill logic
    std::cout << "Unable to fill Engine/Thruster dialog box..." << std::endl;
}

#endif // ENGINE_THRUSTER_DIALOG_H
