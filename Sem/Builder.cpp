#include "Builder.hpp"

#include "Suite.hpp"
#include "../Parser/OwlParser.hpp"

#include <string>

namespace Sem
{

PackageBuilder::PackageBuilder(const std::string& name, const std::string& version)
	: package(new Package(name, version)) { }

void
PackageBuilder::parse(const std::string& filename)
{
	Parser::OwlParser parser(this, filename);
	parser.parse();
}

void
PackageBuilder::add(Suite* suite)
{
	// TODO: Disallow if Group
	this->suites.push_back(suite);
	// TODO: Add to group if Func
}

};
