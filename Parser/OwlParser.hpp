#pragma once

#include <fstream>
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
	const std::string& filename;
	
// Need to be public for lexer
public:
	void* scanner;
	std::ifstream* is;
	
public:
	OwlParser(Sem::PackageBuilder* builder, const std::string& filename)
		: builder(builder), filename(filename)
	{
		this->is = new std::ifstream(filename.c_str());
		this->init_scanner();
	}
	
	bool parse()
	{
		return owlparse(this) == 0;
	}
	
	void error(int line, const char* msg)
	{
		std::cerr << this->filename << ":" << line << ": " << msg << std::endl;
	}
	
	~OwlParser()
	{
		this->destroy_scanner();
		this->is->close();
		delete this->is;
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
