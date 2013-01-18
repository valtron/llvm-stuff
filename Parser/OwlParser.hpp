#pragma once

#include <vector>
#include <fstream>
#include <iostream>

namespace Sem
{
	class PackageBuilder;
	class Module;
	class Suite;
	class QName;
	class Expr;
	class IdentExpr;
	class Param;
	class ParamList;
	class TypeRef;
	class Stmt;
}

namespace Parser
{
	class OwlParser;
}

int owlparse(Parser::OwlParser*);

namespace Parser
{

struct ModuleInfo
{
	Sem::Module* module;
	bool stub;
	
	ModuleInfo(Sem::Module*, bool);
};

class OwlParser
{
	Sem::PackageBuilder* builder;
	const std::string& filename;
	std::vector<ModuleInfo> modules;
	
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
	
	Sem::Module* _getTopModule() const;
	void _emitSuite(Sem::Suite*);
	
// Not really public, but needs to be accessible by the generated parser code.
public:
	// Defined in actions.inl
	void aModuleHead(Sem::QName*, bool);
	void aModuleTail();
	void aFunc(Sem::IdentExpr*, Sem::TypeRef*, Sem::ParamList*, Sem::Stmt*);
	void aUse();
	Sem::ParamList* aParamListMake(Sem::Param*) const;
	Sem::ParamList* aParamListAppend(Sem::ParamList*, Sem::Param*) const;
	Sem::Param* aParamMake(Sem::TypeRef*, Sem::IdentExpr*, Sem::Expr*) const;
	Sem::QName* aQNameBegin(Sem::IdentExpr*) const;
	Sem::QName* aQNameAppend(Sem::QName*, Sem::IdentExpr*) const;
	Sem::IdentExpr* aIdentMake(char*) const;
};

}
