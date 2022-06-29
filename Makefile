OUTPUT=main
FREETYPE_FLAGS=$(shell pkg-config --cflags freetype2)
CC=clang++

build:
	$(CC) glad/glad.c src/*.c* -lglfw -lGL -lfreetype -o $(OUTPUT) $(FREETYPE_FLAGS)

clean:
	-rm $(OUTPUT)

test: build
	./$(OUTPUT)

.PHONY: build clean test