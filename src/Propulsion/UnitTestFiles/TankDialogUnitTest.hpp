#ifndef TANK_DIALOG_TEST_HPP
#define TANK_DIALOG_TEST_HPP

#include <gtkmm.h>
#include "Propulsion/TankDialog.hpp"

class TankDialogTest {
public:
    TankDialogTest(); // Constructor for initializing test environment
    ~TankDialogTest(); // Destructor for cleanup

    // Function to initialize and run the tests
    void runTest();
    void testDialogCreation();      // Test dialog creation and default values
    void testConfirmButton();       // Test functionality of the confirm (OK) button
    void testCancelButton();        // Test functionality of the cancel button

private:
    // Declare a Gtk::Application for testing purposes
    Glib::RefPtr<Gtk::Application> app;

    // Declare the dialog pointer for testing
    TankDialog* dialog;

    // Simulate the behavior of the dialog's response function
    void onResponse(int response_id);

    // Helper function to run the tests
    void assertTrue(bool condition, const std::string& testName);
};

#endif // TANK_DIALOG_TEST_HPP
