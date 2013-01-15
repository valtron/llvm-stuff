%pure-parser
%name-prefix="owl"
%locations
%defines
%error-verbose
%parse-param { Parser::OwlParser* parser }
%lex-param { void* scanner  }

%union
{
	int n;
}

%token <n> A
%token <n> B

%type <n> X

%{
	#include "OwlParser.hpp"
	
	int owllex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);
	
	void owlerror(YYLTYPE* locp, Parser::OwlParser* parser, const char* err)
	{
		parser->error(locp->first_line, err);
	}
	
	#define scanner parser->scanner
%}

%%

start
	: X { parser->result = $1; }
;

X
	: A X { $$ = $1 + $2; }
	| B X { $$ = $1 + $2; }
	| { $$ = 0; }
;

%%

#undef scanner
