CC = gcc
CFLAGS = $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2) -lm
TARGET = build/main

all: $(TARGET)

build:
	mkdir -p build

$(TARGET): src/main.c src/camera/camera.c | build
	$(CC) -o $(TARGET) src/main.c src/camera/camera.c $(CFLAGS) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build

play: clean all run

.PHONY: all run clean play