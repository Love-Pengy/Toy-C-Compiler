CC = gcc
CFLAGS = -Wall -O2

objects = d-java.o err_str.o getbytes.o labels.o lltoa.o \
          opcodes.o packages.o reclass.o shattrib.o shclass.o \
          shconst.o shjasmin.o

target = D-Java

$(target) : $(objects)
	gcc -o $(target) $(objects)

d-java.o : d-java.h
err_str.o :
getbytes.o : d-java.h
labels.o : d-java.h
lltoa.o : 
opcodes.o : 
packages.o : 
reclass.o : d-java.h
shattrib.o : d-java.h
shclass.o : d-java.h
shconst.o : d-java.h
shjasmin.o : d-java.h

d-java.h : clconst.h clstruct.h opdefs.h

.PHONY : clean
clean:
	-rm $(target) $(objects)
