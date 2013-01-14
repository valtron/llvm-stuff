#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Analysis/Verifier.h>

int main(int argc, char** argv)
{
	llvm::LLVMContext& ctxt = llvm::getGlobalContext();
	llvm::Module* module = new llvm::Module("test", ctxt);
	module->dump();
	delete module;
	
	return 0;
}
