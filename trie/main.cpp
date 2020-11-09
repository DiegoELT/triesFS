#include <iostream>
#include <string>

using namespace std;
struct Node{
public:
    Node* next[72]; // 32 al 126
    bool esTerminal;

    Node(){
	esTerminal=false;
    }
};

class Trie{
private:
    Node * root ;
public:
    Trie(){
	root = new Node();
    }
    void insert(std::string str){
	Node**temp = &root;
	for (char& c :str){
	    //cout<< (int)c << endl;
	    int posInArr = (int)c -32 ;
	    temp = &(*temp)->next[posInArr];

	    if( !(*temp) ) {
		*temp  =new Node();
	    }
	}
	(*temp)->esTerminal = true;
    }
    void printTrie(){
	Node* imprimir = root;
        std::string pal;
        for(auto it = imprimir->next.begin(); it != imprimir->next.end(); ++it) {
            pal.push_back(it->first);
            print_helper(pal, it->second);
            pal.clear();
        }

    }


};

int main(){
    string str= " hola! #1";
    string str2= "heyy";
    Trie tr;
    tr.insert(str);
    tr.insert(str2);
    tr.printTrie();

   return 0;
}
