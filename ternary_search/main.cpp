#include "TernarySearchTree.h"
#include <chrono>

int main () {
	TernarySearchTree t;
	t.index ("filePaths.txt");
	auto start = std::chrono::high_resolution_clock::now ();
	for (int i = 0; i < 10; i++) {
		t.withPrefix ("Con");
		t.withPrefix ("Emergency");
		t.withPrefix ("jasper");
		t.withPrefix ("CS");
		t.withPrefix ("Software");
		t.withPrefix ("EDA");
		t.withPrefix ("Initial");
		t.withPrefix ("classified");
		t.withPrefix ("standard");
		t.withPrefix ("s");
	}
	auto end = std::chrono::high_resolution_clock::now ();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
	std::cout << "duration: " << duration << "us" << std::endl;
	std::cout << "Size in bytes: " << t.getBytes () << std::endl;
}
