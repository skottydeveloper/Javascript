# Variables:
CC = gcc
CFLAGS = -Wall
LIBS = -lpthread -lrt
TARGET = program_1

# Default target:
all: $(TARGET)

# Build the target:
$(TARGET): program_1.c
	$(CC) $^ -o $@ $(LIBS) $(CFLAGS)

# Run program_1:
run_prog_1: $(TARGET1)
	./$(TARGET1)	

# Clean:
clean:
	rm -f $(TARGET) output.txt