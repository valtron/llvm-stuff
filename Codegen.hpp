#pragma once

#include <llvm/LLVMContext.h>
#include <llvm/IRBuilder.h>

namespace Sem {
	class PackageBuilder;
	class Package;
	class Func;
	class TypeRef;
	class Stmt;
}

namespace llvm {
	class Module;
	class Type;
	class Function;
	class AllocaInst;
}

namespace Codegen
{

class Compiler
{
	llvm::LLVMContext& lctx;
	Sem::PackageBuilder* builder;
	llvm::Module* mod;
	
public:
	Compiler(Sem::PackageBuilder*, llvm::LLVMContext&);
	llvm::Module* compile();
	
private:
	void compileFunc(Sem::Func*);
	llvm::Type* lookupType(Sem::TypeRef*);
};

class Builder
{
	llvm::LLVMContext& lctx;
	llvm::Function* func;
	int block_count;
	llvm::BasicBlock* entry_block;
	llvm::BasicBlock* first_block;
	llvm::IRBuilder<> builder;
	
public:
	Builder(llvm::Function*, llvm::LLVMContext&);
	
	llvm::AllocaInst* createVar(llvm::Type*, const std::string&);
	bool isInBlock() const;
	
	llvm::BasicBlock* startBlock();
	void setBlock(llvm::BasicBlock*);
	
	void finalize();
	
	void instRetVoid();
};

class CodeWalker
{
	llvm::Function* func;
	Builder builder;
	
public:
	CodeWalker(llvm::Function*, llvm::LLVMContext&);
	
	void codegen(Sem::Stmt*);
};

}
