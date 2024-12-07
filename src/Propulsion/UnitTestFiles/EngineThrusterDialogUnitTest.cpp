#include "EngineThrusterDialogUnitTest.hpp"
#include <iostream>

EngineThrusterDialogTest::EngineThrusterDialogTest() {
    // Initialize the GTK application for testing
    app = Gtk::Application::create();
}

EngineThrusterDialogTest::~EngineThrusterDialogTest() {
    // Clean up if needed (though Gtk::Application should manage cleanup)
}

void EngineThrusterDialogTest::runTest() {
    testDialogCreation();
    testConfirmButton();
    testCancelButton();
}

void EngineThrusterDialogTest::testDialogCreation() {
    // Create an instance of the dialog with test engine and thruster names
    dialog = new EngineThrusterDialog("TestEngine", "TestThruster");

    // Check if the dialog was created successfully
    assertTrue(dialog != nullptr, "Dialog creation test");

    // Check if dialog title is set correctly
    assertTrue(dialog->get_title() == "Engine/Thruster Setup", "Dialog title test");

    // Clean up
    delete dialog;
}

void EngineThrusterDialogTest::testConfirmButton() {
    // Create an instance of the dialog for testing
    dialog = new EngineThrusterDialog("TestEngine", "TestThruster");

    // Simulate a response with GTK_RESPONSE_ACCEPT (OK button)
    dialog->onResponse(GTK_RESPONSE_ACCEPT);

    // Since we're not interacting with a real GUI, let's just check output
    // We expect "Confirmed! Settings have been applied." to be printed
    // (In real tests, we could capture stdout, but here we just print)
    std::cout << "Test: Confirm button pressed!" << std::endl;

    // Clean up
    delete dialog;
}

void EngineThrusterDialogTest::testCancelButton() {
    // Create an instance of the dialog for testing
    dialog = new EngineThrusterDialog("TestEngine", "TestThruster");

    // Simulate a response with GTK_RESPONSE_REJECT (Cancel button)
    dialog->onResponse(GTK_RESPONSE_REJECT);

    // Since we're not interacting with a real GUI, let's just check output
    // We expect "Canceled! No changes were applied." to be printed
    std::cout << "Test: Cancel button pressed!" << std::endl;

    // Clean up
    delete dialog;
}

void EngineThrusterDialogTest::onResponse(int response_id) {
    if (response_id == GTK_RESPONSE_ACCEPT) {
        dialog->onConfirm();
    }
    else {
        dialog->onCancel();
    }
}

void EngineThrusterDialogTest::assertTrue(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << testName << " passed!" << std::endl;
    }
    else {
        std::cout << testName << " failed!" << std::endl;
    }
}
