#include "ComponentSprite.hpp"

namespace JSBEdit
{

//Having this allows to only load the sprite files once.
std::vector<Glib::RefPtr<Gdk::Pixbuf>> ComponentSprite::spriteTable{};

void ComponentSprite::Draw(const Cairo::RefPtr<Cairo::Context> &drawCont)
{
    size_t spriteIndex = static_cast<std::size_t>(m_componentType);
    //Should probably do a resize check here in case another sprite scaled it.
    Gdk::Cairo::set_source_pixbuf(drawCont, spriteTable.at(spriteIndex), m_x, m_y);
    drawCont->paint();
}

const std::pair<int, int> ComponentSprite::GetBounds() const
{
    return std::pair<int, int>(m_width, m_height);
}

const ComponentType ComponentSprite::GetComponentType() const
{
    return m_componentType;
}

const std::pair<int, int> ComponentSprite::GetPosition() const
{
    return std::pair<int, int>(m_x, m_y);
}

void ComponentSprite::SetBounds(int width, int height)
{
    m_width = width;
    m_height = height;
}

void ComponentSprite::SetComponentType(const ComponentType& compType)
{
    m_componentType = compType;
}

void ComponentSprite::SetPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

void ComponentSprite::LoadSpriteComponents()
{
    //Check if we already loaded sprites, if so return
    if(!spriteTable.empty())
        return;

    //WARNING make sure this order is the same as ComponentEnum, so as to cast it to the index.
    std::vector<std::string> filenames{
        "actuator.bmp", "deadband,bmp", "destination.bmp"
        , "filter.bmp", "func.bmp", "gain.bmp", "kinemat.bmp"
        , "pid.bmp", "sensor.bmp", "source.bmp", "summer.bmp", "switch.bmp"
    };
    std::string pathPrefix = "componentImg/";

    //Create the pixel_bufs
    for(auto& i : filenames)
    {
        Glib::RefPtr<Gdk::Pixbuf> sprite = Gdk::Pixbuf::create_from_file(pathPrefix+i); 
        if(!sprite)
            std::cerr <<"Error loading component sprite:" + pathPrefix + i + "\n";
        else
            spriteTable.push_back(sprite);
    }
}

};