GXX := g++

blah: 
	$(GXX) -g -Wall -o bf src/codegen.cpp  src/parser.cpp src/lexer.cpp src/main.cpp 