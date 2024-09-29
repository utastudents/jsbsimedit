#pragma once

#include <gtkmm.h>
#include <gtkmm/application.h>

namespace JSBEdit
{

    class Application
    {
    private:
        Glib::RefPtr<Gtk::Application> m_pApp;
        Glib::ustring m_appPath;

    public:
        Application();
        int Run();
        int Stop();
        Glib::ustring GetApplicationPath();
    };

};