#include <iostream>

#include <llvm/Module.h>

#include "Sem/Builder.hpp"
#include "Codegen.hpp"

int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " file..." << std::endl;
		return -1;
	}
	
	Sem::PackageBuilder builder("test", "0.0.0");
	
	for (int i = 1; i < argc; ++i) {
		builder.parse(argv[i]);
	}
	
	Codegen::Compiler compiler(&builder);
	auto compiled = compiler.compile();
	
	compiled->dump();
	
	return 0;
}
