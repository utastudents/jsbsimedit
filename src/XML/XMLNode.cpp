#include <XML/XMLNode.hpp>
#include <XML/XMLDoc.hpp>
#include <XML/XMLParser.hpp>

#include <glibmm.h>
#include <memory>

JSBEdit::XMLNode::XMLNode(JSBEdit::XMLDoc& doc)
{
    m_Node = doc.GetPugiDoc().append_child("");
}

JSBEdit::XMLNode::XMLNode(JSBEdit::XMLDoc& doc, const std::string &element): XMLNode(doc)
{
    // use the xml parser
    //Glib::Markup needs a context to parse
    std::unique_ptr<Glib::Markup::Parser> parser = std::unique_ptr<JSBEdit::XMLParser>(new JSBEdit::XMLParser{this});
    Glib::Markup::ParseContext parseContext{*parser.get()};
    try {
        parseContext.parse(element);
        parseContext.end_parse();
    } catch (Glib::MarkupError& error) 
    {
        m_Node = pugi::xml_node();
        std::cerr << "Error: " << error.what() << "\n";
    }
    
}

JSBEdit::XMLNode::XMLNode(JSBEdit::XMLDoc& doc, std::string name, std::vector<AttributeKV>& attributes, std::string text): XMLNode(doc)
{
    SetName(name);
    SetAttributes(attributes);
    SetText(text);
}

std::vector<AttributeKV> JSBEdit::XMLNode::GetAttributes()
{
    std::vector<AttributeKV> attributes;

    for(auto& attribute: m_Node.attributes())
    {
        attributes.push_back({attribute.name(), attribute.as_string()});
    }
    return attributes;
}

AttributeKV JSBEdit::XMLNode::GetAttribute(std::string attributeName)
{
    
    return AttributeKV(attributeName, m_Node.attribute(attributeName.c_str()).as_string());
}

bool JSBEdit::XMLNode::AddAttributes(std::vector<AttributeKV> &attributes)
{
    bool allAttributesAdded = true;
    for(auto& attribute: attributes)
    {
        pugi::xml_attribute returnedNode = m_Node.append_attribute(attribute.first.c_str()) = attribute.second.c_str();

        if (returnedNode.empty())
            allAttributesAdded = false;
    }

    return allAttributesAdded;
}

bool JSBEdit::XMLNode::AddAttribute(AttributeKV attribute)
{
    // returns true if attribute is added
    try {
        if (m_Node.append_attribute(attribute.first.c_str()) = attribute.second.c_str()) {
            return true;
        }
        else {
            throw("Attribute not added");
        }
    }
    // catches known errors and returns false
    catch(const std::string& e) {
        std::cerr << "AddAttribute Error: " << e << std::endl;
        return false;
    }
    // catches unknown errors and returns false
    catch (...) {
        std::cerr << "AddAtribute Error: Unknown Error" << std::endl;
    }

}

void JSBEdit::XMLNode::SetAttributes(std::vector<AttributeKV> &attributes)
{
    m_Node.remove_attributes();
    for(auto& attribute: attributes)
    {
        m_Node.append_attribute(attribute.first.c_str()) = attribute.second.c_str();
    }
}

void JSBEdit::XMLNode::SetAttribute(AttributeKV attribute)
{
    m_Node.remove_attributes();
    m_Node.append_attribute(attribute.first.c_str()) = attribute.second.c_str();
}

bool JSBEdit::XMLNode::ChangeAttributeValue(AttributeKV attribute)
{
    pugi::xml_attribute xmlAttribute = m_Node.attribute(attribute.first.c_str());
    if(!xmlAttribute)
    {
        return false;
    }

    return xmlAttribute.set_value(attribute.second.c_str());
    
}

bool JSBEdit::XMLNode::RemoveAttributes()
{
    return m_Node.remove_attributes();
}

bool JSBEdit::XMLNode::RemoveAttribute(std::string attribute)
{
    // returns true if attribute was removed
    try {
        if (m_Node.remove_attribute(attribute.c_str())) {
            return true;
        }
        else {
            throw("Attribute not Removed");
        }
    }
    // catches known errors and returns false
    catch (const std::string& e) {
        std::cerr << "RemoveAttributes Error: " << e << std::endl;
        return false;
    }
    // catches unknown errors and returns false
    catch (...) {
        std::cerr << "RemoveAttributes Error: Unhandled Error" << std::endl;
        return false;
    }
}

std::string JSBEdit::XMLNode::GetText()
{
    return m_Node.text().as_string();
}

