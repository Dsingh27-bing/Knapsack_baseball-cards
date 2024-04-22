CC = g++
CFLAGS  = -g -Wall
default: program1

program1: program1.o
	$(CC) $(CFLAGS) -o program1 program1.o -lm

program1.o: program1.cpp
	$(CC) $(CFLAGS) -c program1.cpp

clean:
	$(RM) program1 *.o *~ output.txt
