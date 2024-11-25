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

        Gtk::CheckButton positive{"Positive"};
        Gtk::CheckButton negative{"Negative"};
        Gtk::TextView textBox; // <-- Make textBox a member variable
        std::vector<std::string> listInput{};
        Glib::RefPtr<Gtk::TextBuffer> textBuffer;
};

};