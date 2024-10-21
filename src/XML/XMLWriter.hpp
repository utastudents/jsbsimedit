#include <string>

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