#pragma once

#include <string>
#include <vector>

namespace Sem
{

class Stmt {};

class DoStmt: public Stmt
{
	
};

class VarDeclStmt: public Stmt
{
	
};

class AssignStmt: public Stmt
{
	
};

class LoopStmt: public Stmt
{
	
};

class IfStmt: public Stmt
{
	
};

class RetStmt: public Stmt
{
	
};

class Expr {};

class IdentExpr: public Expr
{
public:
	std::string ident;
	IdentExpr(const std::string& ident);
};

class NumExpr: public Expr
{
	
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
