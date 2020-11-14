#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

struct Node{
public:
    Node* next[94]; // 32 al 126
    bool esTerminal;
    Node(){
	esTerminal=false;
	for (int i = 0; i < 94; i++) {
		next[i] = nullptr;
	}
    }
/*

class Node {
protected:
	Node *left, *equal, *right;
	char key;
	bool terminal;
	std::vector<std::pair<int, int>> paths;
	std::unordered_map<int, std::vector<std::string>> sizes;
public:
	Node () : left (nullptr), equal (nullptr), right (nullptr) {
		key = '-';
	};
	Node (char key) : key (key), left (nullptr), equal (nullptr), right (nullptr), terminal (false) {};
	Node (bool terminal) : terminal (terminal), left (nullptr), equal (nullptr), right (nullptr) {
		key = '-';
	};

	char getKey () { return key; }

	bool isTerminal () { return terminal; }

	void print (int count) {
		std::cout << key;
		if (terminal)
			std::cout << "*";
		std::cout <<  std::endl;
		if (left)
			left->print (count+1);
		if (right)
			right->print (count+1);
		if (equal)
			equal->print (count+1);
	}

	void addPath (std::pair<int, int> path) {
		paths.push_back (path);
	}

	std::vector<std::pair<int, int>> getPaths () {
		return paths;
	}
	~Node () {
		delete left;
		delete equal;
		delete right;
	}
	friend class TernarySearchTree;
   */
};
