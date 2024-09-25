#include <gtkmm.h>
#include <gtkmm/application.h>

#include <Application/Application.hpp>

#include <XML/XMLDoc.hpp>


int main( [[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    printf("Hello World!\n");

    JSBEdit::Application app;

    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse({"../../../reference/JSBSimCommander/f16.xml"});

    //Shows the window and returns when it is closed.
    return app.Run();
}

