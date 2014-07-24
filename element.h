/*!
 * \file element.h
 * \author Nathan Eloe
 * \brief Declaration of a BSON element
 */

#pragma once

#include "typeinfo.h"
#include <sstream>
#include <memory>

namespace bson
{
  const char X00 = '\0'; // null character, useful for encoding in bson
  
  class Document; // forward declaration for friend classness
  
  class Element
  {
    public:
      /*!
       * \brief Default Constructor
       * \pre None
       * \post Constructs an empty element with no data or type
       */
      Element(): m_data(nullptr), m_type(_UNKNOWN) {}
      
      /*!
       * \brief Constructor
       * \pre Related template functions are specialized for type T
       * \pre Type t has been configured such that it is compatible with type
       * \post Constructs the object using the template specialization
       */
      template <typename T>
      Element(const T& data, const TypeInfo & type = _UNKNOWN);
      
      /*!
       * \brief decodes a byte string into the calling object
       * \pre m_type reflects the object type that is BSON encoded in data
       * \post the calling object contains the data that is BSON encoded in data
       * \return the number of bytes consumed while decoding
       */
      unsigned decode(const char* data, const TypeInfo m_type);
      
      /*!
       * \brief encodes this object ias a bytestring
       * \pre None
       * \post encodes this object in BSON into the output string stream
       */
      void encode(std::ostringstream& oss) const;
      
      /*!
       * \brief type accessor
       * \pre None
       * \post None
       * \return the type of the object
       */
      TypeInfo get_type() const {return m_type;}
      /*!
       * \brief data accessor
       * \pre None
       * \post None
       * \return the data held in the calling object.
       * \throws bson::type_error
       */      
      template <typename T>
      const T& data() const;
      /*!
       * \brief data accessor
       * \pre None
       * \post changes the parameter to be the data held in the calling object
       * \throws bson::type_error
       */
      template <typename T>
      void data(T& t) const {t = data<T>();}
      
      /*!
       * \brief static encoders and decoders
       * \pre m_type reflects the object type that is BSON encoded in data
       * \post calls the member functions encode/decode on the passed objects
       */
      static void encode(std::ostringstream& oss, const Element& e) {e.encode(oss);}
      static void decode(const char* data, const TypeInfo type, Element& e) {e.decode(data, type);}
      
      /*!
       * \brief std::string conversion operator
       * \pre _to_std_str is template specialized
       * \post converts this object to a string
       */
      operator std::string() const;
      
    private:
      friend class Document;
      
      std::shared_ptr<void> m_data;
      TypeInfo m_type;

/* ------------ ALL FUNCTIONS BELOW THIS LINE MUST BE SPECIALIZED FOR TYPES --------- */
      
      template <typename T>
      bool check_convert() const;
      
      template <typename T>
      void type_check() const;
      
      template<typename T>
      unsigned deserialize_bytes(const char* bytes);
      
      template<typename T>
      void serialize_bson(std::ostringstream& oss) const;
      
      template <typename T>
      std::string _to_std_str() const;
  };

  /*!
   * \brief converts a type name to a string (for exceptions)
   * \pre Specialized for any and all types
   * \post None
   * \return the name of the type as a string
   */
  template <typename T>
  std::string to_string();
  
  /*!
   * \brief determines the default type for type T
   * \pre Specialized for types
   * \post None
   * \return the typeinfo that type T should default to.
   */
  template <typename T>
  TypeInfo default_type();
  
}

#include "template_spec/floats.hpp"
#include "template_spec/strings.hpp"
#include "template_spec/ints.hpp"
#include "template_spec/bools.hpp"
#include "template_spec/document.hpp"
#include "template_spec/vectors.hpp"
#include "element.hpp"