CC=gcc
CFLAGS=


TEST_FILE=p1

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

p1: p1.o
	$(CC) -o $@ $^

test: clean $(TEST_FILE)
	./$(TEST_FILE) < test_input.txt > output.txt
	diff correct.txt output.txt


clean:
	rm -f *.o p1 p2

