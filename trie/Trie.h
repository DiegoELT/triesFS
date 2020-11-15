#include "Node.h"
#include <sys/stat.h>
#include <fstream>
using namespace std;
class Trie{
public:
    Node * root;
    unsigned long long bytes;

    Trie(){
	root = new Node();
	bytes = 0;
    }
    void insert(std::string str, int start, int offset){
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
	(*temp)->addPath (std::make_pair (start, offset));
    }


    void dfs (Node **temp, std::string word) {
	if ((*temp)->esTerminal) {
	    std::unordered_map<int, std::vector<std::string>> sizes;
	    //std::cout << word<<"esta presente: " << std::endl;
	    for (int i = 0; i < (*temp)->getPaths ().size (); i++) {
		std::ifstream pathfile ("filePaths.txt");
		char location [255];
		pathfile.seekg ((*temp)->getPaths ()[i].first);
		pathfile.read (location, (*temp)->getPaths ()[i].second);
		struct stat buf;
		stat (location, &buf);
		sizes.insert(std::make_pair (buf.st_size, std::vector<std::string>()));
		sizes[buf.st_size].push_back (location);
	    }
	    for (auto it = sizes.begin (); it != sizes.end (); it++) {
		//std::cout << "with size: " << it->first << " at ";
		for (int i = 0; i < it->second.size (); i++) {
		//	std::cout << it->second[i] << " | ";
		}
		//std::cout << std::endl;
	    }
	}
	bytes += sizeof(Node) + (2 * sizeof (int)) * (*temp)->paths.size ();
	auto nodo = temp;
	std::string palabra = word;

	for (int i = 0; i < 94; i++) {
		if ((*nodo)->next[i]) {
			word += (char) (i + 32);
			dfs (&(*nodo)->next[i], word);
			word = palabra;
		}
	}
    }

    void consulta (std::string prefix) {
	    Node **temp = &root;
	    int pos;
	    for (int i = 0; i < prefix.size (); i++) {
		    pos = ((int) prefix[i]) - 32;
		    if ((*temp)->next[pos])
			    temp = &(*temp)->next[pos];
		    else
			    return;
	    }
	    dfs (temp, prefix);
    }
    int getBytes () {
	return bytes;
    }


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
		//cout<<name<<endl;
		insert (name, start, line.size ());
		name.clear ();
		start = indexFile.tellg ();
	    }
    }
	
	void sumBytes () {
		bytes = 0; 
		dfs (&root, "");
	}
};
