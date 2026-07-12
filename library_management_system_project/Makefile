CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
TARGET = lms
SRC = src/main.c src/menu.c src/books.c src/issues.c src/storage.c src/utils.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c include/lms.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(TARGET) $(TARGET).exe books.dat issues.dat

.PHONY: all clean
