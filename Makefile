.PHONY: all generate test clean run 

.DEFAULT_GOAL := generate

ARGS=""

generate: 
	@gcc ./src/tc.c ./src/TCCMDLineReader.c ./src/TCglobals.c -o ./bin/tc -Wall
	@echo "Generation Has Completed"

test: 
	@gcc ./src/tc.c ./src/TCCMDLineReader.c ./src/TCglobals.c -g -o ./bin/tc 
	@gdb --args ./bin/tc $(ARGS)

clean:	
	@rm *.out
	@echo "Cleaning Has Completed"

run: 
	@./bin/tc $(ARGS) 



