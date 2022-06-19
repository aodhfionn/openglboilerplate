OUTPUT=main

build:
	g++ src/*.c* -lglfw -lGL -o $(OUTPUT)

clean:
	-rm $(OUTPUT)

test: build
	./$(OUTPUT)

.PHONY: build clean test