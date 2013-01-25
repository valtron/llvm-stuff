#pragma once

#include <string>
#include <vector>

namespace Sem
{

class TypeRef;

class Stmt {
public:
	virtual ~Stmt() = 0;
};

class Expr {
public:
	virtual ~Expr() = 0;
};

class DoStmt: public Stmt
{
public:
	std::vector<Stmt*> stmts;
};

class IdentExpr: public Expr
{
public:
	std::string ident;
	IdentExpr(const std::string& ident);
};

class VarDeclStmt: public Stmt
{
public:
	IdentExpr* var;
	TypeRef* type;
	Expr* rhs;
	
	VarDeclStmt(IdentExpr*, TypeRef*, Expr*);
};

class AssignStmt: public Stmt
{
public:
	IdentExpr* var;
	Expr* rhs;
	
	AssignStmt(IdentExpr*, Expr*);
};

class LoopStmt: public Stmt
{
public:
	Stmt* body;
	
	LoopStmt(Stmt*);
};

class IfStmt: public Stmt
{
public:
	Expr* cond;
	Stmt* then_body;
	Stmt* else_body;
	
	IfStmt(Expr*, Stmt*, Stmt*);
};

class RetStmt: public Stmt
{
public:
	Expr* retval;
	
	RetStmt(Expr*);
};

class NumExpr: public Expr
{
public:
	std::string data;
	
	NumExpr(const std::string&);
};

class QName
{
public:
	typedef std::vector<const IdentExpr*> ListType;
	
private:
	ListType _parts;
	
	QName(const ListType&);
public:
	QName(const IdentExpr*);
	
	QName append(const IdentExpr*) const;
	
	const IdentExpr* first() const;
	const IdentExpr* last() const;
	const ListType& parts() const;
};

}
