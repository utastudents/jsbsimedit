#pragma once
#include <gtkmm.h>
#include "IComponentCommon.hpp"
#include <string>
#include <set>
#include <memory>

namespace DragDrop
{

class ComponentWindowCommon : public Gtk::Window
{
    public:
        ComponentWindowCommon(std::shared_ptr<IComponentCommon> component, 
            std::shared_ptr<std::set<std::string>> setOfNames);
    protected:
        //Member funcs
        void CreateCommonTab();
        void CloseWindow();

        //Member vars
        //Used to ensure that the component name doesnt already exist in this channel.
        std::shared_ptr<std::set<std::string>> m_setOfNames;
        Gtk::Notebook m_noteBook{};
        Gtk::Button m_acceptButton{"Accept"};

    private:
        //Member funcs
        void ClipperChange();
        bool OnWindowClosePressed();
        void SaveCommonChanges();

        //Member variabels
        std::shared_ptr<IComponentCommon> m_component;
        Gtk::Entry m_maxEntry{};
        Gtk::Entry m_minEntry{};
        Gtk::Entry m_nameEntry{};
        Gtk::CheckButton m_clipperButton;
        Gtk::Button m_cancelButton{"Cancel"};
        Gtk::Box m_windowContainer{};
        Gtk::Box m_tabContainer{};
        Gtk::Grid m_grid{};

};

};