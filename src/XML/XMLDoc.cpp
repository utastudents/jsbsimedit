#include <XML/XMLDoc.hpp>



void JSBEdit::XMLDoc::GetFileContexts(const std::filesystem::path& path)
{
    if(!std::filesystem::exists(path))
    {
        std::cerr << "XMLDoc Error: GetFileContexts path does not exist. Path: " << path << "\n";
    }

    // use a stream because they are fast enough, and I don't want to write alot of code
    std::ifstream inFileStream{path};
    std::stringstream buffer;
    buffer << inFileStream.rdbuf();

    m_xmlData = buffer.str();
}

bool JSBEdit::XMLDoc::ParseData()
{
    // Glib::Markup needs a context to parse
    Glib::Markup::ParseContext parseContext{*m_pParser};
    try {
        parseContext.parse(m_xmlData);
    } catch (Glib::MarkupError error) 
    {
        std::cerr << "Error: " << error.what() << "\n";
        return false;
    }
    return true;
}

JSBEdit::XMLDoc::XMLDoc()
{
    m_pParser = new JSBEdit::XMLParser();
}

JSBEdit::XMLDoc::~XMLDoc()
{
    delete m_pParser;
}

void JSBEdit::XMLDoc::LoadFileAndParse(const std::filesystem::path& path)
{
    GetFileContexts(path);
    ParseData();
}