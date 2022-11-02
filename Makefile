OUTPUT=main
FREETYPE_FLAGS=$(shell pkg-config --cflags freetype2)
CC=clang++
INCLUDE_PATH=/usr/include

build:
	$(CC) glad/glad.c src/*.c* -lglfw -lGL -lfreetype -o $(OUTPUT) $(FREETYPE_FLAGS)

setup:
	cp -r glad/include/* $(INCLUDE_PATH)

clean:
	-rm $(OUTPUT)

test: build
	./$(OUTPUT)

.PHONY: build clean test