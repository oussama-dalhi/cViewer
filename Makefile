CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Iinclude
SDL_FLAGS = $(shell sdl2-config --cflags --libs)
LDLIBS = -lm
TARGET = src/cViewer
SRC = src/cViewer.c
TEST_IMAGE = images/nature.jpg
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(SDL_FLAGS) $(LDLIBS)
.PHONY: clean
clean:
	rm -f $(TARGET)
.PHONY: run
run: $(TARGET)
	./$(TARGET) $(TEST_IMAGE)
