#include "Codegen.hpp"

#include <llvm/Module.h>
#include <llvm/LLVMContext.h>

#include "Sem/Builder.hpp"
#include "Sem/Suite.hpp"

namespace Codegen
{

Compiler::Compiler(Sem::PackageBuilder* builder): builder(builder) {
	auto pkg = builder->package;
	this->mod = new llvm::Module(pkg->name, llvm::getGlobalContext());
}

llvm::Module* Compiler::compile() {
	for (auto suite: this->builder->suites) {
		// TODO
	}
	
	return this->mod;
}

}
