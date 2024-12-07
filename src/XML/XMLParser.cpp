#include <XML/XMLParser.hpp>
#include <XML/XMLNode.hpp>


void JSBEdit::XMLParser::on_start_element([[maybe_unused]] Glib::Markup::ParseContext& context, const Glib::ustring& element_name, const AttributeMap& attributes)
{
    m_Node->SetName(element_name);
    for(auto attribute: attributes)
    {
        m_Node->AddAttribute(attribute);
       // std::cout << "attribute: " << attribute.first << " = \"" << attribute.second << "\"\n";
    }
}

void JSBEdit::XMLParser::on_end_element([[maybe_unused]] Glib::Markup::ParseContext& context, [[maybe_unused]] const Glib::ustring& element_name)
{
    
}

void JSBEdit::XMLParser::on_text([[maybe_unused]] Glib::Markup::ParseContext& context, [[maybe_unused]] const Glib::ustring& text)
{
    if(text.length() != 0)
        m_Node->SetText(text);
}

void JSBEdit::XMLParser::on_passthrough([[maybe_unused]] Glib::Markup::ParseContext& context, [[maybe_unused]] const Glib::ustring& passthrough_text)
{
    
}

 void JSBEdit::XMLParser::on_error([[maybe_unused]] Glib::Markup::ParseContext& context, const Glib::MarkupError& error)
{
    // if we have an error, set the node to null.
    m_Node->m_Node = pugi::xml_node();

    std::cerr << "Error: " << error.what() << "\n";
}
