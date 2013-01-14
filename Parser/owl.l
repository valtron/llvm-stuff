%{
	#include "Parser/OwlLexer.hpp"
%}

%option nodefault yyclass="OwlLexer" noyywrap c++

%%

[1-9][0-9]* { *yylval = 0; }
.+|\n       { }
