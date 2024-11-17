#include "FlightControlDemo.hpp"

namespace DragDrop {

FlightControlDemo::FlightControlDemo(const Glib::RefPtr<Gtk::Application> &app)
    : m_canvas(app)
{
    set_orientation(Gtk::Orientation::VERTICAL);
    try
    {
        m_refBuilder = Gtk::Builder::create_from_file("../../../flightControl.xml");
    }
    catch (const Glib::Error& ex)
    {
        std::cerr << "Error loading flightControl.xml" << ex.what();
    }


    std::vector<std::string> widgetContainers {"componentBox", "dividerBox", "canvasBox"};
    //Get all the box widgets, and add them to a container widget:
    for(auto& i : widgetContainers)
    {
        auto boxWidget = m_refBuilder->get_widget<Gtk::Box>(i);
        if (boxWidget)
        {
            //if canvasBox append the canvas to it, sorry about one line if
            if(i == "canvasBox") { boxWidget->append(m_canvas); boxWidget->show(); }
            append(*boxWidget);
        }
        else
            std::cerr << "Error loading GUI widget: " << i << "from file.\n";
    }

    //Get all the box widgets, and add them to a container widget:
    for(int i = 0; i < COMPONENT_NAMES.size(); i++)
    {
        auto imgWidget = m_refBuilder->get_widget<Gtk::Image>(COMPONENT_NAMES[i]);
        if (imgWidget)
        {
            auto dragController = Gtk::DragSource::create();
            dragController->property_content().set_value(SetDragData(i));
            imgWidget->add_controller(dragController);
        }
        else
            std::cout << "Error finding: " << COMPONENT_NAMES[i] << " widget.\n";
    }

}

Glib::RefPtr<Gdk::ContentProvider> FlightControlDemo::SetDragData(int _data)
{
    Glib::Value<int> data;
    data.init(data.value_type());
    data.set(_data);
    return Gdk::ContentProvider::create(data);
}

};
