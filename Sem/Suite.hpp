#pragma once

#include <string>
#include <vector>

namespace Sem {

class Expr;
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
	virtual ~Suite() = 0;
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
	
	Param(TypeRef*, const std::string&, Expr*);
};

class ParamList
{
	std::vector<Param*> list;
public:
	
	typedef std::vector<Param*>::reverse_iterator iterator;
	typedef std::vector<Param*>::const_reverse_iterator const_iterator;
	
	void add(Param*);
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
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
