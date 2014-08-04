%skeleton "lalr1.cc"
%defines
%define api.namespace {bson}
%define parser_class_name {JSON_Parser}

%code requires {
  namespace bson {
    class JSON_Scanner;
    class JSON_Loader;
    class Element;
    class Document;
  }
}

%lex-param	{JSON_Scanner &scanner}
%parse-param	{JSON_Scanner &scanner}

%lex-param	{JSON_Loader &driver}
%parse-param	{JSON_Loader &driver}

%{
#include <algorithm>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include "jsonloader.h"
#include "../document.h"
#include "../element.h"
static int yylex(bson::JSON_Parser::semantic_type *yylval, bson::JSON_Scanner &scanner, bson::JSON_Loader &driver);

inline std::string stripquotes (const char* txt)
{
  return std::string(txt + 1, std::strlen(txt) - 2);
}

%}

%union {
std::string * text;
long l;
double d;
bson::Element * elm;
std::vector<bson::Element> * vec;
}

%token T_NIL T_OBJBEG T_OBJEND T_ARRBEG T_ARREND T_COLON T_COMMA T_T T_F
%token <text> T_STR 
%token <l> T_INT
%token <d> T_DOUB

%destructor { if ($$) { delete $$; $$ = nullptr;}} <text>
%destructor { if ($$) { delete $$; $$ = nullptr;}} <elm>
%destructor { if ($$) { delete $$; $$ = nullptr;}} <vec>

%type <elm> object value array obj_list obj_pair
%type <vec> arrvals


%start _object
%%
_object  : object {driver.set_doc($1->data<bson::Document>());};

object   : T_OBJBEG obj_list T_OBJEND {$$ = $2;}
         | T_OBJBEG T_OBJEND {$$ = new bson::Element(bson::Document());};

obj_list : obj_list T_COMMA obj_pair { bson::Document d($1->data<bson::Document>()); d.combine($3->data<bson::Document>()); $$ = new Element(d); }
         | obj_pair {$$ = $1;};
         
obj_pair : T_STR T_COLON value { $$ = new bson::Element(bson::Document({{stripquotes($1->c_str()), $3}})); };

array    : T_ARRBEG arrvals T_ARRBEG {std::vector<bson::Element> v(*$2); std::reverse(v.begin(),v.end()); $$ = new bson::Element(v);}
         | T_ARRBEG T_ARREND {$$ = new bson::Element(std::vector<bson::Element>());};

arrvals  : arrvals T_COMMA value {std::vector<bson::Element> v(*$1); v.push_back(*($3)); $$ = new std::vector<bson::Element>(v);}
         | value {$$ = new std::vector<bson::Element>({$1});};

value    : T_STR {$$ = new bson::Element(stripquotes($1->c_str()));} //handle quotes
         | T_DOUB {$$ = new bson::Element($1);}
         | T_INT {$$ = new bson::Element($1);}
         | object {$$ = $1;}
         | array {$$ = $1;}
         | T_T {$$ = new bson::Element(true);}
         | T_F {$$ = new bson::Element(false);}
         | T_NIL {$$ = new bson::Element(nullptr, bson::NIL);};

%%

void bson::JSON_Parser::error(const std::string & err_message)
{
  std::cerr << "Error: " << err_message << std::endl;
  return;
}



#include "jsonscanner.h"

static int yylex(bson::JSON_Parser::semantic_type *yylval, bson::JSON_Scanner &scanner, bson::JSON_Loader &driver)
{
  return scanner.yylex(yylval);
}