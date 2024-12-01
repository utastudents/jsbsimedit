#include "ComponentSprite.hpp"

namespace DragDrop
{

//Having this allows to only load the sprite files once.
std::vector<Glib::RefPtr<Gdk::Pixbuf>> ComponentSprite::spriteTable{};

ComponentSprite::ComponentSprite(const ComponentType &comp, int x, int y)
    : m_componentType(comp), m_spriteBox(x-16, y-16, 32, 32)
        , m_inputBox(x-20, y-2, 4, 4), m_outputBox(x+16, y-2, 4, 4)
{
    //Spriteboxs are oriented via top left position, however the drop coordiate is top left
    //We want it to be orientied in the center of the mouse. Input boxes are 4x4 currently 
    //Oriented from the sides, hence all the math.
}

void ComponentSprite::Draw(const Cairo::RefPtr<Cairo::Context> &drawCont)
{
    size_t spriteIndex = static_cast<std::size_t>(m_componentType);
    //Should probably do a resize check here in case another sprite scaled it before hand
    //TODO Determine width/height at a later date.
    auto sprPos = m_spriteBox.GetPosition();
    Gdk::Cairo::set_source_pixbuf(drawCont, spriteTable.at(spriteIndex), sprPos.first, sprPos.second);
    drawCont->paint();

    //Draw Input box, I know width height is 4x4 which is bad if we change later, sorry for hardcode
    //Source shouldnt have a input box.
    if(m_componentType == ComponentType::SOURCE)
    {
        auto impPos = m_inputBox.GetPosition();
        drawCont->set_source_rgb(0.0, 1.0, 0.0); //Green
        drawCont->rectangle(impPos.first, impPos.second, 4, 4);
        drawCont->fill();
        drawCont->stroke();
    }

    //Draw output box, destination component doesnt have an output.
    if(m_componentType == ComponentType::DESTINATION)
        return;
    auto outPos = m_outputBox.GetPosition();
    drawCont->set_source_rgb(1.0, 0.0, 0.0); //Red
    drawCont->rectangle(outPos.first, outPos.second, 4, 4);
    drawCont->fill();
    drawCont->stroke();
}

bool ComponentSprite::ContainsPoint(int x, int y)
{
    return (m_spriteBox.ContainsPoint(x,y) || m_inputBox.ContainsPoint(x,y)
        || m_outputBox.ContainsPoint(x,y));
}

bool ComponentSprite::IsInputBoxClicked(int x, int y) const
{
    //Source component shouldnt have one.
    if(m_componentType == ComponentType::SOURCE)
        return false;
    return m_inputBox.ContainsPoint(x,y);
}

bool ComponentSprite::IsOutputBoxClicked(int x, int y) const
{
    //Desitnation component shouldnt have one.
    if(m_componentType == ComponentType::DESTINATION)
        return false;
    return m_outputBox.ContainsPoint(x,y);
}

std::pair<int, int> ComponentSprite::GetBounds() const
{
    return m_spriteBox.GetBounds();
}

std::pair<int, int> ComponentSprite::GetInputBoxPosition() const
{
    return m_inputBox.GetPosition();
}

std::pair<int, int> ComponentSprite::GetOutputBoxPosition() const
{
    return m_outputBox.GetPosition();
}

ComponentType ComponentSprite::GetComponentType() const
{
    return m_componentType;
}

std::pair<int, int> ComponentSprite::GetPosition() const
{
    //box is topleft oriented, but this should return center oriented
    auto point = m_spriteBox.GetPosition();
    point.first += 16;
    point.second += 16;
    return point;
}

void ComponentSprite::SetComponentType(const ComponentType& compType)
{
    m_componentType = compType;
}

void ComponentSprite::SetPosition(int x, int y)
{
    m_spriteBox.SetPosition(x-16, y-16);
    m_inputBox.SetPosition(x-20, y-2);
    m_outputBox.SetPosition(x+16, y-2);
}

void ComponentSprite::LoadSpriteComponents()
{
    //Check if we already loaded sprites, if so return
    if(!spriteTable.empty())
        return;

    //WARNING make sure this order is the same as ComponentEnum, so as to cast it to the index.
    std::vector<std::string> filenames{
        "actuator.bmp", "deadband.bmp", "destination.bmp"
        , "filter.bmp", "func.bmp", "gain.bmp", "kinemat.bmp"
        , "pid.bmp", "sensor.bmp", "source.bmp", "summer.bmp", "switch.bmp"
    };
    std::string pathPrefix = "../../../assets/componentImg/"; //Only because i didnt wanna manually type it yay lazy

    //Create the pixel_bufs
    for(auto& i : filenames)
    {
        Glib::RefPtr<Gdk::Pixbuf> sprite = Gdk::Pixbuf::create_from_file(pathPrefix+i); 
        if(!sprite)
        {
            std::cerr <<"Error loading component sprite:" + pathPrefix + i + "\n";
        }
        else
        {
            spriteTable.push_back(sprite);
        }
    }
}

};
