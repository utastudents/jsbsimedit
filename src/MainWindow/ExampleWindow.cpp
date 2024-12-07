#include "ExampleWindow.hpp"
#include <iostream>

#include "inc/XML_api.hpp"

#include "Aerodynamics/AeroDynamicsSubsystem.hpp"
#include "BuoyantForces/BuoyantForcesSubsystem.hpp"
#include "Metrics/MetricsSubsystem.hpp"
#include "Propulsion/PropulsionSubsystem.hpp"
#include "InputOutput/IOSubSystem.hpp"
#include "MassBalance/MassBalanceSubsystem.hpp"
#include "ExternalReactions/ExternalReactionsSubsystem.hpp"
#include "GeneralInformation/GeneralInformationSubsystem.hpp"
#include "GroundReactions/GroundReactionsSubsystem.hpp"



namespace JSBEdit {

ExampleWindow::ExampleWindow(const Glib::RefPtr<Gtk::Application>& app)
    : m_Box(Gtk::Orientation::VERTICAL),
    m_refRecentManager(Gtk::RecentManager::get_default()),
    m_tab1(app, "HI TAB1"), m_tab2(app, "TAB2"), m_fcDemo(app, "flight_control")
{
    set_title("JSBSim Commander");
    set_default_size(800, 600);
    //We can put a PopoverMenuBar at the top of the box and other stuff below it.
    set_child(m_Box);

    //Create actions for menus and toolbars:
    m_refActionGroup = Gio::SimpleActionGroup::create();

    //File menu:
    m_refActionGroup->add_action("new",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new));


    m_refActionGroup->add_action("save",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_save)); //save


    //A menu item to open the file dialog:
    m_refActionGroup->add_action("files-dialog",
        sigc::mem_fun(*this, &ExampleWindow::on_menu_file_files_dialog));

    m_refActionGroup->add_action("quit",
        sigc::mem_fun(*this, &ExampleWindow::on_menu_file_quit));

    insert_action_group("example", m_refActionGroup);

    // When the menubar is a child of a Gtk::Window, keyboard accelerators are not
    // automatically fetched from the Gio::Menu.
    // See the examples/book/menus/main_menu example for an alternative way of
    // adding the menubar when using Gtk::ApplicationWindow.
    app->set_accel_for_action("example.new", "<Primary>n");
    app->set_accel_for_action("example.files-dialog", "<Primary>o");
    app->set_accel_for_action("example.quit", "<Primary>q");
    app->set_accel_for_action("example.save", "<Primary>s");

    // There are a lot of reasons this is the wrong place to open
    // up the xml file.  But to get work progressing, this is a 
    // start.


    xmlptr()->LoadFileAndParse({"../../../data/aircraft/f16/f16.xml"}); //loading xml data
    
    try
    {
        m_refBuilder = Gtk::Builder::create_from_file("../../../mainWindow.xml");
    }
    catch (const Glib::Error& ex)
    {
        std::cerr << "Error loading mainWindow.xml" << ex.what();
    }

    auto pToolbar = m_refBuilder->get_widget<Gtk::Box>("toolbar");
    if (pToolbar)
        //Toolbar:
        m_Box.append(*pToolbar);
    else
        g_warning("toolbar not found");
        
    m_Notebook = new Gtk::Notebook();
    m_Notebook->set_margin(10);
    m_Notebook->set_expand();
    m_Box.append(*m_Notebook);

    // create the Subsystems objects
    m_Subsystems.push_back(new GeneralInformationSubsystem());
    m_Subsystems.push_back(new AeroDynamicsSubsystem());
    m_Subsystems.push_back(new BuoyantForcesSubsystem());
    m_Subsystems.push_back(new MetricsSubsystem());
    m_Subsystems.push_back(new PropulsionSubsystem());
    m_Subsystems.push_back(new IOSubSystem());
    m_Subsystems.push_back(new MassBalanceSubsystem());
    m_Subsystems.push_back(new ExternalReactionsSubsystem());
    m_Subsystems.push_back(new GroundReactionsSubsystem());

    
    // Call Create() for all subsystems
    for (const auto &i : m_Subsystems) 
    {
        i->Create();
        m_Notebook->append_page(i->m_Grid, i->m_Name);  
    }

    // this subsystem is special
    m_Notebook->append_page(m_fcDemo,"Flight Control"); 
    m_fcDemo.LoadXMLData();
}

void ExampleWindow::on_menu_file_new()
{
if (!m_refFileDialog)
    {
        m_refFileDialog = Gtk::FileDialog::create();
        m_refFileDialog->set_modal(true);
    }
    m_refFileDialog->open(*this, sigc::mem_fun(*this, &ExampleWindow::on_dialog_finish));
    }

void ExampleWindow::on_menu_file_save() //implement save function to over-write the xml
{
  //std::cout << "Saving data..." << std::endl;
  
  if (xmlptr()->SaveToFile(xmlptr()->GetFilePath())) //Calling the SaveToFile function with the file path. Note: this save will overwrite the existing file.
  {
    std::cout << "Data saved successfully to: " << xmlptr()->GetFilePath() << std::endl;
  }
  else
  {
    std::cout << "Failed to save to: " << xmlptr()->GetFilePath() << std::endl;
  }
}


void ExampleWindow::on_menu_file_files_dialog()
{
    if (!m_refFileDialog)
    {
        m_refFileDialog = Gtk::FileDialog::create();
        m_refFileDialog->set_modal(true);
        m_refFileDialog->set_title("Open XML File");
    }
    m_refFileDialog->open(*this, sigc::mem_fun(*this, &ExampleWindow::on_dialog_finish));
}

void ExampleWindow::on_menu_file_quit()
{
    set_visible(false); //Closes the main window to stop the app->make_window_and_run().
}

void ExampleWindow::on_dialog_finish(Glib::RefPtr<Gio::AsyncResult>& result)
{
    Glib::RefPtr<Gio::File> file;
    try
    {
        file = m_refFileDialog->open_finish(result);
    }
    catch (const Gtk::DialogError& err)
    {
        std::cout << "No file selected, " << err.what() << std::endl;
        return;
    }

    auto selected_uri = file->get_uri();
    std::cout << "URI selected = " << selected_uri << std::endl;
    std::string selected_path = selected_uri.substr(7);
    
    xmlptr()->LoadFileAndParse(selected_path);
    
    std::cout << "Loaded XML data from: " << xmlptr()->GetFilePath() << std::endl;
}
void ExampleWindow::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num)
{
  std::cout << "Switched to tab with index " << page_num << std::endl;
  
  //You can also use m_Notebook.get_current_page() to get this index.
}

};

