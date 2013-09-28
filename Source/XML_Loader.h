#ifndef XML_LOADER_H
#define XML_LOADER_H
#include <string>
#include <tinyxml2.h>


namespace XML
    {

    bool Init_XML_File(tinyxml2::XMLDocument& document, const std::string& fileName);
    void LoadContentString(tinyxml2::XMLDocument& doc, const std::string& Entity, const std::string& Attribute);
    int LoadContentInt(tinyxml2::XMLDocument& doc, const std::string& Entity, const std::string& Attribute);
    }

#endif // XML_LOADER_H
