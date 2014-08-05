/*!
 * \file jsonloader.h
 * \author Nathan Eloe
 * \brief An interface to the flex/bison implementation of the JSON parser
 */
#pragma once

#include <memory>
#include "../document.h"
#include "jsonscanner.h"
#include "json.tab.hh"

namespace bson
{
  class JSON_Loader
  {
    public:
      JSON_Loader(): m_doc(), parser(nullptr), scanner(nullptr) {}
      virtual ~JSON_Loader() {}
      
      void set_doc(const Document & doc) {m_doc = doc;}
      const Document& parse(const std::string& jsonstr);
      
    private:
      Document m_doc;
      std::shared_ptr<JSON_Parser> parser;
      std::shared_ptr<JSON_Scanner> scanner;
  };
}