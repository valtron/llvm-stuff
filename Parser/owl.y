%code requires {
	#include "../Sem/Code.hpp"
}

%define api.pure
%name-prefix="owl"
%locations
%defines
%error-verbose
%parse-param { Parser::OwlParser* parser }
%lex-param { void* scanner  }

%union
{
	Sem::Stmt* stmt;
	Sem::Expr* expr;
	Sem::QName* qname;
	Sem::IdentExpr* ident;
	char* cstr;
}

%token ID NUM

%token T_BCL "{"
%token T_BCR "}"
%token T_BRL "("
%token T_BRR ")"
%token T_SEMI ";"
%token T_COMMA ","
%token T_DOT "."
%token T_MODULE "module"
%token T_USE "use"
%token T_FN "fn"
%token T_MY "my"
%token T_IF "if"
%token T_RET "ret"
%token T_LOOP "loop"
%token T_ELSE "else"
%token END 0 "end of file"

%type <stmt> r_stmt r_block r_if r_ret r_var r_assign r_loop r_stmt_list r_if_else
%type <expr> r_expr r_expr_opt
%type <qname> r_qname
%type <ident> r_ident
%type <cstr> ID

%left "+" "-"
%left "*" "/"
%right "^"
%left "~"

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
	:	"module" r_qname
		"{" { parser->aModuleHead($2, false); }
			r_suite_list
		"}" { parser->aModuleTail(); }
	| "module" r_qname ";"
		{ parser->aModuleHead($2, true); }

r_func
	: r_func_type r_ident r_func_params r_func_body
	{ parser->aFunc(); }

r_func_params
	: "(" r_param_list ")"

r_param_list
	: r_param "," r_param_list
	| r_param
	|

r_param
	: r_type r_ident r_param_default

r_param_default
	: "=" r_expr
	|

r_use
	: "use" r_qname ";"
	{ parser->aUse(); }

r_qname
	: r_ident { $$ = parser->aQNameBegin($1); }
	| r_qname "." r_ident { $$ = parser->aQNameAppend($1, $3); }

r_func_type
	: r_type
	| "fn"

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
	: "{" r_stmt_list "}" { $$ = $2; }

r_stmt_list
	: r_stmt_list r_stmt
	| { $$ = 0; }

r_loop
	: "loop" r_block { $$ = 0; }

r_if
	: "if" r_expr r_block r_if_else { $$ = 0; }

r_if_else
	: "else" r_block { $$ = $2; }
	| "else" r_if { $$ = $2; }
	| { $$ = 0; }

r_ret
	: "ret" r_expr_opt ";" { $$ = 0; }

r_var
	: r_var_type r_ident "=" r_expr ";" { $$ = 0; }

r_var_type
	: r_qname

r_var_type
	: "my"

r_assign
	: r_ident "=" r_expr ";" { $$ = 0; }

r_expr_opt
	: r_expr
	| { $$ = 0; }

r_expr
	: r_ident { $$ = $1; }
	| NUM { $$ = 0; }

r_type
	: r_qname

r_ident
	: ID { $$ = parser->aIdentMake($1); }

%%

#undef scanner

#include "actions.inl"
