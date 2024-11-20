#include "ComponentWindowCommon.hpp"

namespace DragDrop
{

    ComponentWindowCommon::ComponentWindowCommon(std::shared_ptr<IComponentCommon> component, std::shared_ptr<std::set<std::string>> setOfNames)
        : m_component(component), m_setOfNames(setOfNames)
    {
        set_size_request(300, 400);
        set_title(m_component->GetName());
        //Makes its so you can't interact with other windows but this
        set_modal(true);

        //Contains window contents..
        m_windowContainer.set_vexpand(true);
        m_windowContainer.set_hexpand(true);
        m_windowContainer.append(m_noteBook);
    
        //Add window container, then show the window
        set_child(m_windowContainer);
        show();

    }

    void ComponentWindowCommon::CreateCommonTab()
    {
        m_maxEntry.set_text(std::to_string(m_component->GetClipperMax()));
        m_minEntry.set_text(std::to_string(m_component->GetClipperMin()));
        m_clipperButton.set_active(m_component->IsClipperEnabled());
        m_nameEntry.set_text(m_component->GetName());
        //Tabs contents in the box
        m_tabContainer.set_vexpand(true);
        m_tabContainer.set_hexpand(true);

        //Name layout.
        Gtk::Label nameLabel{"Name:"};
        //Type label
        Gtk::Label typeLabel{"Component Type:" + COMPONENT_NAMES[(int)m_component->GetComponentType()]};
  
        //Max label
        Gtk::Label maxLabel{"Max:"};
        Gtk::Label minLabel{"Min:"};
        //Disable when check box is clicked
        m_maxEntry.set_sensitive(m_component->IsClipperEnabled());
        m_minEntry.set_sensitive(m_component->IsClipperEnabled());
  
        //Clipper button and label
        Gtk::Label clipperLabel{"Clipper:"};
        m_clipperButton.signal_toggled().connect(sigc::mem_fun(*this, &ComponentWindowCommon::ClipperChange), false);

        //Accept/Cancel button
        m_acceptButton.signal_clicked().connect(sigc::mem_fun(*this, &ComponentWindowCommon::SaveCommonChanges), false);
        m_cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &ComponentWindowCommon::CloseWindow), false);
        signal_close_request().connect(sigc::mem_fun(*this, &ComponentWindowCommon::OnWindowClosePressed), false);

        //Attaching all the widgets to the grid
        m_grid.attach(nameLabel,1,1);
        m_grid.attach(m_nameEntry,1,2);
        m_grid.attach(typeLabel,1,3);
        m_grid.attach(clipperLabel,1,4);
        m_grid.attach(m_clipperButton,2,4);
        m_grid.attach(maxLabel, 1, 5);
        m_grid.attach(m_maxEntry, 2, 5);
        m_grid.attach(minLabel, 1, 6);
        m_grid.attach(m_minEntry, 2, 6);
        m_grid.attach(m_acceptButton,1,7);
        m_grid.attach(m_cancelButton,2,7);

        //Add grid to box
        m_tabContainer.append(m_grid);
        //Add tab to notebook
        m_noteBook.append_page(m_tabContainer, "Common");
        show();
    }

    void ComponentWindowCommon::CloseWindow()
    {
        close();
    }

    void ComponentWindowCommon::SaveCommonChanges()
    {
        //Set the component name if not empty
        auto nameEntered = m_nameEntry.get_text();
        if(!nameEntered.empty())
            m_component->SetName(nameEntered);

        //Clipper max next, convert string to float
        try{ 
            float inpFloat = std::stof(m_maxEntry.get_text());
            m_component->SetClipperMax(inpFloat);
        }
        catch(...){} //Do nothin on the throw

        //Clipper min next, convert string to float
        try{ 
            float inpFloat = std::stof(m_minEntry.get_text());
            m_component->SetClipperMin(inpFloat);
        }
        catch(...){} //Do nothin on the throw

        //Set the value of the clipper check
        m_component->SetClipperState(m_clipperButton.get_active());

        CloseWindow();
    }

    void ComponentWindowCommon::ClipperChange()
    {
        bool newState = !m_component->IsClipperEnabled();
        m_component->SetClipperState(newState);
        m_clipperButton.set_active(newState);
        m_maxEntry.set_sensitive(newState);
        m_minEntry.set_sensitive(newState);
    }

    bool ComponentWindowCommon::OnWindowClosePressed()
    {
        SaveCommonChanges();
        return false; //BEcause the callback wants a bool thats why and if it returns true then no close.
    }

};