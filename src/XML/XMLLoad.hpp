#pragma once
#include <XML/XMLDoc.hpp>

namespace JSBEdit
{

    class XMLLoad
    {
        public:
            XMLLoad() = default;
            XMLDoc Load(std::filesystem::path);
    };

};