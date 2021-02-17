# compiler
CC = g++

# compiler flags
CFLAGS = -g -Wall

# build target
TARGET = main

all:
	$(CC) $(CFLAGS) -o knotandcross $(TARGET).cpp
