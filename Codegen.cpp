#include "Codegen.hpp"

#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>
#include <llvm/LLVMContext.h>

#include "Sem/Builder.hpp"
#include "Sem/Suite.hpp"

#include <vector>

#define IF_IS(e, T, v) auto v = dynamic_cast<T>(e); if (v)

namespace Codegen
{

Compiler::Compiler(Sem::PackageBuilder* builder): builder(builder) {
	auto pkg = builder->package;
	this->mod = new llvm::Module(pkg->name, llvm::getGlobalContext());
}

llvm::Module* Compiler::compile() {
	for (auto suite: this->builder->suites) {
		IF_IS(suite, Sem::Func*, func) {
			this->compileFunc(func);
		}
		IF_IS(suite, Sem::Module*, module) {
			
		}
		IF_IS(suite, Sem::Use*, use) {
			
		}
	}
	
	return this->mod;
}

void Compiler::compileFunc(Sem::Func* func) {
	auto& ctxt = llvm::getGlobalContext();
	
	std::vector<llvm::Type*> params;
	llvm::ArrayRef<llvm::Type*> llparams(params);
	auto llft = llvm::FunctionType::get(llvm::Type::getVoidTy(ctxt), params, false);
	
	auto llfunc = this->mod->getOrInsertFunction(func->name, llft);
}

}
