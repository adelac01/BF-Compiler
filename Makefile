GXX := g++

blah: 
	$(GXX) -g -Wall -std=c++20 -o bf src/codegen.cpp  src/parser.cpp src/lexer.cpp src/main.cpp 