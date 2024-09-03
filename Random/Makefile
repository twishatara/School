CC = gcc -S HW2.c
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: HW2

HW2: HW2.c
	$(CC) $(CFLAGS) -c HW2.c

clean:
	rm -f HW2 *.o

format:
	clang-format -i -style=file *.{c,h}

