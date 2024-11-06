#include "ChannelCanvas.hpp"

namespace JSBEdit
{

ChannelCanvas::ChannelCanvas(const Glib::RefPtr<Gtk::Application> &app)
{
    m_refApp = app;

    set_draw_func(sigc::mem_fun(*this, &ChannelCanvas::Draw));
    signal_show().connect([=](){ queue_draw(); });
    set_content_height(400);
    set_content_width(600);

    //Connecting the dnd handler..
    auto dropController = Gtk::DropTarget::create(G_TYPE_INT, Gdk::DragAction::COPY);
    dropController->signal_drop().connect(sigc::mem_fun(*this, &ChannelCanvas::OnDragEnd), false);
    add_controller(dropController);

    //Creating a clicking handler.
    auto clickController = Gtk::GestureClick::create();
    clickController->signal_released().connect(sigc::mem_fun(*this, &ChannelCanvas::OnClickRelease), false);
    add_controller(clickController);

    ComponentSprite::LoadSpriteComponents();

    //Making a default channel for testing functionallity
    m_currentChannel = "test";
    m_channels.insert({m_currentChannel, Channel{m_refApp, m_currentChannel}});
}

ChannelCanvas::~ChannelCanvas()
{
}

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
    drawCont->set_source_rgb(1.0, 1.0, 0);
    drawCont->paint();

    auto result = m_channels.find(m_currentChannel);
    //Channel doesn't exist... or we are empty.
    if( result == m_channels.end())
        return;

    //Channel exists, yay. Now draw it.
    result->second.Draw(drawCont);
}

bool ChannelCanvas::OnDragEnd(const Glib::ValueBase &value, double x, double y)
{
    Glib::Value<int> passedData;
    passedData.init(value.gobj());
    std::cout << "Something was dragged at: "<< x << ", " << y << " with data type: "
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

    //WHYYYYYY does m_channels[m_currentChannel] raise all hell here but .at() is fine...
    if(numClick < 2)
        m_channels.at(m_currentChannel).HandleClickRelease(static_cast<int>(x), static_cast<int>(y));
    else
        m_channels.at(m_currentChannel).HandleDoubleClick(static_cast<int>(x), static_cast<int>(y));
}

};