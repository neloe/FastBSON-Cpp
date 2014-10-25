/*
  Copyright (c) Nathan Eloe, 2014
  This file is part of FastBSON-Cpp.

  FastBSON-Cpp is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  FastBSON-Cpp is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with FastBSON-Cpp.  If not, see <http://www.gnu.org/licenses/>.
*/
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
#include <cstring>

namespace bson
{
  //enum {T_NIL, T_T, T_F, T_STR, T_INT, T_DOUB, T_OBJBEG, T_OBJEND, T_ARRBEG, T_ARREND, T_COLON, T_COMMA};
  class invalid_token: public std::exception
  {
    private: char m_exctext[100];
    public:
      invalid_token (const char* badtok) {std::strcpy(m_exctext, "Invalid json token: "); std::strcat(m_exctext, badtok);}
      virtual const char* what() const noexcept
      {
	return m_exctext;
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