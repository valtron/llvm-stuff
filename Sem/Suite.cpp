#include "Suite.hpp"

namespace Sem
{

Suite::Suite(const std::string& name, Module* parent)
	: name(name), parent(parent) {}

Module::Module(const std::string& name, Module* parent)
	: Suite::Suite(name, parent) {}

Func(const std::string& name, Module* parent, TypeRef* ret_type, ParamList* params, Stmt* body)
	: Suite::Suite(name, parent), ret_type(ret_type), params(params), body(body)
	{}

}
