#include <iostream>

#include "../Sem/Suite.hpp"
#include "../Sem/Code.hpp"

namespace Parser
{

ModuleInfo::ModuleInfo(Sem::Module* module, bool stub): module(module), stub(stub) {}

Sem::Module* OwlParser::_getTopModule() const {
	if (this->modules.empty()) {
		return 0;
	}
	return this->modules.back().module;
}

void OwlParser::_emitSuite(Sem::Suite*) {
	// TODO
}

void
OwlParser::aModuleHead(Sem::QName* qname, bool stub)
{
	// Replace stub at top, if exists
	if (stub && !this->modules.empty()) {
		if (this->modules.back().stub) {
			this->modules.pop_back();
		}
	}
	
	Sem::Module* mod = this->_getTopModule();
	
	for (auto ident: qname->parts()) {
		mod = new Sem::Module(ident->ident, mod);
		this->_emitSuite(mod);
	}
	
	this->modules.push_back(ModuleInfo(mod, stub));
}

void
OwlParser::aModuleTail()
{
	// Block module ended. Unpop all the stubs and topmost non-stub.
	
	bool pop = true;
	
	while (pop) {
		if (this->modules.empty()) {
			return;
		}
		
		pop = this->modules.back().stub;
		this->modules.pop_back();
	}
}

void
OwlParser::aFunc
(Sem::IdentExpr* name, Sem::TypeRef* ret_type, Sem::ParamList* params, Sem::Stmt* body)
{
	this->_emitSuite(new Sem::Func(
		name->ident, this->_getTopModule(),
		ret_type, params, body
	));
}

void
OwlParser::aUse()
{
	std::cout << "use" << std::endl;
}

Sem::ParamList* OwlParser::aParamListMake(Sem::Param* param) const {
	auto params = new Sem::ParamList();
	params->add(param);
	return params;
}

Sem::ParamList* OwlParser::aParamListAppend
(Sem::ParamList* params, Sem::Param* param) const {
	params->add(param);
	return params;
}

Sem::Param* OwlParser::aParamMake
(Sem::TypeRef* type, Sem::IdentExpr* name, Sem::Expr* dfault) const {
	return new Sem::Param(type, name->ident, dfault);
}

Sem::DoStmt* OwlParser::aDoStmtMake() const {
	return new Sem::DoStmt();
}

Sem::DoStmt* OwlParser::aDoStmtAppend(Sem::DoStmt* block, Sem::Stmt* stmt) const {
	block->stmts.push_back(stmt);
	return block;
}

Sem::Stmt* OwlParser::aLoopStmtMake(Sem::Stmt* body) const {
	return new Sem::LoopStmt(body);
}

Sem::Stmt* OwlParser::aIfStmtMake
(Sem::Expr* cond, Sem::Stmt* then_body, Sem::Stmt* else_body) const {
	return new Sem::IfStmt(cond, then_body, else_body);
}

Sem::Stmt* OwlParser::aVarDeclStmtMake
(Sem::IdentExpr* var, Sem::TypeRef* type, Sem::Expr* rhs) const {
	return new Sem::VarDeclStmt(var, type, rhs);
}

Sem::Stmt* OwlParser::aAssignStmtMake(Sem::IdentExpr* var, Sem::Expr* rhs) const {
	return new Sem::AssignStmt(var, rhs);
}

Sem::Stmt* OwlParser::aRetStmtMake(Sem::Expr* retval) const {
	return new Sem::RetStmt(retval);
}

Sem::Expr* OwlParser::aNumExprMake(const std::string& data) const {
	return new Sem::NumExpr(data);
}

Sem::QName* OwlParser::aQNameBegin(Sem::IdentExpr* part) const {
	return new Sem::QName(part);
}

Sem::QName* OwlParser::aQNameAppend(Sem::QName* qname, Sem::IdentExpr* part) const {
	return new Sem::QName(qname->append(part));
}

Sem::IdentExpr* OwlParser::aIdentMake(char* ident) const {
	return new Sem::IdentExpr(ident);
}

}
