# compiler
CC = g++

# compiler flags
CFLAGS = -g -Wall

# build target
TARGET = main.cpp

all: $(TARGET)
	$(CC) $(CFLAGS) -o knotandcross $(TARGET)
