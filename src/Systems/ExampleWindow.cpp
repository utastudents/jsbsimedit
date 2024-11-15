#if 0
#include "ExampleWindow.hpp"
#include <iostream>

namespace JSBEdit {

ExampleWindow::ExampleWindow(const Glib::RefPtr<Gtk::Application>& app)
    : m_Box(Gtk::Orientation::VERTICAL),
    m_refRecentManager(Gtk::RecentManager::get_default()),
    m_tab1(app, "HI TAB1"), m_tab2(app, "HI TAB2"), m_fcDemo(app)
{
    set_title("Recent files example");
    set_default_size(300, 150);
    //We can put a PopoverMenuBar at the top of the box and other stuff below it.
    set_child(m_Box);

    //Create actions for menus and toolbars:
    m_refActionGroup = Gio::SimpleActionGroup::create();

    //File menu:
    m_refActionGroup->add_action("new",
        sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new));

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

    try
    {
        m_refBuilder = Gtk::Builder::create_from_file("mainWindow.xml");
    }
    catch (const Glib::Error& ex)
    {
        std::cerr << "Error loading mainWindow.xml" << ex.what();
    }
    //Get the menubar and toolbar widgets, and add them to a container widget:
    auto object = m_refBuilder->get_object("menubar");
    auto gmenu = std::dynamic_pointer_cast<Gio::Menu>(object);
    if (gmenu)
    {
        //Menubar:
        auto pMenubar = Gtk::make_managed<Gtk::PopoverMenuBar>(gmenu);
        m_Box.append(*pMenubar);
    }
    else
        g_warning("GMenu not found");

    auto pToolbar = m_refBuilder->get_widget<Gtk::Box>("toolbar");
    if (pToolbar)
        //Toolbar:
        m_Box.append(*pToolbar);
    else
        g_warning("toolbar not found");

    //Load Stack elements..
    if(!load_stack(app))
        std::cerr << "Error loading tabs\n";
    //Append the stack siwtcher to the mainPage box
    auto tabBox = m_refBuilder->get_widget<Gtk::Box>("tabBox");
    if (tabBox)
    {
        m_Box.append(*tabBox);
        tabBox->append(m_stackSwitcher);
    }
    else
        g_warning("tabbox not found");
    
    //Append the stack to the tabContents box
    auto tabContents = m_refBuilder->get_widget<Gtk::Box>("tabContents");
    if (tabContents)
    {
        m_Box.append(*tabContents);
        tabContents->append(m_stack);
    }
    else
        g_warning("tabbox not found");
}

bool ExampleWindow::load_stack(const Glib::RefPtr<Gtk::Application> &app)
{
    m_stack.add(m_tab1, "Tab1", "Tab1");
    m_stack.add(m_tab2, "Tab2", "Tab2");
    m_stack.add(m_fcDemo, "Flight Control", "Flight Control");
    m_stackSwitcher.set_stack(m_stack);
    m_stackSwitcher.set_visible(true);
    m_stack.set_visible(true);
    return true;
}

void ExampleWindow::on_menu_file_new()
{
    std::cout << " New File" << std::endl;
}

void ExampleWindow::on_menu_file_quit()
{
    set_visible(false); //Closes the main window to stop the app->make_window_and_run().
}

void ExampleWindow::on_menu_file_files_dialog()
{
    if (!m_refFileDialog)
    {
        m_refFileDialog = Gtk::FileDialog::create();
        m_refFileDialog->set_modal(true);
    }
    m_refFileDialog->open(*this, sigc::mem_fun(*this, &ExampleWindow::on_dialog_finish));
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
    std::cout << (m_refRecentManager->has_item(selected_uri) ? "A" : "Not a")
        << " recently used file" << std::endl;
}

};
#endif
