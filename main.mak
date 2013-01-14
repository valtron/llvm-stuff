LLVM_CONFIG := llvm-config
CXX := g++ -c
CXXFLAGS := -g $(shell $(LLVM_CONFIG) --cppflags)
LD := g++
LLVM_LDFLAGS = $(shell llvm-config --libs core) $(shell llvm-config --ldflags)
LDFLAGS := -static-libgcc -static-libstdc++ $(LLVM_LDFLAGS)
BINDIR = bin

test: exec_main
	@$(BINDIR)/main.exe

exec_main:
	@$(CXX) $(CXXFLAGS) main.cpp -o $(BINDIR)/main.o
	@$(LD) $(BINDIR)/main.o $(LDFLAGS) -o $(BINDIR)/main.exe

parser:
	flex owl.l
	bison owl.yy
