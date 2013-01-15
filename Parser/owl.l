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
		char c; \
		(*yyextra->is) >> c; \
		if(yyextra->is->eof()) \
			result = YY_NULL; \
		else { \
			buf[0] = c; \
			result = 1; \
		} \
	}
%}

%%

"a"	yylval->n = 1; return A;
"b"	yylval->n = 2; return B;

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
