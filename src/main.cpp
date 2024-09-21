#include <gtkmm.h>
#include <gtkmm/application.h>

#include "examplewindow.h"

#include <stdio.h>


int main( [[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    printf("Hello World!\n");
    auto app = Gtk::Application::create("org.gtkmm.example");

    //Shows the window and returns when it is closed.
    return app->make_window_and_run<ExampleWindow>(argc, argv, app);

    return 0;
}
