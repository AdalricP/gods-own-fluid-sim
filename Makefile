CC = gcc
CFLAGS = $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2)
TARGET = build/main

all: $(TARGET)

build:
	mkdir -p build

$(TARGET): src/main.c | build
	$(CC) -o $(TARGET) src/main.c $(CFLAGS) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build

.PHONY: all run clean