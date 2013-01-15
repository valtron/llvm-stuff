#pragma once

#include <istream>

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
	int result;
	std::istream* is;
	
public:
	OwlParser(std::istream* is)
	{
		this->init_scanner();
		this->is = is;
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
