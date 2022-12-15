CC=gcc
CFLAGS ?= -O2

TEST_FILE=p2

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

p1: p1.o
	$(CC) -o $@ $^ $(CFLAGS)


p2: p2.o
	$(CC) -o $@ $^ $(CFLAGS)


new: clean $(TEST_FILE)
	./$(TEST_FILE) < test_input.txt


clean:
	rm -f *.o p1 p2

