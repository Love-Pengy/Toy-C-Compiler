.PHONY: all generate test test2 clean run 

.DEFAULT_GOAL := generate

DEBUG = @

tc: ./build/TCCMDLineReader.o ./build/TCglobals.o ./build/TCtoken.o ./build/tc.o ./build/TClexer.o ./build/TCparser.o
	$(DEBUG)gcc ./build/TClexer.o ./build/tc.o ./build/TCCMDLineReader.o ./build/TCglobals.o ./build/TCtoken.o ./build/TCparser.o -o ./bin/tc -Wall	

TCCMDLineReader.o: ./src/cmdLine/TCCMDLineReader.c ./include/cmdLine/TCCMDLineReader.h
	$(DEBUG)gcc -c ./src/cmdLine/TCCMDLineReader.c -o ./build/TCCMDLineReader.o -Wall

TCglobals.o: ./src/cmdLine/TCglobals.c ./include/cmdLine/TCglobals.h
	$(DEBUG)gcc -c ./src/cmdLine/TCglobals.c -o ./build/TCglobals.o -Wall

TCtoken.o: ./src/lexer/TCtoken.c ./include/lexer/TCtoken.h 	
	$(DEBUG)gcc -c ./src/lexer/TCtoken.c -o ./build/TCtoken.o -Wall

tc.o: ./src/tc.c
	$(DEBUG)gcc -c ./src/tc.c -o ./build/tc.o -Wall

TClexer.o: ./src/lexer/TClexer.c ./include/lexer/TClexer.h
	$(DEBUG)gcc -c ./src/lexer/TClexer.c -o ./build/TClexer.o -Wall

TCparser.o: ./src/parser/TCparser.c ./include/parser/TCparser.h
	$(DEBUG)gcc -c ./src/parser/TCparser.c -o ./build/TCparser.o -Wall

generate: TCCMDLineReader.o TCglobals.o TCtoken.o TClexer.o TCparser.o tc.o tc 
	@echo "Generation Has Completed"

test: 
	$(DEBUG)gcc ./build/tc.o ./build/TCCMDLineReader.o ./build/TCglobals.o ./build/TClexer.o ./build/TCtoken.o ./build/TCparser.o -g -o ./bin/tc -Wall 
	@gdb --args ./bin/tc $(ARGS)

test2: 
	$(DEBUG)gcc -fsanitize=address ./build/tc.o ./build/TCCMDLineReader.o ./build/TCglobals.o ./build/TClexer.o ./build/TCtoken.o ./build/TCparser.o -g -o ./bin/tc -Wall 
	@gdb --args ./bin/tc $(ARGS)

clean:	
	$(DEBUG)rm ./bin/tc
	$(DEBUG)rm ./build/*
	@echo "Cleaning Has Completed"

run: 
	@./bin/tc $(ARGS) 



