#include <MainWindow/ExampleWindow.hpp>

#include "Application.hpp"

namespace JSBEdit
{

    Application::Application()
    {
        m_pApp = Gtk::Application::create("org.gtkmm.example");
        m_appPath = Glib::get_current_dir();
    }
    int Application::Run(int argc,char *argv[])
    {
        if (argc>1)
        {
            std::cout << "the first arg is " << argv[1] << std::endl;
            // note this is where the filename can be taken when the 
            // program is invoked with an arguument.
        }
        return m_pApp->make_window_and_run<ExampleWindow>(0, nullptr, m_pApp);
    }
    int Application::Stop()
    {
        return 0;
    }
    Glib::ustring Application::GetApplicationPath()
    {
        return m_appPath;
    }

};
