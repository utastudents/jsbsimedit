#include "ChannelCanvas.hpp"

namespace DragDrop
{

ChannelCanvas::ChannelCanvas(const Glib::RefPtr<Gtk::Application> &app, const std::string& sysName)
    : m_systemName(sysName)
{
    m_refApp = app;

    set_draw_func(sigc::mem_fun(*this, &ChannelCanvas::Draw));
    signal_show().connect([=](){ queue_draw(); });
    set_hexpand(true);
    set_vexpand(true); // allowes default size to fix itself

    //Connecting the dnd handler..
    auto dropController = Gtk::DropTarget::create(G_TYPE_INT, Gdk::DragAction::COPY);
    dropController->signal_drop().connect(sigc::mem_fun(*this, &ChannelCanvas::OnDropEnd), false);
    add_controller(dropController);

    //Creating a clicking handler.
    auto clickController = Gtk::GestureClick::create();
        //Mouse release handler
    clickController->signal_released().connect(sigc::mem_fun(*this, &ChannelCanvas::OnClickRelease), false);
        //Mouse down handler
    clickController->signal_pressed().connect(sigc::mem_fun(*this, &ChannelCanvas::OnClickDown), false);
    add_controller(clickController);

    //Dragging
    auto dragController = Gtk::GestureDrag::create();
    dragController->signal_drag_begin().connect(sigc::mem_fun(*this, &ChannelCanvas::OnDragBegin), false);
    dragController->signal_drag_update().connect(sigc::mem_fun(*this, &ChannelCanvas::OnDragUpdate), false);
    dragController->signal_drag_end().connect(sigc::mem_fun(*this, &ChannelCanvas::OnDragEnd), false);
    add_controller(dragController);


    ComponentSprite::LoadSpriteComponents();
}

ChannelCanvas::~ChannelCanvas()
{
}

bool ChannelCanvas::CreateNewChannel(const std::string & name, bool fromXmlFile)
{
    //Blank channel names not allowed.
    if(name.empty())
        return false;
    //If channel exists, then ignore. Could consider a update function if called from XML
    if(m_channels.contains(name))
        return false;

    Channel newChannel { m_refApp, name };
    
    //if from Xml file call channel load from xmlfile.
    //if(fromXmlFile)
    

    m_channels.insert({ name, newChannel });
    std::cout << "Created new channel: " << name << ".\n";

    //If this is the only channel, then lets make it current.
    if(!CurrentChannelExists())
        m_currentChannel = name;
    return true;
}

//In the event somehow the channel is deleted and the current channel string is set to it?
bool ChannelCanvas::CurrentChannelExists()
{
    if (m_currentChannel.empty())
        return false;
    return m_channels.contains(m_currentChannel);
}

const std::string ChannelCanvas::GetCurrentChannelName() const
{
    return m_currentChannel;
}

void ChannelCanvas::SetCurrentChannelName(const std::string &channelName)
{
    m_currentChannel = channelName;
    //Changed the channel so we should recall draw
    queue_draw();
}

void ChannelCanvas::Draw(const Cairo::RefPtr<Cairo::Context> &drawCont, int width, int height)
{
    //Drawing the back ground this color cause why not.
    drawCont->set_source_rgb(0.54, 0.81, 0.94);
    drawCont->paint();

    auto result = m_channels.find(m_currentChannel);
    //Channel doesn't exist... or we are empty.
    if( result == m_channels.end())
        return;

    //Channel exists, yay. Now draw it.
    result->second.Draw(drawCont);
}

bool ChannelCanvas::OnDropEnd(const Glib::ValueBase &value, double x, double y)
{
    Glib::Value<int> passedData;
    passedData.init(value.gobj());
    std::cout << "Something was dropped at: "<< x << ", " << y << " with data type: "
        << passedData.get() << ".\n";

    if(!CurrentChannelExists())
        return false;

    //Channel exists, make the dropped sprite.
    m_channels.at(m_currentChannel).CreateDroppedComponent(
        static_cast<ComponentType>(passedData.get()), static_cast<int>(x), static_cast<int>(y));
    return true;
}

void ChannelCanvas::OnClickRelease(int numClick, double x, double y)
{
    if(!CurrentChannelExists())
        return;

    std::cout << "Mouse released at: "<< x << ", " << y << ".\n";


    //WHYYYYYY does m_channels[m_currentChannel] raise all hell here but .at() is fine...
    if(numClick < 2)
        m_channels.at(m_currentChannel).HandleClickRelease(static_cast<int>(x), static_cast<int>(y));
    else
        m_channels.at(m_currentChannel).HandleDoubleClick(static_cast<int>(x), static_cast<int>(y));
}

void ChannelCanvas::OnClickDown(int numClick, double x, double y)
{
    if(!CurrentChannelExists())
        return;
     std::cout << "Mouse down at: "<< x << ", " << y << ".\n";

    //Click handling here for left click
}

void ChannelCanvas::OnDragBegin(double x, double y)
{
     std::cout << "Drag began at: "<< x << ", " << y << ".\n";

}

void ChannelCanvas::OnDragUpdate(double x, double y)
{
     std::cout << "Drag update at: "<< x << ", " << y << ".\n";
}

void ChannelCanvas::OnDragEnd(double x, double y)
{
     std::cout << "Drag ended at: "<< x << ", " << y << ".\n";

}
};