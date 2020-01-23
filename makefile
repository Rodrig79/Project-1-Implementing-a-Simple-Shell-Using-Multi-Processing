#Makefile
OBJS = p1.o
CC = g++
DEBUG = -g 
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
    $(CC)  $(LFLAGS)  $(OBJS)  –o  p1

p1.o : p1.h  
    $(CC)  $(CFLAGS)  p1.cpp

clean:
    \rm *.o *~
