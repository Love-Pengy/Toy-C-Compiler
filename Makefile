.PHONY: all generate test clean run 

.DEFAULT_GOAL := generate

ARGS=""

tc: ./build/TCCMDLineReader.o ./build/TCglobals.o ./build/TCtoken.o ./build/tc.o ./build/TClexer.o
	@gcc ./build/TClexer.o ./build/tc.o ./build/TCCMDLineReader.o ./build/TCglobals.o ./build/TCtoken.o -o ./bin/tc	

TCCMDLineReader.o: ./src/TCCMDLineReader.c ./include/TCCMDLineReader.h
	@gcc -c ./src/TCCMDLineReader.c -o ./build/TCCMDLineReader.o

TCglobals.o: ./src/TCglobals.c ./include/TCglobals.h
	@gcc -c ./src/TCglobals.c -o ./build/TCglobals.o

TCtoken.o: ./src/TCtoken.c ./include/TCtoken.h 	
	@gcc -c ./src/TCtoken.c -o ./build/TCtoken.o

tc.o: ./src/tc.c
	@gcc -c ./src/tc.c -o ./build/tc.o

TClexer.o: ./src/TClexer.c ./include/TClexer.h
	@gcc -c ./src/TClexer.c -o ./build/TClexer.o

generate: TCCMDLineReader.o TCglobals.o TCtoken.o TClexer.o tc.o tc
	@echo "Generation Has Completed"

test: 
	@gcc ./build/tc.o ./build/TCCMDLineReader.o ./build/TCglobals.o ./build/TClexer.o ./build/TCtoken.o -g -o ./bin/tc 
	@gdb --args ./bin/tc $(ARGS)

clean:	
	@rm ./bin/tc
	@rm ./build/*
	@echo "Cleaning Has Completed"

run: 
	@./bin/tc $(ARGS) 



