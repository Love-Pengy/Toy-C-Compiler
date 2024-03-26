.PHONY: all generate test test2 clean run 

.DEFAULT_GOAL := generate

DEBUG = @

tc: ./build/TCCMDLineReader.o ./build/TCglobals.o ./build/TCtoken.o ./build/tc.o ./build/TClexer.o ./build/TCparser.o ./build/ASBlockStatementSynTree.o ./build/ASNullStatementSynTree.o ./build/ASBreakStatementSynTree.o ./build/ASOperatorSynTree.o ./build/ASDefinitionSynTree.o ./build/ASOpExpressionSynTree.o ./build/ASExpressionStatementSynTree.o ./build/ASProgramSynTree.o ./build/ASExpressionSynTree.o ./build/ASReadStatementSynTree.o ./build/ASFunctionCallSynTree.o ./build/ASReturnStatementSynTree.o ./build/ASFunctionDefinitionSynTree.o ./build/ASStatementSynTree.o ./build/ASVariableDefinitionSynTree.o ./build/ASMinusSynTree.o ./build/ASWhileStatementSynTree.o ./build/ASNewlineStatementSynTree.o ./build/ASWriteStatementSynTree.o ./build/ASNotSynTree.o 
	$(DEBUG)gcc -o ./build/TCCMDLineReader.o ./build/TCglobals.o ./build/TCtoken.o ./build/tc.o ./build/TClexer.o ./build/TCparser.o ./build/ASBlockStatementSynTree.o ./build/ASNullStatementSynTree.o ./build/ASBreakStatementSynTree.o ./build/ASOperatorSynTree.o ./build/ASDefinitionSynTree.o ./build/ASOpExpressionSynTree.o ./build/ASExpressionStatementSynTree.o ./build/ASProgramSynTree.o ./build/ASExpressionSynTree.o ./build/ASReadStatementSynTree.o ./build/ASFunctionCallSynTree.o ./build/ASReturnStatementSynTree.o ./build/ASFunctionDefinitionSynTree.o ./build/ASStatementSynTree.o ./build/ASVariableDefinitionSynTree.o ./build/ASMinusSynTree.o ./build/ASWhileStatementSynTree.o ./build/ASNewlineStatementSynTree.o ./build/ASWriteStatementSynTree.o ./build/ASNotSynTree.o ./bin/tc -Wall	

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

dynamicArray.o: ./lib/dynamicArray/dynamicArray.c ./lib/dynamicArray/dynamicArray.h
	$(DEBUG)gcc -c ./lib/dynamicArray/dynamicArray.c -o ./build/dynamicArray.o -Wall
	
ASBlockStatementSynTree.o: ./src/parser/ASSpecs/ASBlockStatementSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASBlockStatementSynTree.c -o ./build/ASBlockStatementSynTree.o -Wall
	
ASNullStatementSynTree.o: ./src/parser/ASSpecs/ASNullStatementSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASNullStatementSynTree.c -o ./build/ASNullStatementSynTree.o -Wall

ASBreakStatementSynTree.o: ./src/parser/ASSpecs/ASBreakStatementSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASBreakStatementSynTree.c -o ./build/ASBreakStatementSynTree.o -Wall

ASOperatorSynTree.o: ./src/parser/ASSpecs/ASOperatorSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASOperatorSynTree.c -o ./build/ASOperatorSynTree.o -Wall

ASDefinitionSynTree.o: ./src/parser/ASSpecs/ASDefinitionSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASDefinitionSynTree.c -o ./build/ASDefinitionSynTree.o -Wall

ASOpExpressionSynTree.o: ./src/parser/ASSpecs/ASOpExpressionSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASOpExpressionSynTree.c -o ./build/ASOpExpressionSynTree.o -Wall

ASExpressionStatementSynTree.o: ./src/parser/ASSpecs/ASExpressionStatementSynTree.c  ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASExpressionStatementSynTree.c -o ./build/ASExpressionStatementSynTree.o -Wall

ASProgramSynTree.o: ./src/parser/ASSpecs/ASProgramSynTree.c  ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASProgramSynTree.c -o ./build/ASProgramSynTree.o -Wall

ASExpressionSynTree.o: ./src/parser/ASSpecs/ASExpressionSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASExpressionSynTree.c -o ./build/ASExpressionSynTree.o -Wall

ASReadStatementSynTree.o: ./src/parser/ASSpecs/ASReadStatementSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASReadStatementSynTree.c -o ./build/ASReadStatementSynTree.o -Wall

ASFunctionCallSynTree.o: ./src/parser/ASSpecs/ASFunctionCallSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASFunctionCallSynTree.c -o ./build/ASFunctionCallSynTree.o -Wall

ASReturnStatementSynTree.o: ./src/parser/ASSpecs/ASReturnStatementSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASReturnStatementSynTree.c -o ./build/ASReturnStatementSynTree.o -Wall

ASFunctionDefinitionSynTree.o: ./src/parser/ASSpecs/ASFunctionDefinitionSynTree.c  ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASFunctionDefinitionSynTree.c -o ./build/ASFunctionDefinitionSynTree.o -Wall

ASStatementSynTree.o: ./src/parser/ASSpecs/ASStatementSynTree.c  ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASStatementSynTree.c -o ./build/ASStatementSynTree.o -Wall

ASIfStatementSynTree.o: ./src/parser/ASSpecs/ASIfStatementSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASIfStatementSynTree.c -o ./build/ASIfStatementSynTree.o -Wall

ASVariableDefinitionSynTree.o: ./src/parser/ASSpecs/ASVariableDefinitionSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASVariableDefinitionSynTree.c -o ./build/ASVariableDefinitionSynTree.o -Wall

ASMinusSynTree.o: ./src/parser/ASSpecs/ASMinusSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASMinusSynTree.c -o ./build/ASMinusSynTree.o -Wall

ASWhileStatementSynTree.o: ./src/parser/ASSpecs/ASWhileStatementSynTree.c  ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASWhileStatementSynTree.c -o ./build/ASWhileStatementSynTree.o -Wall

ASNewlineStatementSynTree.o: ./src/parser/ASSpecs/ASNewlineStatementSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASNewlineStatementSynTree.c -o ./build/ASNewlineStatementSynTree.o -Wall

ASWriteStatementSynTree.o: ./src/parser/ASSpecs/ASWriteStatementSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASWriteStatementSynTree.c -o ./build/ASWriteStatementSynTree.o -Wall

ASNotSynTree.o: ./src/parser/ASSpecs/ASNotSynTree.c ./include/parser/ASsynTree.h
	$(DEBUG)gcc -c ./src/parser/ASSpecs/ASNotSynTree.c -o ./build/ASNotSynTree.o -Wall

generate: TCCMDLineReader.o TCglobals.o TCtoken.o TClexer.o dynamicArray.o ASBlockStatementSynTree.o ASNullStatementSynTree.o ASBreakStatementSynTree.o ASOperatorSynTree.o ASDefinitionSynTree.o ASOpExpressionSynTree.o ASExpressionStatementSynTree.o ASProgramSynTree.o ASExpressionSynTree.o ASReadStatementSynTree.o ASFunctionCallSynTree.o ASReturnStatementSynTree.o ASFunctionDefinitionSynTree.o ASStatementSynTree.o ASIfStatementSynTree.o ASVariableDefinitionSynTree.o ASMinusSynTree.o ASWhileStatementSynTree.o ASNewlineStatementSynTree.o ASWriteStatementSynTree.o ASNotSynTree.o TCparser.o tc.o tc 
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



