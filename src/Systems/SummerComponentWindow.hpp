#pragma once

#include "ComponentWindowCommon.hpp"
#include "SummerComponent.hpp"

namespace DragDrop{

class SummerComponentWindow : public ComponentWindowCommon
{
    public:
        SummerComponentWindow(std::shared_ptr<IComponentCommon> comp, 
            std::shared_ptr<std::set<std::string>> setOfNames);
    private:
        void Summer();
        void positiveToggled();
        void negativeToggled();
        void AddInput();
        void RemoveInput();
        void SaveInfo();

        // MUST remain as pointer as they are manipulated in different function.
        std::vector<std::string> listInput{};
        Glib::RefPtr<Gtk::CheckButton> m_positive{};
        Glib::RefPtr<Gtk::CheckButton> m_negative{};
        Glib::RefPtr<Gtk::Button> buttonAdd;
        Glib::RefPtr<Gtk::Button> buttonRemove;
        Glib::RefPtr<Gtk::TextBuffer> textBuffer;
};

};