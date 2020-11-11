#include "Node.h"
#include <stack>
#include <fstream>

class TernarySearchTree {
private:
	Node *root;
	int size;
public:
	TernarySearchTree () : root (nullptr), size (0) {};

	void index (std::string fileName) {
			std::ifstream indexFile (fileName);
			std::string line, name;
			
			int start;
			start = indexFile.tellg ();

			while (std::getline (indexFile, line)) {
				int i = line.size () - 1;
				while (line[i] != '/') {
					name = line[i] + name;
					i--;
				}
				insert (name, start, line.size ());
				name.clear (); 
				start = indexFile.tellg ();
			}
	}
	
	void insert (std::string word, int start, int offset) {
		int i = 0;
		Node *temp;
		if (!root) {
			root = new Node (word[i]);
			i++;
			temp = root;
			while (i < word.size ()) {
				temp->equal = new Node (word[i]);
				size++;
				i++;
				temp = temp->equal;
			}
			temp->equal = new Node (true);
			size++;
			temp->equal->addPath (std::make_pair (start, offset));
			return;
		}
		temp = root;
		while (i < word.size ()) {
				if (temp->key == '-') {
					temp->key = word[i];
					i++;
					while (i < word.size ()) {
						temp->equal = new Node (word[i]);
						i++;
						temp = temp->equal;
					}
					break;
				}
				if (word[i] == temp->key) {
					if (!temp->equal) {
						temp->equal = new Node (word[i]);
						size++;
						i++;
						temp = temp->equal;
						while (i < word.size ()) {
							temp->equal = new Node (word[i]);
							i++;
							temp = temp->equal;
						}
						break;

					}
					temp = temp->equal;
					i++;
				}
				else if (word[i] < temp->key) {
					if (!temp->left) {
						temp->left = new Node (word[i]);
						size++;
						i++;
						temp = temp->left;
						while (i < word.size ()) {
							temp->equal = new Node (word[i]);
							i++;
							temp = temp->equal;
						}
						break;
					}
					temp = temp->left;
				}
				else if (word[i] > temp->key) {
					if (!temp->right) {
						temp->right = new Node (word[i]);
						i++;
						size++;
						temp = temp->right;
						while (i < word.size ()) {
							temp->equal = new Node (word[i]);
							i++;
							temp = temp->equal;
						}
						break;
					}
					temp = temp->right;
				}
		}
		if (temp->key == '-') {
			temp->addPath (std::make_pair (start, offset));
			return;	
		}
		if (temp->equal) {
			temp->equal->terminal = true;
			temp->equal->addPath (std::make_pair (start, offset));
		}
		else {
			temp->equal = new Node (true);
			temp->equal->addPath (std::make_pair (start, offset));
			size++;
		}
	}

	void print () {
		root->print (0);
		std::cout << "size: " << size << std::endl;
	}
	
	void dfs (Node *temp, std::string word) {
		if (temp->terminal) {
			std::cout << word << " present at " << std::endl;
			for (int i = 0; i < temp->getPaths ().size (); i++) {
				std::ifstream pathfile ("filePaths.txt");
				char location [255];
				pathfile.seekg (temp->getPaths ()[i].first);
				pathfile.read (location, temp->getPaths ()[i].second);
				std::cout << location << std::endl;
			}
			std::cout << std::endl;
		}

		if (temp->left)
			dfs (temp->left, word);
		if (temp->right)
			dfs (temp->right, word);
		if (temp->equal) {
			word += temp->key;
			dfs (temp->equal, word);
		}
	}	

	void printWords () {
		std::string word;
		
		dfs (root, word);
	}
	~TernarySearchTree () {
		delete root;
	}
};
