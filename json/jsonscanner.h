/*!
 * \file jsonscanner.h
 * \author Nathan Eloe
 * \brief a JSON lexical scanner
 */

#pragma once

#if ! defined (yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL int bson::JSON_Scanner::yylex()

#include "json.tab.hpp"

namespace bson
{
  //enum {T_NIL, T_T, T_F, T_STR, T_INT, T_DOUB, T_OBJBEG, T_OBJEND, T_ARRBEG, T_ARREND, T_COLON, T_COMMA};
  class invalid_token: public std::exception
  {
    private: std::string m_exctext;
    public:
      invalid_token (const char* badtok): m_exctext("Invalid json token: ") {m_exctext += badtok;}
      virtual const char* what() const noexcept
      {
	return m_exctext.c_str();
      }
  };
  
  class JSON_Scanner: public yyFlexLexer
  {
    public:
      JSON_Scanner(std::istream & in) : yyFlexLexer(&in), yylval (nullptr) {}
      int yylex(JSON_Parser::semantic_type *lval)
      {
	yylval = lval;
	return yylex();
      }
    private:
      int yylex();
      JSON_Parser::semantic_type *yylval;
  };
}