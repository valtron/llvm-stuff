#LLVM_CONFIG := llvm-config
CXX := g++ -c
#CXXFLAGS := -g $(shell $(LLVM_CONFIG) --cppflags)
CXXFLAGS := -g
LD := g++
#LLVM_LDFLAGS = $(shell llvm-config --libs core) $(shell llvm-config --ldflags)
#LDFLAGS := -static-libgcc -static-libstdc++ $(LLVM_LDFLAGS)
LDFLAGS := -static-libgcc -static-libstdc++
BINDIR = bin

test: exec_main
	@$(BINDIR)/main.exe

exec_main: bindir parser
	@$(CXX) $(CXXFLAGS) main.cpp -o $(BINDIR)/main.o
	@$(LD) $(BINDIR)/main.o $(LDFLAGS) -o $(BINDIR)/main.exe

bindir:
	@mkdir -p $(BINDIR)

parser: Parser/owl.tab.hh

Parser/owl.tab.hh: Parser/owl.yy Parser/owl.l
	@flex --outfile=Parser/lex.yy.cc --header-file=OwlLexer.hpp Parser/owl.l
	@bison --file-prefix=Parser/owl Parser/owl.yy
