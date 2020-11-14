#include "Node.h"
using namespace std;
class Trie{
public:
    Node * root;

    Trie(){
	root = new Node();
    }
    void insert(std::string str){
	Node**temp = &root;
	for (char& c :str){
	    //cout<< (int)c << endl;
	    int posInArr = (int)c -32 ;
	//	cout << c << " " << posInArr << endl;
	    temp = &(*temp)->next[posInArr];

	    if( !(*temp) ) {
		//cout << "creating node" << endl;
		*temp  =new Node();
	    }
	}
	(*temp)->esTerminal = true;
    }
	void dfs (Node *temp, std::string word) {
		if (temp->esTerminal) {
			std::cout << word << std::endl;
		}
		for (int i = 0; i < 94; i++) {
			if (temp->next[i]) {
				word += (char) (i + 32);
				dfs (temp->next[i], word);
			}
		}
	}

	void withPrefix (std::string prefix) {
		Node *temp = root;
		int pos;
		for (int i = 0; i < prefix.size (); i++) {
			pos = ((int) prefix[i]) - 32;
			if (temp->next[pos])
				temp = temp->next[pos];
			else
				return;
		}
		dfs (temp, prefix);
	}
};
