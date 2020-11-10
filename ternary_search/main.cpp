#include "TernarySearchTree.h"

int main () {
	TernarySearchTree t;
	/*t.insert ("Emergency.pdf", 0, 0);
	t.insert ("Expired.pdf", 0, 0);
	t.insert ("Eric Freeman", 0, 0);
	t.insert ("Emergency.pdf", 0, 0);
	t.insert ("Expired.pdf", 0, 0);
	t.insert ("TALLERES", 0, 0);*/
	t.index ("filePaths.txt");
	t.printWords ();
}
