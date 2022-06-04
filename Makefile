#Benjamin Reeves
#CS 262, Lab section 208
#Project 2
CC = gcc
CFLAGS= -g -Wall -std=c89 -pedantic-errors -O2
TARGET = p2_breeves6_208

all: $(TARGET).c
	$(CC) $(TARGET).c -o $(TARGET) $(CFLAGS)
clean:
	rm $(TARGET)