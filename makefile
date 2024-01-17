all: test_zco test_zco_queue

CC = gcc
CFLAGS = -fsanitize=address -Wall -Werror -g
SRC = zco.c mutex.c

test_zco: test/test_zco.c
	$(CC) $(CFLAGS) -o $@ $< $(SRC)

test_zco_queue: test/test_zco_queue.c
	$(CC) $(CFLAGS) -o $@ $< $(SRC)

clean:
	rm test_zco test_zco_queue -rf