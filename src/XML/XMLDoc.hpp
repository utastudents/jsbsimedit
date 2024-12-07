#pragma once

#include <pugixml.hpp>
#include <XML/XMLNode.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <sstream>
#include <filesystem>


namespace JSBEdit
{

    class XMLDoc
    {
    private:
        pugi::xml_document doc;
        std::string m_xmlData;
        std::filesystem::path m_filePath;

        void GetFileContexts(const std::filesystem::path &path);
        bool ParseData();
    public:
        XMLDoc();
        XMLDoc(pugi::xml_document&& newDoc) : doc {std::move(newDoc)} {} 
        ~XMLDoc();
        void LoadFileAndParse(const std::filesystem::path &path);
        void LoadStringAndParse(const std::string& xmlstring);
        pugi::xml_document& GetPugiDoc() { return doc; }
        XMLNode GetNode(std::string search);
        std::vector<XMLNode> GetNodes(std::string search);
        bool SaveToFile(const std::filesystem::path &path);
        // void Print();

        //Function to retrieve the file file path
        std::filesystem::path GetFilePath() const;
    };

};