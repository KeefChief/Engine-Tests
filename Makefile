TARGET = engine
CC = gcc
CFLAGS = -Wall -Wextra -g -pthread -Iinclude 
SRC = $(wildcard source/*.c)
OBJ = $(SRC:source/%.c=build/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $(TARGET)

build/%.o: source/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*.o

run:$(TARGET)
	./$(TARGET)

.PHONY: all clean
