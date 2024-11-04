#ifndef TANK_DIALOG_H
#define TANK_DIALOG_H

class TankDialog {
public:
    // Constructor
    TankDialog();

    // Method to handle confirmation action
    void onConfirm();

    // Method to handle cancellation action
    void onCancel();

    // Method to fill default values of dialog box
    void defaultValueFill();
};

#endif // TANK_DIALOG_H