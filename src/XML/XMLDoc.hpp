#pragma once

#include <pugixml.hpp>
#include <Metrics/Metrics.hpp>

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

    class XMLDoc
    {
    private:
        pugi::xml_document doc;
        Glib::ustring m_xmlData;

        void GetFileContexts(const std::filesystem::path &path);
        bool ParseData();
        void CreateMetrics();

    public:
        XMLDoc();
        ~XMLDoc();
        void LoadFileAndParse(const std::filesystem::path &path);
        pugi::xml_document& GetPugiDoc() { return doc; }
    };

};