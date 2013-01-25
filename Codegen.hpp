#pragma once

namespace Sem {
	class PackageBuilder;
	class Package;
	class Func;
}

namespace llvm {
	class Module;
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
};

}
