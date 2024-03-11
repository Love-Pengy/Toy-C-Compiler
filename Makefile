.PHONY: all generate test clean run 

.DEFAULT_GOAL := generate

DEBUG = @

tc: ./build/TCCMDLineReader.o ./build/TCglobals.o ./build/TCtoken.o ./build/tc.o ./build/TClexer.o ./build/TCparser.o
	$(DEBUG)gcc ./build/TClexer.o ./build/tc.o ./build/TCCMDLineReader.o ./build/TCglobals.o ./build/TCtoken.o ./build/TCparser.o -o ./bin/tc -Wall	

TCCMDLineReader.o: ./src/TCCMDLineReader.c ./include/TCCMDLineReader.h
	$(DEBUG)gcc -c ./src/TCCMDLineReader.c -o ./build/TCCMDLineReader.o -Wall

TCglobals.o: ./src/TCglobals.c ./include/TCglobals.h
	$(DEBUG)gcc -c ./src/TCglobals.c -o ./build/TCglobals.o -Wall

TCtoken.o: ./src/TCtoken.c ./include/TCtoken.h 	
	$(DEBUG)gcc -c ./src/TCtoken.c -o ./build/TCtoken.o -Wall

tc.o: ./src/tc.c
	$(DEBUG)gcc -c ./src/tc.c -o ./build/tc.o -Wall

TClexer.o: ./src/TClexer.c ./include/TClexer.h
	$(DEBUG)gcc -c ./src/TClexer.c -o ./build/TClexer.o -Wall

TCparser.o: ./src/TCparser.c ./include/TCparser.h
	$(DEBUG)gcc -c ./src/TCparser.c -o ./build/TCparser.o -Wall

generate: TCCMDLineReader.o TCglobals.o TCtoken.o TClexer.o TCparser.o tc.o tc 
	@echo "Generation Has Completed"

test: 
	$(DEBUG)gcc ./build/tc.o ./build/TCCMDLineReader.o ./build/TCglobals.o ./build/TClexer.o ./build/TCtoken.o ./build/TCparser.o -g -o ./bin/tc -Wall 
	@gdb --args ./bin/tc $(ARGS)

clean:	
	$(DEBUG)rm ./bin/tc
	$(DEBUG)rm ./build/*
	@echo "Cleaning Has Completed"

run: 
	@./bin/tc $(ARGS) 



