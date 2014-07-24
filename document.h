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
      /*!
       * \brief accessor
       * \pre None
       * \post None
       * \return the Element at the specified field name
       */
      const Element& operator[] (const std::string & index) const {return m_data.at(index);}
      
      /*!
       * \brief element addition
       * \pre None
       * \post creates the element in the map
       */ 
      void add (const std::string name, const Element& data) {m_data[name] = data;}
      template <class T>
      void add (const std::string name, const T& data, const TypeInfo ti = _UNKNOWN) {m_data[name] = Element(data, ti);}
      
      /*!
       * \brief insertion operator overloading
       * \pre None
       * \post inserts document d into the stream (using the string conversion for insertion)
       */
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