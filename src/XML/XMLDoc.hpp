#pragma once
#include <XML/XMLParser.hpp>

#include <string>

namespace JSBEdit
{

    class XMLDoc
    {
    private:
        Glib::ustring m_xmlData;
        XMLParser *m_pParser;
        void GetFileContexts(const std::filesystem::path &path);
        bool ParseData();

    public:
        XMLDoc();
        ~XMLDoc();
        void LoadFileAndParse(const std::filesystem::path &path);
    };

};