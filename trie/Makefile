CC=g++
CFLAGS= -Wall -g
ALLOBJ=main.o
DEPS=Node.h Trie.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Trie: $(ALLOBJ)
	$(CC) -o $@ $^ $(CFLAGS)
.PHONY: clean

clean:
	rm -f Trie
	rm -f $(ALLOBJ)
