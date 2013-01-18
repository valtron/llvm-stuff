#include "Suite.hpp"

namespace Sem
{

Suite::Suite(const std::string& name, Module* parent)
	: name(name), parent(parent) {}

Module::Module(const std::string& name, Module* parent)
	: Suite::Suite(name, parent) {}

Func::Func(const std::string& name, Module* parent, TypeRef* ret_type, ParamList* params, Stmt* body)
	: Suite::Suite(name, parent), ret_type(ret_type), params(params), body(body)
	{}

Param::Param(TypeRef* type, const std::string& name, Expr* dfault)
	: type(type), name(name), dfault(dfault) {}

void ParamList::add(Param* param) {
	this->list.push_back(param);
}

ParamList::iterator ParamList::begin() {
	return this->list.rbegin();
}

ParamList::const_iterator ParamList::begin() const {
	return this->list.rbegin();
}

ParamList::iterator ParamList::end() {
	return this->list.rend();
}

ParamList::const_iterator ParamList::end() const {
	return this->list.rend();
}

}
