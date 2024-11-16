#include "XML_Api.hpp"

// hide the pointer
static XMLDoc* docptr = nullptr;

XMLDoc* xmlptr()
{
    return docptr;
}
