.PHONY: all generate test clean run 

.DEFAULT_GOAL := generate

ARGS=""

generate: 
	@gcc ./src/tc.c ./src/TCCMDLineReader.c ./src/TCglobals.c ./src/TClexer.c ./src/TCtoken.c -o ./bin/tc -Wall
	@echo "Generation Has Completed"

test: 
	@gcc ./src/tc.c ./src/TCCMDLineReader.c ./src/TCglobals.c ./src/TClexer.c ./src/TCtoken.c -g -o ./bin/tc 
	@gdb --args ./bin/tc $(ARGS)

clean:	
	@rm ./bin/*
	@echo "Cleaning Has Completed"

run: 
	@./bin/tc $(ARGS) 



