#include "Suite.hpp"

namespace Sem
{

Suite::Suite(const std::string& name, Module* parent): name(name), parent(parent) {}

Module::Module(const std::string& name, Module* parent): Suite::Suite(name, parent) {}

}
