#include "ExampleTab.hpp"
#include <iostream>

namespace JSBEdit {

ExampleTab::ExampleTab([[maybe_unused]] const Glib::RefPtr<Gtk::Application>& app
    , const std::string& buttonName)
        : l(buttonName)
{
    try
    {
        m_refBuilder = Gtk::Builder::create_from_file("../../../mainWindow.xml");
    }
    catch (const Glib::Error& ex)
    {
        std::cerr << "Error loading mainWindow.xml " << ex.what() << std::endl;
    }
    append(l);
}

ExampleTab::~ExampleTab()
{
}

};
