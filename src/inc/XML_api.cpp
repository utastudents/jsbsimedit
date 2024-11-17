#include "inc/XML_api.hpp"

// hide the object
static JSBEdit::XMLDoc docptr;

JSBEdit::XMLDoc* xmlptr()
{
    return &docptr;
}
