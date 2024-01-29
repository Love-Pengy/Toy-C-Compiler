.PHONY: all generate test clean run 

.DEFAULT_GOAL := generate

generate: 
	@gcc main.c mod1.c mod2.c -Wall -o compiler.out
	@echo "Generation Has Completed"

test: 
	@echo "Testing Hasn't Been Set Up Yet!"

clean:	
	@rm *.out
	@echo "Cleaning Has Completed"

run: 
	@./compiler.out



