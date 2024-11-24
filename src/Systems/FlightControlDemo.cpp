#include "FlightControlDemo.hpp"

namespace DragDrop {



FlightControlDemo::FlightControlDemo(const Glib::RefPtr<Gtk::Application> &app,
    const std::string& sysName)
    : m_canvas(app, sysName), m_systemName(sysName)
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


    std::vector<std::string> widgetContainers {"stackBox", "componentBox", "dividerBox", "canvasBox"};
    //Get all the box widgets, and add them to a container widget:
    for(auto& i : widgetContainers)
    {
        auto boxWidget = m_refBuilder->get_widget<Gtk::Box>(i);
        if (boxWidget)
        {
            //if canvasBox append the canvas to it, sorry about one line if
            if(i == "canvasBox") { boxWidget->append(m_canvas); boxWidget->show(); }
            if(i == "stackBox") { boxWidget->append(m_notebook); boxWidget->show(); }
            append(*boxWidget);
        }
        else
            std::cerr << "Error loading GUI widget: " << i << "from file.\n";
    }

    //Get all the image widgets, and add them to a container widget:
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
    m_notebook.set_hexpand(true);
    m_notebook.set_show_border(false);
    //signal handler for changing channel tabs
    m_notebook.signal_switch_page().connect(sigc::mem_fun(*this, &FlightControlDemo::on_notebook_switch_page));
}

void FlightControlDemo::CreateNewTab(const std::string &name)
{
    Gtk::Box emptyBox{};
    m_notebook.append_page(emptyBox, name);
    m_notebook.show();
}

void FlightControlDemo::LoadXMLData()
{
    auto node = xmlptr()->GetNode("fdm_config").FindChild(m_systemName);
    if(!node)
        std::cout << "Error loading: " << m_systemName << " from file.";
    else
    {
        for(auto& i : node.GetChildren())
        {
            if(i.GetName() == "channel")
            {
                auto nameAtt = i.GetAttribute("name");
                if(nameAtt.second.empty()){
                    std::cout << "Error loading: " << m_systemName << "\n";
                    continue;
                }
                if(m_canvas.CreateNewChannel(nameAtt.second))
                {
                    CreateNewTab(nameAtt.second);
                    m_canvas.LoadChannelFromXml(nameAtt.second, i);
                }
            }
            else
                std::cout << i.GetText() << "\n";
        }
    }
}

Glib::RefPtr<Gdk::ContentProvider> FlightControlDemo::SetDragData(int _data)
{
    Glib::Value<int> data;
    data.init(data.value_type());
    data.set(_data);
    return Gdk::ContentProvider::create(data);
}

void FlightControlDemo::on_notebook_switch_page(Gtk::Widget *wid, guint page_num)
{
    //not gonna lie i copied the function prototype above from the examplewindow.cpp
    auto nameClicked = m_notebook.get_tab_label_text(*wid);
    std::cout << nameClicked << "\n";
    m_canvas.SetCurrentChannelName(nameClicked);
}
};
