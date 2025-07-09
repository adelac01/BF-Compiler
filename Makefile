GXX := g++

blah: 
	$(GXX) -Wall -std=c++20 -g -o bf src/codegen.cpp  src/parser.cpp src/lexer.cpp src/main.cpp 