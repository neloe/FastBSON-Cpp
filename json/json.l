/*
 * \file json.l
 * \author Nathan Eloe
 * \brief a JSON parser written in flex
 */

/*
 * Token types
 */
 
%{
#include <memory>
#include <iostream>
#include <exception>

#include "jsonscanner.h"

#define DEBUG 0
                
const char* NAMES[] = {"NULL", "TRUE", "FALSE", "String", "Integer", 
                       "Double", "Obj. Beg", "Obj. End", "Arr Beg", "Arr End",
                       "Colon", "Comma"};
void dbprint(const int toktype, const char* text);
%}

%option noyywrap
%option yyclass="bson::JSON_Scanner"
%option c++

/*
 * regexs
 */

WSPACE	[ \t\n\r]+

ESCCH	\\[\"\\\/bfnrt(u[:xdigit:]{4})]
STRCNT	({ESCCH}|[^\"])*
STRING	\"{STRCNT}\"

DOUBLE  "-"?(0|([1-9][0-9]*))\.[0-9]+([eE][+-]?[0-9]+)?
INTEGER	"-"?(0|([1-9][0-9]*))([eE][+-]?[0-9]+)?

TRUE	"true"
FALSE	"false"
NIL	"null"
%%
"{" 		{dbprint(bson::JSON_Parser::token::T_OBJBEG, YYText()); return bson::JSON_Parser::token::T_OBJBEG;}
"}" 		{dbprint(bson::JSON_Parser::token::T_OBJEND, YYText()); return bson::JSON_Parser::token::T_OBJEND;}
"["		{dbprint(bson::JSON_Parser::token::T_ARRBEG, YYText()); return bson::JSON_Parser::token::T_ARRBEG;}
"]" 		{dbprint(bson::JSON_Parser::token::T_ARREND, YYText()); return bson::JSON_Parser::token::T_ARREND;}

":"		{dbprint(bson::JSON_Parser::token::T_COLON, YYText());  return bson::JSON_Parser::token::T_COLON;}
","		{dbprint(bson::JSON_Parser::token::T_COMMA, YYText());  return bson::JSON_Parser::token::T_COMMA;}
{NIL}		{dbprint(bson::JSON_Parser::token::T_NIL, YYText());    return bson::JSON_Parser::token::T_NIL;}
{DOUBLE} 	{dbprint(bson::JSON_Parser::token::T_DOUB, YYText()); yylval->d = atof(YYText());   return bson::JSON_Parser::token::T_DOUB;}
{INTEGER} 	{dbprint(bson::JSON_Parser::token::T_INT, YYText());  yylval->l = atol(YYText());  return bson::JSON_Parser::token::T_INT;}
{STRING}	{dbprint(bson::JSON_Parser::token::T_STR, YYText());  yylval->text = new std::string(YYText());  return bson::JSON_Parser::token::T_STR;}
{TRUE}		{dbprint(bson::JSON_Parser::token::T_T, YYText());      return bson::JSON_Parser::token::T_T;}
{FALSE}		{dbprint(bson::JSON_Parser::token::T_T, YYText());      return bson::JSON_Parser::token::T_F;}
{WSPACE}	{}
.		{throw invalid_token(YYText());}
%%
void dbprint(const int toktype, const char* text)
{
#if DEBUG
  std::cout << "Found: " << toktype << " : " << text << std::endl;
#endif
}

 