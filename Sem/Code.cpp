#include "Code.hpp"

namespace Sem
{

IdentExpr::IdentExpr(const std::string& ident): ident(ident) {}

QName::QName(const IdentExpr* part) {
	this->_parts.push_back(part);
}

VarDeclStmt::VarDeclStmt(IdentExpr* var, TypeRef* type, Expr* rhs)
	: var(var), type(type), rhs(rhs) {}

AssignStmt::AssignStmt(IdentExpr* var, Expr* rhs): var(var), rhs(rhs) {}

LoopStmt::LoopStmt(Stmt* body): body(body) {}

IfStmt::IfStmt(Expr* cond, Stmt* then_body, Stmt* else_body)
	: cond(cond), then_body(then_body), else_body(else_body) {}

RetStmt::RetStmt(Expr* retval): retval(retval) {}

NumExpr::NumExpr(const std::string& data): data(data) {}

QName::QName(const QName::ListType& parts)
	: _parts(parts) {}

QName QName::append(const IdentExpr* part) const {
	QName newobj(this->_parts);
	newobj._parts.push_back(part);
	return newobj;
}

const IdentExpr* QName::last() const {
	return this->_parts.back();
}

const IdentExpr* QName::first() const {
	return this->_parts.front();
}

const QName::ListType& QName::parts() const {
	return this->_parts;
}

}
