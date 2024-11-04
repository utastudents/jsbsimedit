#ifndef TANK_DIALOG_H
#define TANK_DIALOG_H
#include "TankDialog.hpp"
#include <map>
#include <string>

class TankDialog {
public:
    // Constructor
    TankDialog();

    // Method to handle confirmation action
    void onConfirm();

    // Method to handle cancellation action
    void onCancel();
};

#endif // TANK_DIALOG_H