#pragma once

#include <gtkmm.h>
#include <gtkmm/application.h>
#include <XML/XMLDoc.hpp>

namespace JSBEdit
{

    class Application
    {
    private:
        Glib::RefPtr<Gtk::Application> m_pApp;
        Glib::RefPtr<XMLDoc> m_aircraftDoc;
        static Application s_Instance;

    public:
        Application();
        ~Application() {}

        Application& operator=(const Application&) = delete;
        Application(const Application&) = delete;

        int Run();
        int Stop();
        Glib::RefPtr<XMLDoc> GetAircraftDoc() { return m_aircraftDoc; }

        static Application& Get() { return s_Instance; }
    };

};