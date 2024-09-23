#include <gtkmm.h>
#include <gtkmm/application.h>


#include <stdio.h>
#include "examplewindow.h"

#include <glib.h>

#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <sstream>
#include <filesystem>

static void foo_parser_start_element(GMarkupParseContext* context,
    const gchar* element_name,
    const gchar** attribute_names,
    const gchar** attribute_values,
    gpointer              user_data,
    GError** error);
static void foo_parser_end_element(GMarkupParseContext* context,
    const gchar* element_name,
    gpointer              user_data,
    GError** error);
static void foo_parser_characters(GMarkupParseContext* context,
    const gchar* text,
    gsize                 text_len,
    gpointer              user_data,
    GError** error);
static void foo_parser_passthrough(GMarkupParseContext* context,
    const gchar* passthrough_text,
    gsize                 text_len,
    gpointer              user_data,
    GError** error);
static void foo_parser_error(GMarkupParseContext* context,
    GError* error,
    gpointer              user_data);

static int xml_main(void);


int main( [[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    printf("Hello World!\n");
    auto app = Gtk::Application::create("org.gtkmm.example");

    xml_main();

    //Shows the window and returns when it is closed.
    return app->make_window_and_run<ExampleWindow>(argc, argv, app);
}

/*
 * Parser
 */
static const GMarkupParser foo_xml_parser = {
  foo_parser_start_element,
  foo_parser_end_element,
  foo_parser_characters,
  foo_parser_passthrough,
  foo_parser_error
};

/*
 * Called for opening tags like <foo bar="baz">
 */
static void
foo_parser_start_element(GMarkupParseContext* context,
    const gchar* element_name,
    const gchar** attribute_names,
    const gchar** attribute_values,
    gpointer             user_data,
    GError** error)
{
    g_print("element: <%s>\n", element_name);

    for (gsize i = 0; attribute_names[i]; i++)
    {
        g_print("attribute: %s = \"%s\"\n", attribute_names[i],
            attribute_values[i]);
    }
}

/*
 * Called for closing tags like </foo>
 */
static void
foo_parser_end_element(GMarkupParseContext* context,
    const gchar* element_name,
    gpointer             user_data,
    GError** error)
{
    g_print("element: </%s>\n", element_name);
}

/*
 * Called for character data. Text is not nul-terminated
 */
static void
foo_parser_characters(GMarkupParseContext* context,
    const gchar* text,
    gsize                text_len,
    gpointer             user_data,
    GError** error)
{
    g_print("text: [%s]\n", text);
}

/*
 * Called for strings that should be re-saved verbatim in this same
 * position, but are not otherwise interpretable. At the moment this
 * includes comments and processing instructions. Text is not
 * nul-terminated.
 */
static void
foo_parser_passthrough(GMarkupParseContext* context,
    const gchar* passthrough_text,
    gsize                 text_len,
    gpointer              user_data,
    GError** error)
{
    g_print("passthrough: %s\n", passthrough_text);
}

/*
 * Called when any parsing method encounters an error. The GError should not be
 * freed.
 */
static void
foo_parser_error(GMarkupParseContext* context,
    GError* error,
    gpointer             user_data)
{
    g_printerr("ERROR: %s\n", error->message);
}

static int xml_main(void)
{
    GMarkupParseContext* context;
    gboolean success = FALSE;
    glong len;

    std::filesystem::path path{"../../../reference/JSBSimCommander/f16.xml"};

    if(!std::filesystem::exists(path))
    {
        g_printerr("ERROR: file does not exist\n");
        return 1;
    }

    // TODO: add error handling here, this will fail if the path is wrong. - Ellis Nielsen
    std::ifstream t(path.c_str());
    std::stringstream buffer;
    buffer << t.rdbuf();

    // have to hold this temp, as str deletes the object after expression
    const std::string tmp = buffer.str();
    const gchar* filedata = tmp.c_str();

    len = g_utf8_strlen(filedata, -1);
    g_print("Parsing: %s\n", filedata);
    g_print("(%ld UTF-8 characters)\n", len);

    context = g_markup_parse_context_new(&foo_xml_parser, G_MARKUP_DEFAULT_FLAGS, NULL, NULL);

    success = g_markup_parse_context_parse(context, filedata, len, NULL);

    g_markup_parse_context_free(context);

    if (success)
    {
        g_print("DONE\n");
        return 0;
    }
    else
    {
        g_printerr("ERROR\n");
        return 1;
    }
}
