CC=g++
OPTS=-lrt -lpthread -lstdc++

.PHONY: all dependencies clean

all: dependencies
	cp src/arduPi.o .
	cp src/*.h .
	$(CC) $(OPTS) $(TARGET).cpp *.o -o $(TARGET)

dependencies:
	$(CC) -c ./src/*.cpp

clean:
	rm -f *.o
