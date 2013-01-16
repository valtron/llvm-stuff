#include <iostream>

namespace Parser
{

void
OwlParser::aModuleHead()
{
	std::cout << "module head" << std::endl;
}

void
OwlParser::aModuleTail()
{
	std::cout << "module tail" << std::endl;
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

}
