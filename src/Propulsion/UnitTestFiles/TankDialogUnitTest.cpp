#include <gtest/gtest.h>
#include <gtkmm.h>
#include "TankDialog.hpp"

class TankDialogTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize GTK application
        app = Gtk::Application::create();
    }

    Glib::RefPtr<Gtk::Application> app;
};

// Test default value filling
TEST_F(TankDialogTest, DefaultValueFillTest) {
    TankDialog dialog;

    // Verify default values for typeComboBox
    EXPECT_EQ(dialog.typeComboBox.get_active_text(), "OXIDIZER");

    // Verify default values for capacity and contents
    EXPECT_EQ(dialog.capacityEntry.get_text(), "0");
    EXPECT_EQ(dialog.capacityUnitComboBox.get_active_text(), "LBS");
    EXPECT_EQ(dialog.contentsEntry.get_text(), "0");
    EXPECT_EQ(dialog.contentsUnitComboBox.get_active_text(), "LBS");

    // Verify default values for location fields
    EXPECT_EQ(dialog.xEntry.get_text(), "0");
    EXPECT_EQ(dialog.yEntry.get_text(), "0");
    EXPECT_EQ(dialog.zEntry.get_text(), "0");

    // Verify default value for zUnitComboBox
    EXPECT_EQ(dialog.zUnitComboBox->get_active_text(), "IN");
}

// Test the validity of selection
TEST_F(TankDialogTest, IsValidSelectionTest) {
    TankDialog dialog;

    // Initially, all fields are set to default values; should be valid
    EXPECT_TRUE(dialog.isValidSelection());

    // Invalidate by clearing the capacity entry
    dialog.capacityEntry.set_text("");
    EXPECT_FALSE(dialog.isValidSelection());

    // Restore valid state
    dialog.capacityEntry.set_text("100");
    EXPECT_TRUE(dialog.isValidSelection());
}

// Test Create button functionality
TEST_F(TankDialogTest, OnCreateButtonClickedTest) {
    TankDialog dialog;

    // Redirect stdout to verify output
    testing::internal::CaptureStdout();
    dialog.onCreateButtonClicked();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Tank configuration saved!\n");

    // Invalidate a field and check error message
    dialog.capacityEntry.set_text("");
    testing::internal::CaptureStderr();
    dialog.onCreateButtonClicked();
    std::string errorOutput = testing::internal::GetCapturedStderr();

    EXPECT_EQ(errorOutput, "Please fill out all fields!\n");
}

// Test Cancel button functionality
TEST_F(TankDialogTest, OnCancelButtonClickedTest) {
    TankDialog dialog;

    // Ensure the cancel button closes the dialog without side effects
    EXPECT_NO_THROW(dialog.onCancelButtonClicked());
}

// Test initialization
TEST_F(TankDialogTest, InitializationTest) {
    TankDialog dialog;

    // Verify the dialog title
    EXPECT_EQ(dialog.get_title(), "Tank Setup");
}
