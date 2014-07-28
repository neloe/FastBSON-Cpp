/*!
 * \file element.hpp
 * \author Nathan Eloe
 * \brief Implementation of the BSON element class
 */

#include "element.h"
#include "typeinfo.h"
#include <memory>
#include <vector>
namespace bson
{
  
  unsigned Element::decode(const unsigned char* bytes, const TypeInfo type)
  {
    unsigned num_bytes = -1;
    m_type = type;
    switch (m_type)
    {
      case INT64: case DATETIME: case TIMESTAMP:
	num_bytes = deserialize_bytes<long>(bytes);
	break;
      case INT32:
	num_bytes = deserialize_bytes<int>(bytes);
	break;
      case STRING: case JS: case DEPRECATED:
	num_bytes = deserialize_bytes<std::string>(bytes);
	break;
      case BOOL:
	num_bytes = deserialize_bytes<bool>(bytes);
	break;
      case FLOATING:
	num_bytes = deserialize_bytes<double>(bytes);
	break;
      case DOCUMENT:
	num_bytes = deserialize_bytes<Document>(bytes);
	break;
      case ARRAY:
	num_bytes = deserialize_bytes<array>(bytes);
	break;
      case OID:
	num_bytes = deserialize_bytes<oid>(bytes);
	break;
      case NIL: case MINKEY: case MAXKEY: case UNDEF:
	num_bytes = deserialize_bytes<void>(bytes);
	break;
      case REGEX:
	num_bytes = deserialize_bytes<regex>(bytes);
	break;
      case DBPTR:
	num_bytes = deserialize_bytes<dbptr>(bytes);
	break;
      case JS_SCOPE:
	num_bytes = deserialize_bytes<jscode_scope>(bytes);
	break;
      case BINARY:
	num_bytes = deserialize_bytes<binary>(bytes);
	break;
      case _UNKNOWN:
	throw type_UNKNOWN();
	break;
    }
    return num_bytes;
  }
  
  void Element::encode(std::ostringstream& oss) const
  {
    switch (m_type)
    {
      case INT64: case DATETIME: case TIMESTAMP:
	serialize_bson<long>(oss);
	break;
      case INT32:
	serialize_bson<int>(oss);
	break;
      case STRING: case JS: case DEPRECATED:
	serialize_bson<std::string>(oss);
	break;
      case BOOL:
	serialize_bson<bool>(oss);
	break;
      case FLOATING:
	serialize_bson<double>(oss);
	break;
      case DOCUMENT:
	serialize_bson<Document>(oss);
	break;
      case ARRAY:
	serialize_bson<array>(oss);
	break;
      case OID:
	serialize_bson<oid>(oss);
	break;
      case NIL: case MINKEY: case MAXKEY: case UNDEF:
	serialize_bson<void>(oss);
	break;
      case REGEX:
	serialize_bson<regex>(oss);
	break;
      case DBPTR:
	serialize_bson<dbptr>(oss);
	break;
      case JS_SCOPE:
	serialize_bson<jscode_scope>(oss);
	break;
      case BINARY:
	serialize_bson<binary>(oss);
	break;
      case _UNKNOWN:
	throw type_UNKNOWN();
	break;
    }
    return;
  }
  
  Element::operator std::string() const
  {
    std::string result;
    switch (m_type)
    {
      case INT64: case DATETIME: case TIMESTAMP:
	result = _to_std_str<long>();
	break;
      case INT32:
	result = _to_std_str<int>();
	break;
      case STRING: case JS: case DEPRECATED:
	result = _to_std_str<std::string>();
	break;
      case BOOL:
	result = _to_std_str<bool>();
	break;
      case FLOATING:
	result = _to_std_str<double>();
	break;
      case DOCUMENT:
	result = _to_std_str<Document>();
	break;
      case ARRAY:
	result = _to_std_str<array>();
	break;
      case OID:
	result = _to_std_str<oid>();
	break;
      case NIL: case MINKEY: case MAXKEY: case UNDEF:
	result = _to_std_str<void>();
	break;
      case REGEX:
	result = _to_std_str<regex>();
	break;
      case DBPTR:
	result = _to_std_str<dbptr>();
	break;
      case JS_SCOPE:
	result = _to_std_str<jscode_scope>();
	break;
      case BINARY:
	result = _to_std_str<binary>();
	break;
      case _UNKNOWN:
	throw type_UNKNOWN();
	break;
    }
    return result;
  }
}