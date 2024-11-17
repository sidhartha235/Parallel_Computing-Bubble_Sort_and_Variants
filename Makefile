CC = gcc
CFLAGS = -Wall -fopenmp
MATH = -lm
TARGET = main

.PHONY: all clean

all: $(TARGET)
	@echo "Compilation Successful!"

$(TARGET): inout.o sort.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(MATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o
