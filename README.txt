Toy C Compiler

Name: Brandon Frazier
Language: C
Build tool: Make

Instructions: 

    For building: 
        Use command "make" or "make generate"

For running: 
    Use command "make run ARGS="<arguments>"  where <arguments> is replaced with the normal arguments that you would have after the executable if running it direct
    or
    Run executable "tc" in the bin folder and use arguments as usual 

For cleaning: 
    Use command "make clean"

For testing:    
    to test use the same method as running except replace the word "run" with either test or test2
        test will run gdb as normal with the arguments supplied
        test2 will run gdb with the -fsanitize=address tag
