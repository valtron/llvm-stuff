#LLVM_CONFIG := llvm-config
CXX := g++ -c
#CXXFLAGS := -g $(shell $(LLVM_CONFIG) --cppflags)
CXXFLAGS := -g
LD := g++
#LLVM_LDFLAGS = $(shell llvm-config --libs core) $(shell llvm-config --ldflags)
#LDFLAGS := -static-libgcc -static-libstdc++ $(LLVM_LDFLAGS)
LDFLAGS := -static-libgcc -static-libstdc++
BINDIR = bin

test: $(BINDIR)/main.exe
	@$(BINDIR)/main.exe

$(BINDIR)/main.exe: bindir $(BINDIR)/main.o $(BINDIR)/Parser/lex.owl.o $(BINDIR)/Parser/owl.tab.o
	@$(LD) $(LDFLAGS) -o $(BINDIR)/main.exe $(BINDIR)/main.o $(BINDIR)/Parser/lex.owl.o $(BINDIR)/Parser/owl.tab.o

bindir:
	@mkdir -p $(BINDIR)
	@mkdir -p $(BINDIR)/Parser

$(BINDIR)/main.o: main.cpp
	@$(CXX) $(CXXFLAGS) -o $(BINDIR)/main.o main.cpp

$(BINDIR)/Parser/lex.owl.o: Parser/lex.owl.c Parser/owl.tab.h
	@$(CXX) $(CXXFLAGS) -o $(BINDIR)/Parser/lex.owl.o Parser/lex.owl.c

Parser/lex.owl.c: Parser/Owl.l
	@flex --outfile=Parser/lex.owl.c Parser/owl.l

$(BINDIR)/Parser/owl.tab.o: Parser/Owl.tab.c
	@$(CXX) $(CXXFLAGS) -o $(BINDIR)/Parser/owl.tab.o Parser/owl.tab.c

Parser/owl.tab.c Parser/owl.tab.h: Parser/owl.y
	@bison --file-prefix=Parser/owl Parser/owl.y

.PHONY: clean
clean:
	rm -f $(BINDIR)/*.exe
	rm -f $(BINDIR)/*.o $(BINDIR)/Parser/*.o
	rm -f Parser/owl.tab.c Parser/owl.tab.h Parser/lex.owl.c
