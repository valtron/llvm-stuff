#pragma once

#include <string>
#include <vector>

namespace Sem {

class Stmt;
class Module;

class Package
{
public:
	std::string name;
	std::string version;
	
	Package(const std::string& name, const std::string& version)
		: name(name), version(version) {}
};

class Suite
{
public:
	std::string name;
	Module* parent;
	
	Suite(const std::string&, Module*);
};

class Module: public Suite
{
public:
	Module(const std::string&, Module*);
};

class Group: public Suite
{
	
};

class TypeRef
{
	
};

class Param
{
public:
	TypeRef* type;
	std::string name;
	Expr* dfault;
};

class ParamList
{
public:
	std::vector<Param*> list;
};

class Func: public Suite
{
public:
	TypeRef* ret_type;
	ParamList* params;
	Stmt* body;
	
	Func(const std::string&, Module*, TypeRef*, ParamList*, Stmt*);
};

class Use: public Suite
{
	
};

}
