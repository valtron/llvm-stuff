#pragma once

#include <vector>
#include <map>
#include <string>

namespace Sem {

class Suite;
class Package;
class Module;
class Group;

struct GroupKey
{
	Module* parent;
	std::string name;
};

class PackageBuilder
{
	std::map<GroupKey, Group*> groups;
	
public:
	Package* package;
	std::vector<Suite*> suites;
	
	PackageBuilder(const std::string&, const std::string&);
	
	void parse(const std::string&);
	
	void add(Suite*);
};

}
