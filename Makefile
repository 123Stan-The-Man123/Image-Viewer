CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = src/main.c
DEST = bin/main

$(DEST): $(SRC)
	mkdir -p bin
	$(CC) $^ -o $@ $(CFLAGS) $(shell pkg-config --cflags --libs sdl3)

test: $(DEST)
	$(shell cat images/griffith.ppm | $(DEST))

clean:
	rm -rf bin