bool JSBEdit::XMLNode::SetText(std::string text)
{
    // returns true for setting text or throws error when there is a failure in setting text
    try{
        if (m_Node.text().set(text.c_str()))
            return true;
        else
            throw("Text not set");
    }
    // catches known errors and returns false
    catch (const std::string& e) {
        std::cerr << "SetText Error: " << e << std::endl;
        return false;
    }
    // catches any unknown errors and returns false
    catch (...) {
        std::cerr << "SetText Error: Unhandled Error" << std::endl;
        return false;
    }
}

std::string JSBEdit::XMLNode::GetName()
{
    return m_Node.name();
}

bool JSBEdit::XMLNode::SetName(std::string name)
{
    return m_Node.set_name(name.c_str());
}

bool JSBEdit::XMLNode::AddChild(XMLNode child)
{
    // returns true when child is added
    try {
        pugi::xml_node returnedNode = this->m_Node.append_move(child.m_Node);
        return true;
    }
    // catches any unknown errors and returns false
    catch (...) {
        std::cerr << "Cannot add child: Unhandled Error";
        return false;
    }
    
}

bool JSBEdit::XMLNode::AddChildren(std::vector<XMLNode> &children)
{
    //question
    bool allChildrenAdded = true;
    for(auto& node: children)
    {
        pugi::xml_node returnedNode = this->m_Node.append_move(node.m_Node);

        if (returnedNode.empty())
            allChildrenAdded = false;
    }

    return allChildrenAdded;
}

JSBEdit::XMLNode JSBEdit::XMLNode::FindChild(std::string name)
{
    for(auto& node: m_Node.children())
    {
        if(node.name() == name)
        {
            return JSBEdit::XMLNode{node};
        }
    }

    return JSBEdit::XMLNode{pugi::xml_node()};
}

JSBEdit::XMLNode JSBEdit::XMLNode::GetChild(size_t index)
{
    pugi::xml_node_iterator iter = m_Node.begin();
    size_t curIdx = 0;
    while (iter != m_Node.end())
    {
        if(curIdx == index)
        {
            return JSBEdit::XMLNode(*iter);
        }
        iter++;
        curIdx++;
    }

    // trying to access an idx that doesn't exist, return a empty node
    return JSBEdit::XMLNode(pugi::xml_node());
}

std::vector<JSBEdit::XMLNode> JSBEdit::XMLNode::GetChildren()
{
    std::vector<XMLNode> nodes;
    for(auto& childNode: m_Node.children())
    {
        nodes.push_back({childNode});
    }
    
    return nodes;
}

bool JSBEdit::XMLNode::RemoveChild(int index)
{
    //question
    pugi::xml_node_iterator iter = m_Node.begin();
    size_t curIdx = 0;

    if (iter == m_Node.end())
        return false;

    while (iter != m_Node.end())
    {
        if(curIdx == index)
        {
            return m_Node.remove_child(*iter);
        }
        iter++;
        curIdx++;
    }

    return false;
}

bool JSBEdit::XMLNode::RemoveChild(JSBEdit::XMLNode& child)
{
    //question
    pugi::xml_node_iterator iter = m_Node.begin();

    if (iter == m_Node.end())
        return false;
    
    return m_Node.remove_child(child.m_Node);
}

bool JSBEdit::XMLNode::RemoveChildren()
{
    // returns true when children are removed or throws error when child is not removed
    try {
        if (m_Node.remove_children()) {
            return true;
        }
        else {
            throw("Child not removed");
        }
    }
    // catches known errors and returns false
    catch (const std::string& e) {
        std::cerr << "RemoveChildren Error: " << e << std::endl;
        return false;
    }
    // catches unknown errors and returns false
    catch (...) {
        std::cerr << "RemoveChildren Error: Unhandled Error" << std::endl;
        return false;
    }
    
}

JSBEdit::XMLNode JSBEdit::XMLNode::GetParent()
{
    return JSBEdit::XMLNode(m_Node.parent());
}

JSBEdit::XMLNode JSBEdit::XMLNode::GetRoot()
{
    return XMLNode(m_Node.root());
}

bool JSBEdit::XMLNode::IsMixedContent()
{
    bool pcdata = false;
    bool childElement = false;
    for(auto& node : m_Node.children())
    {
        if(!pcdata && node.type() == pugi::xml_node_type::node_pcdata)
        {
            pcdata = true;
        }
        if(!childElement && node.type() == pugi::xml_node_type::node_element)
        {
            childElement = true;
        }
        
        if(pcdata && childElement)
        {
            break;
        }
    }
    return pcdata && childElement;
}
JSBEdit::XMLNode::operator bool() const
{
    return static_cast<bool>(m_Node);
}

JSBEdit::XMLNode JSBEdit::XMLNode::operator[](size_t _idx)
{
    // TODO: insert return statement here
    return GetChild(_idx);
}
