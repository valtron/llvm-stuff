#include "Builder.hpp"

#include "Suite.hpp"
#include "../Parser/OwlParser.hpp"

#include <string>
#include <fstream>

namespace Sem
{

PackageBuilder::PackageBuilder(const std::string& name, const std::string& version)
	: package(new Package(name, version)) { }

void
PackageBuilder::parse(const std::string& filename)
{
	std::ifstream infile(filename.c_str());
	Parser::OwlParser parser(this, &infile);
	parser.parse();
	infile.close();
}

void
PackageBuilder::add(Suite* suite)
{
	// TODO: Disallow if Group
	this->suites.push_back(suite);
	// TODO: Add to group if Func
}

};
