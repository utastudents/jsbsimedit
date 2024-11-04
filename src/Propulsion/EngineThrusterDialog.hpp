#ifndef ENGINE_THRUSTER_DIALOG_H
#define ENGINE_THRUSTER_DIALOG_H

class EngineThrusterDialog {
public:
    // Constructor
    EngineThrusterDialog();

    // Method to handle confirmation action
    void onConfirm();

    // Method to handle cancellation action
    void onCancel();

    // Method to fill default values of dialog box
    void defaultValueFill();
};

#endif // ENGINE_THRUSTER_DIALOG_H
