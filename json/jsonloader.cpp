/*!
 * \file jsonloader.cpp
 * \author Nathan Eloe
 * \brief Implementation of the JSON Loader class
 */

#include "jsonloader.h"
#include <sstream>

namespace bson
{
  const Document& JSON_Loader::parse(const std::string& jsonstr)
  {
    std::istringstream iss;
    iss.str(jsonstr);
    scanner = std::shared_ptr<JSON_Scanner>(new JSON_Scanner(iss));
    parser = std::shared_ptr<JSON_Parser>(new JSON_Parser(*scanner, *this));
    parser->parse();
    //TODO handle errors here
    return m_doc;
  }

}