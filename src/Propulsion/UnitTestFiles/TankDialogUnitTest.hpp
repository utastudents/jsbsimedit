#include <gtest/gtest.h>
#include <gtkmm.h>
#include "TankDialog.hpp"

class TankDialogTest : public ::testing::Test {
protected:
    Glib::RefPtr<Gtk::Application> app;
    TankDialog* dialog;

    // Set up the GTK application and the dialog before each test
    void SetUp() override {
        app = Gtk::Application::create();
        dialog = new TankDialog();
    }

    // Clean up after each test
    void TearDown() override {
        delete dialog;
    }

    // Helper function to simulate dialog response
    void simulateResponse(int response_id) {
        dialog->on_response(response_id);
    }
};

TEST_F(TankDialogTest, TestDialogCreation) {
    ASSERT_NE(dialog, nullptr) << "Dialog should be created successfully.";
    ASSERT_FALSE(dialog->get_title().empty()) << "Dialog should have a title.";
}

TEST_F(TankDialogTest, TestConfirmButton) {
    // Simulate clicking the "Confirm" button
    simulateResponse(Gtk::RESPONSE_OK);

    // Add your assertions for the confirm action
    ASSERT_TRUE(dialog->isConfirmed()) << "Confirm button should set the dialog to confirmed state.";
}

TEST_F(TankDialogTest, TestCancelButton) {
    // Simulate clicking the "Cancel" button
    simulateResponse(Gtk::RESPONSE_CANCEL);

    // Add your assertions for the cancel action
    ASSERT_FALSE(dialog->isConfirmed()) << "Cancel button should leave the dialog unconfirmed.";
}
