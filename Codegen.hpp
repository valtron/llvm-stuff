#pragma once

namespace Sem {
	class PackageBuilder;
	class Package;
	class Func;
	class TypeRef;
}

namespace llvm {
	class Module;
	class Type;
}

namespace Codegen
{

class Compiler
{
	Sem::PackageBuilder* builder;
	llvm::Module* mod;
	
public:
	Compiler(Sem::PackageBuilder*);
	llvm::Module* compile();
	
private:
	void compileFunc(Sem::Func*);
	llvm::Type* lookupType(Sem::TypeRef*);
};

}
