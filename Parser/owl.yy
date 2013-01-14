%skeleton "lalr1.cc"

%defines
%define namespace "Parser"
%define parser_class_name "OwlParser"
%parse-param { Parser::OwlLexer& lexer }
%lex-param   { Parser::OwlLexer& lexer }

%code requires {
	#include "../Sem.hpp"
	
	// Forward-declare the Scanner class; the Parser needs to be assigned a 
	// Scanner, but the Scanner can't be declared without the Parser
	namespace Parser {
		class OwlLexer;
	}
}

%code {
	// Prototype for the yylex function
	static int yylex(Parser::OwlParser::semantic_type * yylval, Parser::OwlLexer &lexer);
}

%{
	#include "../Sem.hpp"
%}

%token ID NUM

%union {
	Sem::Stmt* stmt;
	Sem::Expr* expr;
}

%type <stmt> r_stmt r_block r_if r_ret r_var r_assign r_loop r_stmt_list r_if_else
%type <expr> r_expr r_expr_opt r_ident

%left '+' '-'
%left '*' '/'
%right '^'
%left '~'

%%

r_unit
	: r_suite_list

r_suite_list
	: r_suite_list r_suite
	|

r_suite
	: r_module
	| r_func
	| r_use

r_module
	: r_module_head r_suite_list r_module_tail

r_module_head
	: 'module' r_qname '{'

r_module_tail
	: '}'

r_func
	: r_func_type r_ident r_func_params r_func_body

r_func_params
	: '(' r_param_list ')'
	|

r_param_list
	: r_param ',' r_param_list
	|

r_param
	: r_type r_ident r_param_default

r_param_default
	: '=' r_expr
	|

r_use
	: 'use' r_qname ';'

r_qname
	: r_ident
	| r_qname '.' r_ident

r_func_type
	: r_type
	| 'fn'

r_func_body
	: r_block

r_stmt
	: r_block
	| r_loop
	| r_if
	| r_ret
	| r_var
	| r_assign

r_block
	: '{' r_stmt_list '}' { $$ = $2; }

r_stmt_list
	: r_stmt_list r_stmt
	| { $$ = 0; }

r_loop
	: 'loop' r_block { $$ = 0; }

r_if
	: 'if' r_expr r_block r_if_else { $$ = 0; }

r_if_else
	: 'else' r_block { $$ = $2; }
	| 'else' r_if { $$ = $2; }
	| { $$ = 0; }

r_ret
	: 'ret' r_expr_opt ';' { $$ = 0; }

r_var
	: r_var_type r_ident '=' r_expr ';' { $$ = 0; }

r_var_type
	: r_qname

r_var_type
	: 'my'

r_assign
	: r_ident '=' r_expr ';' { $$ = 0; }

r_expr_opt
	: r_expr
	| { $$ = 0; }

r_expr
	: r_ident
	| NUM { $$ = 0; }

r_type
	: r_qname

r_ident
	: ID { $$ = 0; }
