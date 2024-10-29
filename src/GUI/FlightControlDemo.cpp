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
    //Get the menubar and toolbar widgets, and add them to a container widget:
    auto cBox = m_refBuilder->get_widget<Gtk::Box>("componentBox");
    if (cBox)
    {
        append(*cBox);
    }
    else
        g_warning("GMenu not found");

    auto dBox = m_refBuilder->get_widget<Gtk::Box>("dividerBox");
    if (dBox)
    {
        append(*dBox);
    }
    else
        g_warning("Divider not found");

    auto canBox = m_refBuilder->get_widget<Gtk::Box>("canvasBox");
    if (canBox)
    {
        canBox->append(m_canvas);
        canBox->show();
        append(*canBox);
    }
    else
        g_warning("CanvasBox not found");
}

};