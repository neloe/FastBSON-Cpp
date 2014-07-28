/*!
 * \file document.h
 * \author Nathan Eloe
 * \brief Definition of the BSON Document class
 */

#pragma once

#include "element.h"
#include "typeinfo"
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <ostream>

namespace bson
{
  
  class Document
  {     
    private:
      friend class Element;
      std::map<std::string, Element> m_data;
      std::set<std::string> m_field_names;
      
    public:
      /*!
       * \brief accessor
       * \pre None
       * \post None
       * \return the Element at the specified field name
       * \throws std::out_of_range if index is not in the dictionary
       */
      const Element& operator[] (const std::string & index) const {return m_data.at(index);}
      Element& operator[] (const std::string & index) {return m_data.at(index);}
      
      /*!
       * \brief element addition
       * \pre None
       * \post creates the element in the map. If name already exists in the document the value is overwritten
       */ 
      void add (const std::string name, const Element& data) {m_data[name] = data; m_field_names.insert(name);}
      /*!
       * \brief element addition
       * \pre T must be template specialized for the Element class
       * \pre if ti is not defaulted, it and type T must be compatible
       * \post creates the element in the map. If name already exists in the document the value is overwritten
       */ 
      template <class T>
      void add (const std::string name, const T& data, const TypeInfo ti = _UNKNOWN) {m_data[name] = Element(data, ti); m_field_names.insert(name);}
      
      /*!
       * \brief element modification
       * \pre name exists as an index in the document
       * \post changes the element at index name
       * \throws std::out_of_range if name is not in the Document
       */
      void set(const std::string name, const Element& data) {m_data.at(name) = data;}
      /*!
       * \brief element modification
       * \pre name exists as an index in the document
       * \pre T must be template specialized for the Element class
       * \pre if ti is not defaulted, it and type T must be compatible
       * \post changes the element at index name
       * \throws std::out_of_range if name is not in the Document
       */
      template <class T>
      void set(const std::string & name, const T& data, const TypeInfo ti = _UNKNOWN){m_data.at(name) = Element(data, ti);}
      
      /*!
       * \brief insertion operator overloading
       * \pre None
       * \post inserts document d into the stream (using the string conversion for insertion)
       */
      friend std::ostream& operator << (std::ostream& o, const Document& d);
      
      /*!
       * \brief iterator functions
       * \pre None
       * \post None
       * \return iterators pointing at the beginning and end of the data in the document
       */
      auto begin() -> decltype(m_data.begin()) {return m_data.begin();}
      auto end() -> decltype(m_data.end()) {return m_data.end();}
      auto rbegin() -> decltype(m_data.rbegin()) {return m_data.rbegin();}
      auto rend() -> decltype(m_data.rend()) {return m_data.rend();}
      auto cbegin() -> decltype(m_data.cbegin()) {return m_data.cbegin();}
      auto cend() -> decltype(m_data.cend()) {return m_data.cbegin();}
      auto crbegin() -> decltype(m_data.crbegin()) {return m_data.crbegin();}
      auto crend() -> decltype(m_data.crend()) {return m_data.crend();}
      
      /*!
       * \brief returns the set of field names
       * \pre None
       * \post None
       * \return the set of field names
       */
      std::set<std::string> field_names() const {return m_field_names;}
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