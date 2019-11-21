CC=g++
CFLAGS=-Wall -g -std=c++11
TARGET=main


all : $(TARGET)

$(TARGET) : main.o functions.o
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.cpp %.h
	$(CC) $(CFLAGS) $< -c

run : $(TARGET)
	./$(TARGET)

clean : 
	rm -rf *.o