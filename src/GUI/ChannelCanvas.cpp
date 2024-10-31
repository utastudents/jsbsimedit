#include "ChannelCanvas.hpp"

namespace JSBEdit
{

ChannelCanvas::ChannelCanvas(const Glib::RefPtr<Gtk::Application> &app)
{
    set_draw_func(sigc::mem_fun(*this, &ChannelCanvas::Draw));
    signal_show().connect([=](){ queue_draw(); });
    set_content_height(400);
    set_content_width(600);

    //Connecting the dnd handler..
    auto dropController = Gtk::DropTarget::create(G_TYPE_INT, Gdk::DragAction::COPY);
    dropController->signal_drop().connect(sigc::mem_fun(*this, &ChannelCanvas::OnDragEnd), false);
    add_controller(dropController);
}

ChannelCanvas::~ChannelCanvas()
{
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

    //This might be slow every draw, I'll probably need to make a channel class.
    auto result = m_spriteChannels.find(m_currentChannel);
    //Channel doesn't exist...
    if( result == m_spriteChannels.end())
        return;

    //Channel exists, draw every sprite in the list.
    for(auto& sprite : result->second)
        sprite.second.Draw(drawCont);
}

bool ChannelCanvas::OnDragEnd(const Glib::ValueBase &value, double x, double y)
{
    Glib::Value<int> passedData;
    passedData.init(value.gobj());
    std::cout << "Something was dragged at: "<< x << ", " << y << " with data type: "
        << passedData.get() << ". \n";
    //Create the sprite... no data for now...
    return true;
}

};