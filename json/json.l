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

enum {T_NIL, T_T, T_F, T_STR, T_INT, T_DOUB, T_OBJBEG, T_OBJEND, T_ARRBEG, T_ARREND, T_COLON, T_COMMA};
const char* NAMES[] = {"NULL", "TRUE", "FALSE", "String", "Integer", 
                       "Double", "Obj. Beg", "Obj. End", "Arr Beg", "Arr End",
                       "Colon", "Comma"};
                
void dbprint(const int toktype, const char* text);

class invalid_token: public std::exception
{
  private: std::string m_bad_token;
  public:
    invalid_token (const char* badtok): m_bad_token(badtok) {}
    virtual const char* what() const noexcept
    {
      std::string exctext = "Invalid json token: " + m_bad_token;
      return exctext.c_str();
    }
};
%}

%option noyywrap
%option yyclass="bson::JSON_Scanner"
%option outfile="json_lex.cpp"
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
"{" 		{dbprint(T_OBJBEG, YYText()); return T_OBJBEG;}
"}" 		{dbprint(T_OBJEND, YYText()); return T_OBJEND;}
"["		{dbprint(T_ARRBEG, YYText()); return T_ARRBEG;}
"]" 		{dbprint(T_ARREND, YYText()); return T_ARREND;}

":"		{dbprint(T_COLON, YYText());  return T_COLON;}
","		{dbprint(T_COMMA, YYText());  return T_COMMA;}
{DOUBLE} 	{dbprint(T_DOUB, YYText()); yylval->d = atof(YYText());   return T_DOUB;}
{INTEGER} 	{dbprint(T_INT, YYText());  yylval->l = atol(YYText());  return T_INT;}
{STRING}	{dbprint(T_STR, YYText());  yylval->text = new std::string(YYText());  return T_STR;}
{TRUE}		{dbprint(T_T, YYText());      return T_T;}
{FALSE}		{dbprint(T_T, YYText());      return T_F;}
{WSPACE}	{}
.		{throw invalid_token(YYText());}
%%


void dbprint(const int toktype, const char* text)
{
#if DEBUG
  std::cout << "Found: " << NAMES[toktype] << " : " << text << std::endl;
#endif
}

#if DEBUG
int main()
{
  std::shared_ptr<FlexLexer> lexer (new yyFlexLexer);
  while (lexer -> yylex());
  return 0;
}
#endif
 