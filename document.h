/*!
 * \file document.h
 * \author Nathan Eloe
 * \brief Definition of the BSON Document class
 */

#pragma once

#include "element.h"
#include "typeinfo"
#include <map>
#include <string>
#include <sstream>
#include <ostream>

namespace bson
{
  
  class Document
  {
    public:
      const Element& operator[] (const std::string & index) const {return m_data.at(index);}
      
      void add (const std::string name, const Element& data) {m_data[name] = data;}
      template <class T>
      void add (const std::string name, const T& data, const TypeInfo ti = _UNKNOWN) {m_data[name] = Element(data, ti);}
      
      friend std::ostream& operator << (std::ostream& o, const Document& d);
      
    private:
      friend class Element;
      std::map<std::string, Element> m_data;
  };

  inline std::ostream& operator << (std::ostream& oss, const Document& d)
  {
    bool first = true;
    oss << "{ ";
    for (std::pair<std::string, Element> p: d.m_data)
    {
      if (!first)
      {
	oss << ", ";
	first = false;
      }
      oss << p.first << " : " << static_cast<std::string>(p.second);
    }
    oss << " }";
    return oss;
  }
}