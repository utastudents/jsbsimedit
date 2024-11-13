#include "Channel.hpp"

namespace JSBEdit{

Channel::Channel(const Glib::RefPtr<Gtk::Application> &app, const std::string & channelName)
    : m_channelName(channelName)
{
    m_appRef = app;
}

bool Channel::ComponentNameExists(const std::string &name)
{
    //I think I should revise this to be a pair of sprites/components.
    return (m_components.contains(name) || m_spriteComponents.contains(name)); 
}

void Channel::CreateDroppedComponent(ComponentType type, int x, int y)
{
    //TODO: Create a default constructed component of the type and add to m_compoonents
    //Just doing the sprite for now.
    ComponentSprite s {type, x, y};
    
    //Generate a unique name.
    auto name = createName(type);
    while(ComponentNameExists(name))
        name = createName(type);

    //Insert the new sprite
    m_spriteComponents.insert({name, s});
    //Insert the appropriate component
    addDefaultComponent(type, name);
}

//Maybe TODO: change this later for partial redraws if its a problem.
void Channel::Draw(const Cairo::RefPtr<Cairo::Context> &drawCont)
{
    //Draw every sprite.
    for(auto& spritePair : m_spriteComponents)
        spritePair.second.Draw(drawCont);
}

std::string Channel::GetChannelName() const
{
    return m_channelName;
}

void Channel::HandleClickRelease(int x, int y)
{
    std::cout << "Canvas was clicked at: " << x << ", " << y << ". \n";
}

void Channel::HandleDoubleClick(int x, int y)
{
    std::cout << "Canvas was double clicked at: " << x << ", " << y << ". \n";
    for(auto& i : m_spriteComponents)
    {
        if(i.second.ContainsPoint(x, y))
        {
            std::cout << i.first << " component was double clicked.\n";
            m_components.at(i.first)->LoadGUI(m_appRef);
            return;
        }
    }
}

void Channel::SetChannelName(const std::string channelName)
{
    m_channelName = channelName;
}

std::string Channel::createName(ComponentType type)
{
    //If theres over 1000 components in a channel we have bigger issues..
    return std::string{COMPONENT_NAMES[static_cast<int>(type)] + std::to_string((std::rand() % 1000))};
}

void Channel::addDefaultComponent(ComponentType type, const std::string & name)
{
    switch(type)
    {
        case ComponentType::GAIN:
            m_components.insert({name, new GainComponent{name}});
            break;
        case ComponentType::PID:
            m_components.insert({name, new PIDComponent{name}});
            break;
        default:
            m_components.insert({name, new GainComponent{name}});
            break;
    }
}

};