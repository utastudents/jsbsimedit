#include "TankDialogUnitTest.hpp"
#include <iostream>

TankDialogTest::TankDialogTest() {
    // Initialize the GTK application for testing
    app = Gtk::Application::create();
}

TankDialogTest::~TankDialogTest() {
    // Clean up if needed
}

void TankDialogTest::runTest() {
    testDialogCreation();
    testConfirmButton();
    testCancelButton();
}

void TankDialogTest::testDialogCreation() {
    // Create an instance of the dialog
    dialog = new TankDialog();

    // Check if the dialog was created successfully
    assertTrue(dialog != nullptr, "Dialog creation test");

    // Check if the dialog title is set correctly
    assertTrue(dialog->get_title() == "Tank Setup", "Dialog title test");

    // Check if default values are filled correctly
    assertTrue(dialog->typeComboBox.get_active_text() == "OXIDIZER", "Default tank type test");
    assertTrue(dialog->capacityEntry.get_text() == "0", "Default capacity test");
    assertTrue(dialog->capacityUnitComboBox.get_active_text() == "LBS", "Default capacity unit test");
    assertTrue(dialog->contentsEntry.get_text() == "0", "Default contents test");
    assertTrue(dialog->contentsUnitComboBox.get_active_text() == "LBS", "Default contents unit test");
    assertTrue(dialog->xEntry.get_text() == "0", "Default x-coordinate test");
    assertTrue(dialog->yEntry.get_text() == "0", "Default y-coordinate test");
    assertTrue(dialog->zEntry.get_text() == "0", "Default z-coordinate test");
    assertTrue(dialog->zUnitComboBox->get_active_text() == "IN", "Default z-unit test");

    // Clean up
    delete dialog;
}

void TankDialogTest::testConfirmButton() {
    // Create an instance of the dialog for testing
    dialog = new TankDialog();

    // Simulate clicking the OK button
    dialog->onCreateButtonClicked();

    // Since we're not interacting with a real GUI, just print a confirmation message
    std::cout << "Test: Confirm button pressed!" << std::endl;

    // Clean up
    delete dialog;
}

void TankDialogTest::testCancelButton() {
    // Create an instance of the dialog for testing
    dialog = new TankDialog();

    // Simulate clicking the Cancel button
    dialog->onCancelButtonClicked();

    // Since we're not interacting with a real GUI, just print a cancel message
    std::cout << "Test: Cancel button pressed!" << std::endl;

    // Clean up
    delete dialog;
}

void TankDialogTest::onResponse(int response_id) {
    if (response_id == GTK_RESPONSE_ACCEPT) {
        dialog->onCreateButtonClicked();
    } else {
        dialog->onCancelButtonClicked();
    }
}

void TankDialogTest::assertTrue(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << testName << " passed!" << std::endl;
    } else {
        std::cout << testName << " failed!" << std::endl;
    }
}
