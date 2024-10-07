#pragma once
#include <XML/XMLParser.hpp>

#include <pugixml.hpp>
#include <Metrics/Metrics.hpp>

#include <string>

namespace JSBEdit
{

    class XMLDoc
    {
    private:
        pugi::xml_document doc;
        Glib::ustring m_xmlData;
        XMLParser *m_pParser;
        // temp here for test remove this and find a better place - Ellis
        Metrics* m_pMetrics;

        void GetFileContexts(const std::filesystem::path &path);
        bool ParseData();
        void CreateMetrics();

    public:
        XMLDoc();
        ~XMLDoc();
        void LoadFileAndParse(const std::filesystem::path &path);
        pugi::xml_document& GetPugiDoc() { return doc; }
        Metrics* GetMetricsData() { return m_pMetrics; }
    };

};