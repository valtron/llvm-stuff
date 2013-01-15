#pragma once

#include <istream>

namespace Sem
{
	class PackageBuilder;
}

namespace Parser
{
	class OwlParser;
}

int owlparse(Parser::OwlParser*);

namespace Parser
{

class OwlParser
{
public:
	void* scanner;
	Sem::PackageBuilder* builder;
	int result;
	std::istream* is;
	
public:
	OwlParser(Sem::PackageBuilder* builder, std::istream* is)
		: builder(builder), is(is)
	{
		this->init_scanner();
	}
	
	bool parse()
	{
		return owlparse(this) == 0;
	}
	
	void error(int line, const char* msg)
	{
		
	}
	
	virtual ~OwlParser()
	{
		this->destroy_scanner();
	}
	
// Defined in Owl.l
protected:
	void init_scanner();
	void destroy_scanner();
};

}
