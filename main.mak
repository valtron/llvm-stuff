#LLVM_CONFIG := llvm-config
CXX := g++ -c
#CXXFLAGS := -g $(shell $(LLVM_CONFIG) --cppflags)
CXXFLAGS := -g
LD := g++
#LLVM_LDFLAGS = $(shell llvm-config --libs core) $(shell llvm-config --ldflags)
#LDFLAGS := -static-libgcc -static-libstdc++ $(LLVM_LDFLAGS)
LDFLAGS := -static-libgcc -static-libstdc++
CSRCS=Parser/lex.owl.c Parser/owl.tab.c
CXXSRCS=main.cpp Sem/Builder.cpp Sem/Code.cpp Sem/Suite.cpp
SRCS=$(CSRCS) $(CXXSRCS)
OBJS=$(CSRCS:.c=.o) $(CXXSRCS:.cpp=.o)
MAIN=main.exe

all: $(MAIN)

test: all
	@$(MAIN) test.owl

$(MAIN): $(OBJS)
	@$(LD) $(LDFLAGS) -o $(MAIN) $(OBJS)

.cpp.o:
	@$(CXX) -c $< $(CXXFLAGS) -std=c++0x -o $@

.c.o:
	@$(CXX) -c $< $(CXXFLAGS) -Wno-error -Wno-all -Wno-fatal-errors -o $@

Parser/lex.owl.c: Parser/owl.l Parser/owl.tab.h
	@flex --outfile=Parser/lex.owl.c Parser/owl.l

Parser/owl.tab.c Parser/owl.tab.h: Parser/owl.y Parser/actions.inl
	@bison --file-prefix=Parser/owl Parser/owl.y

clean:
	rm -v `find . \( -name "*.o" -o -name "*.exe" \)`
	rm -vf Parser/owl.tab.c Parser/owl.tab.h Parser/lex.owl.c
