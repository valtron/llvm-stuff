#include "Sem/Builder.hpp"

int main()
{
	Sem::PackageBuilder builder("test", "0.0.0");
	builder.parse("test.owl");
	
	return 0;
}
