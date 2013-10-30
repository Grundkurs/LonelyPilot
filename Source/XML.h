#ifndef XML_H
#define XML_H
#include <string>
#include "tinyxml2.h"


class XML{
static tinyxml2::XMLDocument doc; 
public:

static bool Init_XML_File(const std::string& fileName);
static std::string LoadContentString(const std::string& Entity, const std::string& Attribute);
static int LoadContentInt(const std::string& Entity, const std::string& Attribute);


};

#endif //XML_H
