TARGET = engine
CC = gcc
CFLAGS = -Wall -Wextra -g -pthread -Iinclude -I../MyDisplaySTuff/include/ -fsanitize=address -fno-omit-frame-pointer 
LFLAGS = -L../MyDisplaySTuff/build -fsanitize=address -lX11 -lpmm
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
