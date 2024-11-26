#pragma once

#include <pugixml.hpp>

#include <vector>
#include <utility>
#include <string>


using AttributeKV = std::pair<std::string, std::string>;

namespace JSBEdit
{
    class XMLDoc;

    class XMLNode
    {
        friend class XMLParser;

    private:
        pugi::xml_node m_Node;
    public:
        XMLNode(XMLDoc& doc);

        XMLNode(pugi::xml_node node): m_Node{node} {}
        // Using the xml parse to build a xml_node
        XMLNode(XMLDoc& doc, const std::string& element);

        XMLNode(XMLDoc& doc, std::string name, std::vector<AttributeKV>& attributes, std::string text);

        std::vector<AttributeKV> GetAttributes();
        // the value in the pair will be empty if the attribute does not exist, XML048
        AttributeKV GetAttribute(std::string attributeName);

        // adds additional attributes to the element node XML046
        bool AddAttributes(std::vector<AttributeKV>& attributes);
        // adds an additional attribute to the element node XML047
        bool AddAttribute(AttributeKV attribute);
        // Sets multiple attributes and overrides attributes in the element node
        void SetAttributes(std::vector<AttributeKV>& attributes);
        // Sets an attribute and overrides attributes in the element node
        void SetAttribute(AttributeKV attribute);
        // changes the value of an attribute without deleting and appending back attributes XML045
        bool ChangeAttributeValue(AttributeKV attribute);

        // removes all attributes from the node element
        bool RemoveAttributes();
        // searches and removes the attributes if found
        bool RemoveAttribute(std::string attribute);
        
        // returns data in-between the start tag and end tag for the element. This will return
        // an empty string if there is no data here
        std::string GetText();
        // sets data in-between the start tag and end tag for the element.
        bool SetText(std::string text);

        std::string GetName();
        bool SetName(std::string name);

        // find the relative child with that name and returns it, else returns a null XMLNode. Return
        // returns to first match
        XMLNode FindChild(std::string name);

        XMLNode GetChild(size_t index);
        std::vector<XMLNode> GetChildren();
        bool AddChild(XMLNode child);
        bool AddChildren(std::vector<XMLNode>& children);
        bool RemoveChild(int index);
        bool RemoveChild(XMLNode& child);
        bool RemoveChildren();
        XMLNode GetParent();

        // find the root of the node
        // returns null if no root was found
        XMLNode GetRoot();

        // returns true if the node has text and children elements
        bool IsMixedContent();
        // returns true if the node is not null
        bool IsValid();

        // converts to boolean
        operator bool() const;
        
        XMLNode operator[](size_t _idx);
        
    };
};