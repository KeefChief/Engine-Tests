TARGET = engine
CC = gcc
CFLAGS = -Wall -Wextra -MMD -MP -pthread -Iinclude -fsanitize=address -fno-omit-frame-pointer 
LFLAGS = -fsanitize=address $(shell pkg-config --libs sdl2) -lSDL2_image
SRC = $(wildcard source/*.c)
OBJ = $(SRC:source/%.c=build/%.o)
DEPS = $(OBJ:.o=.d)
-include $(DEPS)

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
