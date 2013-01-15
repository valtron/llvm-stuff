#include <iostream>
#include "Parser/OwlParser.hpp"

int main()
{
	Parser::OwlParser parser(&std::cin);
	
	if (parser.parse())
	{
		std::cout << parser.result << std::endl;
	}
}
