#include <gtkmm.h>
#include <gtkmm/application.h>

#include <Application/Application.hpp>

#include <XML/XMLDoc.hpp>


int main( [[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    printf("Hello World!\n");

    JSBEdit::Application app;

    std::filesystem::path path {app.GetApplicationPath().c_str()};
    path = std::filesystem::canonical(path.append("../../../reference/JSBSimCommander/f16.xml"));

    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse(path);
    JSBEdit::Metrics* metric = doc.GetMetricsData();

    //Shows the window and returns when it is closed.
    return app.Run();
}

