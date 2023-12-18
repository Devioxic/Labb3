CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = main.c fil.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = CarRegister

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)
