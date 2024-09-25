#include <GUI/ExampleWindow.hpp>

#include "Application.hpp"

namespace JSBEdit {

Application::Application()
{
    m_pApp = Gtk::Application::create("org.gtkmm.example");
}
int Application::Run()
{
    return m_pApp->make_window_and_run<ExampleWindow>(0, nullptr, m_pApp);
}
int Application::Stop()
{
    return 0;
}

};