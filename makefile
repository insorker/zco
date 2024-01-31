CC = gcc
CFLAGS = -Wall -Werror -g # -fsanitize=address
SRC = zco.c mutex.c zco_queue.c zco_aio.c
TESTS = test_zco test_zco_queue test_zco_file test_zco_aio

all: $(TESTS)

%: test/%.c
	$(CC) $(CFLAGS) -o ./test/lib/$@ $< $(SRC)

clean:
	rm $(patsubst %, ./test/lib/%, $(TESTS)) -rf