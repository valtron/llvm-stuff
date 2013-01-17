#include <iostream>

#include "../Sem/Suite.hpp"
#include "../Sem/Code.hpp"

namespace Parser
{

ModuleInfo::ModuleInfo(Sem::Module* module, bool stub): module(module), stub(stub) {}

Sem::Module* OwlParser::_getTopModule() const {
	if (this->modules.empty()) {
		return 0;
	}
	return this->modules[this->modules.size() - 1].module;
}

void OwlParser::_emitSuite(Sem::Suite*) {
	// TODO
}

void
OwlParser::aModuleHead(Sem::QName* qname, bool stub)
{
	// Replace stub at top, if exists
	if (stub && !this->modules.empty()) {
		if (this->modules.back().stub) {
			this->modules.pop_back();
		}
	}
	
	Sem::Module* mod = this->_getTopModule();
	
	const Sem::QName::ListType& parts = qname->parts();
	for (Sem::QName::ListType::const_iterator i = parts.begin(); i != parts.end(); ++i) {
		mod = new Sem::Module((*i)->ident, mod);
		this->_emitSuite(mod);
	}
	
	this->modules.push_back(ModuleInfo(mod, stub));
}

void
OwlParser::aModuleTail()
{
	// Block module ended. Unpop all the stubs and topmost non-stub.
	
	bool pop = true;
	
	while (pop) {
		if (this->modules.empty()) {
			return;
		}
		
		pop = this->modules.back().stub;
		this->modules.pop_back();
	}
}

void
OwlParser::aFunc()
{
	std::cout << "func" << std::endl;
}

void
OwlParser::aUse()
{
	std::cout << "use" << std::endl;
}

Sem::QName* OwlParser::aQNameBegin(Sem::IdentExpr* part) const {
	return new Sem::QName(part);
}

Sem::QName* OwlParser::aQNameAppend(Sem::QName* qname, Sem::IdentExpr* part) const {
	return new Sem::QName(qname->append(part));
}

Sem::IdentExpr* OwlParser::aIdentMake(char* ident) const {
	return new Sem::IdentExpr(ident);
}

}
