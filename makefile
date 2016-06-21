OBJS = *.cpp
CC = g++
LIBS = 

all:
	$(CC) $(OBJS) -o fc-cbj.app $(LIBS)
	./fc-cbj.app
