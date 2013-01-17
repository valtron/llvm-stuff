#pragma once

#include <string>

namespace Sem {

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

class Param
{
	
};

class Func: public Suite
{
	
};

class Use: public Suite
{
	
};

}
