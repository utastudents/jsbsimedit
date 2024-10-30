#include "FlightControlDemo.hpp"

namespace JSBEdit {

FlightControlDemo::FlightControlDemo(const Glib::RefPtr<Gtk::Application> &app)
    : m_canvas(app)
{
    set_orientation(Gtk::Orientation::VERTICAL);
    try
    {
        m_refBuilder = Gtk::Builder::create_from_file("flightControl.xml");
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

    //Make sure this is the same order as the ComponentEnum for casting.
    //Theres probably a better way to do this.
    std::vector<std::string> dragDropIcons { "actuator", "deadband", 
        "destination", "filter", "func", "gain", "kinemat"
        , "pid", "sensor", "source", "summer", "switch"
    };
    //Get all the box widgets, and add them to a container widget:
    for(int i = 0; i < dragDropIcons.size(); i++)
    {
        auto imgWidget = m_refBuilder->get_widget<Gtk::Image>(dragDropIcons[i]);
        if (imgWidget)
        {
            //TODO attach the drag handler here.
        }
        else
            std::cout << "Error finding: " << dragDropIcons[i] << " widget.\n";
    }

}

};