#include <XML/XMLLoad.hpp>


JSBEdit::XMLDoc JSBEdit::XMLLoad::Load(std::filesystem::path path)
{
    if (std::filesystem::exists(path))
    {
        pugi::xml_document doc;
        doc.load_file(path.c_str());
        return JSBEdit::XMLDoc(doc);
    }
    else
        std::cerr << "File path does not exist: " << path << "\n";
}