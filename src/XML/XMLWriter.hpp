#pragma once

#include <string>
#include <XML/XMLDoc.hpp>
namespace JSBEdit
{

    class XMLWriter
    {
    
    public:
        XMLWriter(XMLDoc);
        ~XMLWriter();
        XMLDoc Write(const std::filesystem::path& path);
    };

};