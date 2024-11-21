#include "Channel.hpp"

namespace DragDrop{

Channel::Channel(const Glib::RefPtr<Gtk::Application> &app, const std::string & channelName)
    : m_channelName(channelName)
{
    m_appRef = app;
    m_componentNameSet = std::make_shared<std::set<std::string>>();
}

bool Channel::ComponentNameExists(const std::string &name)
{
    return m_componentNameSet->contains(name); 
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
    m_componentNameSet->insert(name);

    //Generate a uniqueId
    int uId = generateUniqueId();
    m_uniqueIDSet.insert(uId);

    //Insert the new sprite
    m_spriteComponents.insert({uId, s});
    //Insert the appropriate component, also takes care of adding the UID;
    addDefaultComponent(type, name, uId);
}

//Maybe TODO: change this later for partial redraws if its a problem.
void Channel::Draw(const Cairo::RefPtr<Cairo::Context> &drawCont)
{
    //Creating a pango layout & font stuff
    auto layout = Pango::Layout::create(drawCont);
    Pango::FontDescription fontDesc{};
    fontDesc.set_family("Sans");
    fontDesc.set_size(10 * Pango::SCALE);
    layout->set_font_description(fontDesc);
    drawCont->set_source_rgb(0,0,0);
    for(auto& spritePair : m_spriteComponents)
    {
        int uId = spritePair.first;
        layout->set_text(m_components.at(uId)->GetName());
        //Position is oriented center, this goes to the bottom middle of box
        auto pos = spritePair.second.GetPosition();
        auto bounds = spritePair.second.GetBounds();
        int textWidth, textHeight {};
        layout->get_pixel_size(textWidth, textHeight); // For centering seen below V
        drawCont->move_to((-.5f * textWidth + pos.first), (.5f * bounds.second + pos.second));
        layout->show_in_cairo_context(drawCont);
    }

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
            int uid = i.first;
            std::cout << uid << " component was double clicked.\n";
            auto cType = i.second.GetComponentType();
            switch(cType)
            {
                case ComponentType::GAIN:
                    m_winPtr = std::make_shared<GainComponentWindow>(m_components.at(uid), m_componentNameSet);
                    m_appRef->add_window(*m_winPtr);
                    break;
                    
                case ComponentType::KINEMATIC:
                    m_winPtr = std::make_shared<KinematicsComponentWindow>(m_components.at(uid), m_componentNameSet);
                    m_appRef->add_window(*m_winPtr);
                    break;

                default:
                    m_winPtr = std::make_shared<GainComponentWindow>(m_components.at(uid), m_componentNameSet);
                    m_appRef->add_window(*m_winPtr);
                    break;
            }
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
    return std::string{COMPONENT_NAMES[static_cast<int>(type)] + std::to_string((generateUniqueId()))};
}

int Channel::generateUniqueId()
{
    int uId = m_distribuition(m_rng);
    if(m_uniqueIDSet.contains(uId))
        uId = generateUniqueId();
    return uId;
}

void Channel::addDefaultComponent(ComponentType type, const std::string & name, int uId)
{
    switch(type)
    {
        case ComponentType::GAIN:
            m_components.insert({uId, std::make_shared<GainComponent>(name)});
            break;
        case ComponentType::PID:
            m_components.insert({uId, std::make_shared<PIDComponent>(name)});
            break;
        case ComponentType::KINEMATIC:
            m_components.insert({uId, std::make_shared<KinematicsComponent>(name)});
            break;
        case ComponentType::SUMMER:
            m_components.insert({uId, std::make_shared<SummerComponent>(name)});
            break;
        case ComponentType::DEADBAND:
            m_components.insert({uId, std::make_shared<DeadbandComponent>(name)});
            break;
        default:
            m_components.insert({uId, std::make_shared<GainComponent>(name)});
            break;
    }
}

};