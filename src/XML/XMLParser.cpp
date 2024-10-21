#include <XML/XMLParser.hpp>


void JSBEdit::XMLParser::on_start_element([[maybe_unused]] Glib::Markup::ParseContext& context, const Glib::ustring& element_name, const AttributeMap& attributes)
{
    std::cout << "element: <" << element_name << ">\n";
    for(auto attribute: attributes)
    {
        std::cout << "attribute: " << attribute.first << " = \"" << attribute.second << "\"\n";
    }
}

void JSBEdit::XMLParser::on_end_element([[maybe_unused]] Glib::Markup::ParseContext& context, const Glib::ustring& element_name)
{
    std::cout << "element: </" << element_name << ">\n";
}

void JSBEdit::XMLParser::on_text([[maybe_unused]] Glib::Markup::ParseContext& context, const Glib::ustring& text)
{
    if(text.length() != 0)
        std::cout << "text: [" << text <<"]\n";
    else
        std::cout << "text: [N/A]\n";
}

void JSBEdit::XMLParser::on_passthrough([[maybe_unused]] Glib::Markup::ParseContext& context, const Glib::ustring& passthrough_text)
{
    std::cout << "passthrough: " << passthrough_text <<"\n";
}

 void JSBEdit::XMLParser::on_error([[maybe_unused]] Glib::Markup::ParseContext& context, const Glib::MarkupError& error)
{
    std::cerr << "ERROR: " << error.what() << "\n";
}
