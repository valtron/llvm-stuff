#include "Codegen.hpp"

#include "Debug.hpp"

#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>
#include <llvm/LLVMContext.h>
#include <llvm/IRBuilder.h>

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
	
	llvm::Type* ret_type;
	
	if (func->ret_type) {
		ret_type = this->lookupType(func->ret_type);
	} else {
		ret_type = llvm::Type::getVoidTy(ctxt);
	}
	
	auto& params = *func->params;
	
	std::vector<llvm::Type*> param_types;
	for (auto param: params) {
		param_types.push_back(this->lookupType(param->type));
	}
	
	auto llft = llvm::FunctionType::get(ret_type, param_types, false);
	
	auto llfunc = llvm::Function::Create(
		llft, llvm::Function::ExternalLinkage, func->name, this->mod
	);
	
	int i = 0;
	for (auto& llparam: llfunc->getArgumentList()) {
		llparam.setName(params[i]->name);
		i += 1;
	}
	
	auto bb = llvm::BasicBlock::Create(ctxt, "entry", llfunc);
	llvm::IRBuilder<> builder(ctxt);
	builder.SetInsertPoint(bb);
	builder.CreateRetVoid();
}

llvm::Type* Compiler::lookupType(Sem::TypeRef* typeref) {
	return llvm::Type::getInt8Ty(llvm::getGlobalContext());
}

}
