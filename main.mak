LLVM_CONFIG := llvm-config
CXX := g++ -c
CXXFLAGS := -g -std=c++0x $(shell $(LLVM_CONFIG) --cppflags)
LD := g++
LLVM_LDFLAGS = $(shell llvm-config --libs core) $(shell llvm-config --ldflags)
LDFLAGS := -static-libgcc -static-libstdc++ $(LLVM_LDFLAGS)
CSRCS=Parser/lex.owl.c Parser/owl.tab.c
CXXSRCS=main.cpp Sem/Builder.cpp Sem/Code.cpp Sem/Suite.cpp Sem/Walker.cpp Codegen.cpp
SRCS=$(CSRCS) $(CXXSRCS)
OBJS=$(CSRCS:.c=.o) $(CXXSRCS:.cpp=.o)
MAIN=main.exe

all: $(MAIN)

test: all
	@$(MAIN) test.owl

$(MAIN): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(MAIN)

.cpp.o:
	@$(CXX) -c $< $(CXXFLAGS) -o $@

.c.o:
	@$(CXX) -c $< $(CXXFLAGS) -Wno-error -Wno-all -Wno-fatal-errors -o $@

Parser/lex.owl.c: Parser/owl.l Parser/owl.tab.h
	@flex --outfile=Parser/lex.owl.c Parser/owl.l

Parser/owl.tab.c Parser/owl.tab.h: Parser/owl.y Parser/actions.inl
	@bison --file-prefix=Parser/owl Parser/owl.y

clean:
	rm -v `find . \( -name "*.o" -o -name "*.exe" \)`
	rm -vf Parser/owl.tab.c Parser/owl.tab.h Parser/lex.owl.c
