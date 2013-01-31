#include "Codegen.hpp"

#include "Debug.hpp"

#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Module.h>
#include <llvm/LLVMContext.h>
#include <llvm/IRBuilder.h>

#include "Sem/Builder.hpp"
#include "Sem/Suite.hpp"
#include "Sem/Code.hpp"

#include <sstream>
#include <vector>

#define IF_IS(e, T, v) auto v = dynamic_cast<T>(e); if (v)

namespace Codegen
{

Compiler::Compiler(Sem::PackageBuilder* builder, llvm::LLVMContext& lctx)
	: builder(builder), lctx(lctx)
{
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
	llvm::Type* ret_type;
	
	if (func->ret_type) {
		ret_type = this->lookupType(func->ret_type);
	} else {
		ret_type = llvm::Type::getVoidTy(lctx);
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
	
	CodeWalker codewalker(llfunc, lctx);
	codewalker.codegen(func->body);
}

llvm::Type* Compiler::lookupType(Sem::TypeRef* typeref) {
	if (typeref) {
		return llvm::Type::getInt8Ty(lctx);
	} else {
		return llvm::Type::getInt8Ty(lctx);
		//return llvm::Type::getVoidTy(lctx);
	}
}

// CodeWalker

CodeWalker::CodeWalker(llvm::Function* func, llvm::LLVMContext& lctx)
	: func(func), builder(func, lctx) {}

void CodeWalker::codegen(Sem::Stmt* body)
{
	// TODO
	
	/*
	for (ll_arg, param, ll_param_type) in izip(self.ll_func.args, obj.params, self.ll_param_types):
			alloca = self._declare_var(ll_param_type, param.name)
			self._builder.inst('store', ll_arg, alloca)
			
			# TODO: This *always* sets the argument to the default value
			if param.default:
				self._builder.inst('store', param.default.accept(self), alloca)
		
		body.accept(self)
	*/
	
	this->builder.finalize();
}

// Builder

Builder::Builder(llvm::Function* func, llvm::LLVMContext& lctx)
	: lctx(lctx), func(func), builder(lctx)
{
	this->entry_block = llvm::BasicBlock::Create(lctx, "entry", this->func);
	this->first_block = llvm::BasicBlock::Create(lctx, "bl0", this->func);
	this->block_count = 1;
	
	this->builder.SetInsertPoint(this->first_block);
}

llvm::AllocaInst*
Builder::createVar(llvm::Type* type, const std::string& name)
{
	llvm::AllocaInst* ret;
	
	auto ip = this->builder.saveIP();
	this->builder.SetInsertPoint(this->entry_block);
	
	ret = this->builder.CreateAlloca(type, 0, name);
	
	this->builder.restoreIP(ip);
	
	return ret;
}

bool Builder::isInBlock() const {
	return bool(this->builder.GetInsertBlock());
}

llvm::BasicBlock* Builder::startBlock() {
	std::stringstream ss;
	ss << "bl" << this->block_count;
	std::string label = ss.str();
	
	this->block_count += 1;
	auto block = llvm::BasicBlock::Create(lctx, label, this->func);
	return block;
}

void Builder::setBlock(llvm::BasicBlock* block) {
	if (block) {
		this->builder.ClearInsertionPoint();
	} else {
		this->builder.SetInsertPoint(block);
	}
}

void Builder::finalize() {
	this->builder.SetInsertPoint(this->entry_block);
	this->builder.CreateBr(this->first_block);
}

void Builder::instRetVoid() {
	this->builder.CreateRetVoid();
}

}
