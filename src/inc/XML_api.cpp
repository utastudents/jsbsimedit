#include "inc/XML_api.hpp"

// hide the pointer
static JSBEdit::XMLDoc* docptr = nullptr;

JSBEdit::XMLDoc* xmlptr()
{
    return docptr;
}
