#include <gtkmm.h>
#include <gtkmm/application.h>

#include <Application/Application.hpp>

#include <XML/XMLDoc.hpp>
#include <Metrics/Metrics.h>


int main( [[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    printf("Hello World!\n");

    JSBEdit::Application& app = JSBEdit::Application::Get();

    std::filesystem::path path { Glib::get_current_dir() };
    path = std::filesystem::canonical(path.append("../../../reference/JSBSimCommander/f16.xml"));

    Glib::RefPtr<JSBEdit::XMLDoc> doc = app.GetAircraftDoc();
    doc->LoadFileAndParse(path);

    Metrics metrics_system;

    //Shows the window and returns when it is closed.
    return app.Run();
}

