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

#include "json.tab.hh"

namespace bson
{
  //enum {T_NIL, T_T, T_F, T_STR, T_INT, T_DOUB, T_OBJBEG, T_OBJEND, T_ARRBEG, T_ARREND, T_COLON, T_COMMA};
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