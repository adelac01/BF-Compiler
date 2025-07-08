GXX := g++

blah: 
	$(GXX) -Wall -std=c++20 -Wall -g -o bf src/codegen.cpp  src/parser.cpp src/lexer.cpp src/main.cpp 