#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <sstream>
#include <filesystem>

#include <glibmm.h>

namespace JSBEdit
{

    class XMLParser : public Glib::Markup::Parser
    {
    protected:
        // Called for opening tags like <foo bar="baz">
        void on_start_element(Glib::Markup::ParseContext &context, const Glib::ustring &element_name, const AttributeMap &attributes) override;
        // Called for closing tages like </foo>
        void on_end_element(Glib::Markup::ParseContext &context, const Glib::ustring &element_name) override;
        // Called for character data.
        void on_text(Glib::Markup::ParseContext &context, const Glib::ustring &text) override;
        // Called for strings that should be re-saved verbatim in this same position, but are not otherwise interpretable
        void on_passthrough(Glib::Markup::ParseContext &context, const Glib::ustring &passthrough_text) override;
        // Called on error, including one thrown by an overridden virtual method
        void on_error(Glib::Markup::ParseContext &context, const Glib::MarkupError &error) override;
    };
};
