CC=g++
CFLAGS=-g
ALLOBJ=main.o
DEPS=Node.h TernarySearchTree.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

TernarySearchTree: $(ALLOBJ)
	$(CC) -o $@ $^ $(CFLAGS)
.PHONY: clean

clean:
	rm -f TernarySearchTree
	rm -f TernarySearchTree.jpeg
	rm -f $(ALLOBJ)
