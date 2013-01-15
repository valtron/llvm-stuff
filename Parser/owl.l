%{
	#include "owl.tab.hh"
%}

%option nodefault yyclass="OwlLexer" noyywrap c++

%%

[1-9][0-9]* { *yylval = 0; }
.+|\n       { }
