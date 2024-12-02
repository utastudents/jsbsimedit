#pragma once
#include "gtkmm.h"
#include "inc/Subsystem.hpp"


class ExternalReactionsSubsystem : public Subsystem {
    public:
        // std::string m_Name;
        ExternalReactionsSubsystem();
        void Create();
        void tabSetup(Gtk::Grid& ex_grid);

    protected:
        Gtk::Notebook m_notebook;
        std::vector<std::unique_ptr<Gtk::Grid>> m_pages;
        std::map<std::string, std::unique_ptr<Gtk::DropDown>> m_dropdown;
        Glib::RefPtr<Gtk::StringList> m_unitList;


    private:

        double locationX;
        double locationY;
        double locationZ;
        double directionX;
        double directionY;
        double directionZ; 
};