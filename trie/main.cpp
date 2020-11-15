#include <iostream>
#include <string>

using namespace std;
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
};

class Trie{
private:
    Node * root;
public:
    Trie(){
		root = new Node();
    }
    void insert(std::string str){
	Node**temp = &root;
	for (char& c :str){
	    //cout<< (int)c << endl;
	    int posInArr = (int)c -32 ;
		cout << c << " " << posInArr << endl;
	    temp = &(*temp)->next[posInArr];

	    if( !(*temp) ) {
		//cout << "creating node" << endl;
		*temp  =new Node();
	    }
	}
	(*temp)->esTerminal = true;
    }
    /*void printTrie(){
	Node* imprimir = root;
        std::string pal;
        for(auto it = imprimir->next.begin(); it != imprimir->next.end(); ++it) {
            pal.push_back(it->first);
            print_helper(pal, it->second);
            pal.clear();
        }

    }*/
	
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

int main(){
    string str= " hola! #1";
    string str2= "heyy";
    Trie tr;
    tr.insert(str);
    tr.insert(str2);
    tr.withPrefix ("h");

   return 0;
}
