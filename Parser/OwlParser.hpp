#pragma once

#include <istream>
#include <iostream>

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
	Sem::PackageBuilder* builder;
	
// Need to be public for lexer
public:
	void* scanner;
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
	
	~OwlParser()
	{
		this->destroy_scanner();
	}
	
private:
	// Defined in Owl.l
	void init_scanner();
	void destroy_scanner();
	
// Not really public, but needs to be accessible by the generated parser code.
public:
	// Defined in actions.inl
	void aModuleHead();
	void aModuleTail();
	void aFunc();
	void aUse();
};

}
