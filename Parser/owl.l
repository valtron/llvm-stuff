%option reentrant
%option prefix="owl"
%option bison-bridge
%option bison-locations
%option noyywrap
%option yylineno

%{
	#include "OwlParser.hpp"
	#include "owl.tab.h"
	
	#define YY_EXTRA_TYPE Parser::OwlParser*
	#define YY_USER_ACTION yylloc->first_line = yylineno;
	
	#define YY_INPUT(buf, result, max_size) \
	{ \
		if (yyextra->is->eof()) { \
			result = YY_NULL; \
		} else { \
			yyextra->is->read(buf, max_size); \
			result = yyextra->is->gcount(); \
		} \
	}
%}

alpha	[a-zA-Z_]
digit	[0-9]
alnum	({alpha}|{digit})
ws		[ \t\v\n\f\r]

%%

"module"						return T_MODULE;
"use"								return T_USE;
"fn"								return T_FN;
"my"								return T_MY;
"loop"							return T_LOOP;
"ret"								return T_RET;
"if"								return T_IF;
"else"							return T_ELSE;
{alpha}{alnum}*"'"?	yylval->cstr = yytext; return ID;
{digit}+						return NUM;
{ws}								/* skip */;
"."									return T_DOT;
","									return T_COMMA;
"{"									return T_BCL;
"}"									return T_BCR;
"("									return T_BRL;
")"									return T_BRR;
";"									return T_SEMI;
.										/* ignore */;

%%

void Parser::OwlParser::init_scanner()
{
	yylex_init(&this->scanner);
	yyset_extra(this, this->scanner);
}

void Parser::OwlParser::destroy_scanner()
{
	yylex_destroy(this->scanner);
}
