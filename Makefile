CC = gcc
CFLAGS = -Wall -fopenmp -lm

TARGET = main

all: $(TARGET)
	@echo "Compilation Successful!"

$(TARGET): inout.o sort.o main.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) *.o
