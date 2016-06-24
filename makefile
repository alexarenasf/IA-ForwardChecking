OBJS = *.cpp
CC = g++

all:
	$(CC) $(OBJS) -o fc-cbj.app
	./fc-cbj.app -instance $(INSTANCE)

routes:
	$(CC) $(OBJS) -o fc-cbj.app
	./fc-cbj.app -instance $(INSTANCE) -make-routes


