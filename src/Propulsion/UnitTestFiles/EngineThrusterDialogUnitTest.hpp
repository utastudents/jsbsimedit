#ifndef ENGINE_THRUSTER_DIALOG_TEST_HPP
#define ENGINE_THRUSTER_DIALOG_TEST_HPP

#include <gtkmm.h>
#include "Propulsion/EngineThrusterDialog.hpp"

class EngineThrusterDialogTest {
public:
    EngineThrusterDialogTest();
    ~EngineThrusterDialogTest();

    // Function to initialize the test
    void runTest();
    void testDialogCreation();
    void testConfirmButton();
    void testCancelButton();

private:
    // Declare a Gtk::Application for testing purposes
    Glib::RefPtr<Gtk::Application> app;

    // Declare the dialog pointer
    EngineThrusterDialog* dialog;

    // Simulate the behavior of the dialog's response function
    void onResponse(int response_id);

    // Helper function to run the tests
    void assertTrue(bool condition, const std::string& testName);
};

#endif // ENGINE_THRUSTER_DIALOG_TEST_HPP
