#include "Channel.hpp"

namespace DragDrop{

Channel::Channel(const Glib::RefPtr<Gtk::Application> &app, const std::string & channelName)
    : m_channelName(channelName)
{
    m_appRef = app;
    m_componentNameSet = std::make_shared<std::set<std::string>>();
    populateStringComponentMap();
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

    //Generate a uniqueId
    int uId = generateUniqueId();
    m_uniqueIDSet.insert(uId);

    //Insert the new sprite
    m_spriteComponents.insert({uId, s});
    //Insert the appropriate component, also takes care of adding the UID;
    m_components.insert({uId, createComponentFromType(type, name)});
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

    //Draw every connection.
    for(auto& connect : m_connections)
        connect.Draw(drawCont, m_spriteComponents);

    //If we are not connecting then exit early.
    if(m_dragState == DragState::DRAGGING || m_dragState == DragState::NONE)
        return;

    //Drawing the connection lines if we are trying to make connection via dragging.
    drawCont->set_line_width(2);
    drawCont->set_source_rgb(0,0,0);
    std::pair<int, int> startLoc {};

    if(m_dragState == DragState::CONNECT_INP)
        startLoc = m_spriteComponents.at(m_selectedId).GetInputBoxPosition();
    else if(m_dragState == DragState::CONNECT_OUT)
        startLoc = m_spriteComponents.at(m_selectedId).GetOutputBoxPosition();
    drawCont->move_to(startLoc.first, startLoc.second);
    drawCont->line_to(m_currentDragPos.first, m_currentDragPos.second);
    drawCont->stroke();
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
    //std::cout << "Canvas was double clicked at: " << x << ", " << y << ". \n";
    for(auto& i : m_spriteComponents)
    {
        if(i.second.ContainsPoint(x, y))
        {
            int uid = i.first;
            //std::cout << uid << " component was double clicked.\n";
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

                case ComponentType::PID:
                    m_winPtr = std::make_shared<PIDComponentWindow>(m_components.at(uid), m_componentNameSet);
                    m_appRef->add_window(*m_winPtr);
                    break;
                case ComponentType::DEADBAND:
                    m_winPtr = std::make_shared<DeadbandComponentWindow>(m_components.at(uid), m_componentNameSet);
                    m_appRef->add_window(*m_winPtr);
                    break;

                case ComponentType::FILTER:  // New case for Filter
                    m_winPtr = std::make_shared<FilterComponentWindow>(m_components.at(uid), m_componentNameSet);
                    m_appRef->add_window (*m_winPtr);
                    break;

                case ComponentType::SUMMER:
                    m_winPtr = std::make_shared<SummerComponentWindow>(m_components.at(uid), m_componentNameSet);
                    m_appRef->add_window(*m_winPtr);
                    break;

                case ComponentType::SWITCH:
                    m_winPtr = std::make_shared<SwitchComponentWindow>(m_components.at(uid), m_componentNameSet);
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

void Channel::LoadFromXmlFile(JSBEdit::XMLNode& node)
{
    int rowNum = 1;
    int colNum = 1;
    for(auto& i : node.GetChildren())
    {
        if(m_stringToComponentMap.contains(i.GetName()))
        {
            auto type = m_stringToComponentMap.at(i.GetName());
            auto name = i.GetAttribute("name").second;
            auto uId = generateUniqueId();
            auto ptr = createComponentFromType(type, name);
            rowNum++;
            if(rowNum > 5)
            {
                colNum++;
                rowNum = 1;
            }
            auto spr = ComponentSprite{type,rowNum * 150, colNum * 80};
            m_components.insert({uId, ptr});
            m_spriteComponents.insert({uId, spr});
        }
    }
}
void Channel::SetChannelName(const std::string channelName)
{
    m_channelName = channelName;
}

std::shared_ptr<IComponentCommon> Channel::createComponentFromType(ComponentType type, const std::string& name)
{
    std::shared_ptr<IComponentCommon> component;
    switch(type)
    {
        case ComponentType::GAIN:
            component = std::make_shared<GainComponent>(name);
            break;
        case ComponentType::PID:
            component = std::make_shared<PIDComponent>(name);
            break;
        case ComponentType::KINEMATIC:
            component = std::make_shared<KinematicsComponent>(name);
            break;
        case ComponentType::SUMMER:
            component = std::make_shared<SummerComponent>(name);
            break;
        case ComponentType::DEADBAND:
            component = std::make_shared<DeadbandComponent>(name);
            break;
        case ComponentType::FILTER:
            component = std::make_shared<FilterComponent>(name);
            break;
        case ComponentType::SWITCH:
            component = std::make_shared<SwitchComponent>(name);
            break;
        default:
            component = std::make_shared<GainComponent>(name);
            break;
    }
    return component;
}

std::string Channel::createName(ComponentType type)
{
    auto name {std::string{COMPONENT_NAMES[static_cast<int>(type)] + std::to_string((generateUniqueId()))}};
    while(ComponentNameExists(name))
        name = {std::string{COMPONENT_NAMES[static_cast<int>(type)] + std::to_string((generateUniqueId()))}};
    m_componentNameSet->insert(name);
    return name;
}

int Channel::generateUniqueId()
{
    int uId = m_distribuition(m_rng);
    if(m_uniqueIDSet.contains(uId))
        uId = generateUniqueId();
    return uId;
}

void Channel::makeConnection(int inputUID, int outputUID)
{
    Connection connect{inputUID, outputUID};
    //CONNECTIONS ARE ALL SCUFFED AND NEEDS TO BE REWRITTEN.
    if(m_inputConnectionSet.contains(inputUID)){
        if(m_components.at(inputUID)->CanHaveMultipleInputs())
            m_connections.push_back(connect);
    }
    else
    {
        m_inputConnectionSet.insert(inputUID);
        m_connections.push_back(connect);
    }

}

void Channel::populateStringComponentMap()
{
    //This whole thing should probably be static but oh well
	m_stringToComponentMap.insert({"switch", ComponentType::SWITCH});
	m_stringToComponentMap.insert({"pure_gain", ComponentType::GAIN});
	m_stringToComponentMap.insert({"scheduled_gain", ComponentType::GAIN});
	m_stringToComponentMap.insert({"kinematic", ComponentType::KINEMATIC});
	m_stringToComponentMap.insert({"summer", ComponentType::SUMMER});
	m_stringToComponentMap.insert({"pid", ComponentType::PID});
    m_stringToComponentMap.insert({"filter", ComponentType::FILTER});
    
}

void Channel::OnDragBegin(int x, int y)
{
    //Fail safe I guess in case somehow this goes wrong.
    if(m_dragState != DragState::NONE)
        return;

    for(auto& i : m_spriteComponents)
    {
        if(i.second.ContainsPoint(x,y))
        {
            m_dragState = DragState::DRAGGING;
            m_selectedId = i.first;
            //Check to see if its a connection attempt on the inp/output
            if(i.second.IsInputBoxClicked(x,y))
                m_dragState = DragState::CONNECT_INP;
            else if(i.second.IsOutputBoxClicked(x,y))
                m_dragState = DragState::CONNECT_OUT;
            return;
        }    
    }
}

void Channel::OnDragUpdate(int x, int y)
{
    if(m_dragState == DragState::NONE)
        return;

    m_currentDragPos = {x,y};

    if(m_dragState == DragState::DRAGGING)
        m_spriteComponents.at(m_selectedId).SetPosition(x,y);
}

void Channel::OnDragEnd(int x, int y)
{
    if(m_dragState == DragState::NONE)
        return;
    
    m_currentDragPos = {x,y};
    if(m_dragState == DragState::DRAGGING)
    {
        m_spriteComponents.at(m_selectedId).SetPosition(x,y);
    }
    else if(m_dragState == DragState::CONNECT_INP || m_dragState == DragState::CONNECT_OUT)
    {
        for(auto& i : m_spriteComponents)
        {
            //Make connection.
            if(i.first == m_selectedId)
                continue;
            if(i.second.ContainsPoint(x,y))
            {
                if(m_dragState == DragState::CONNECT_OUT)
                    makeConnection(m_selectedId, i.first);
                else
                    makeConnection(i.first, m_selectedId);
                break;
            }
        }
    }

    m_dragState = DragState::NONE;
}

};
