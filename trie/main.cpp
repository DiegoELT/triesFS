#include <iostream>
#include <string>
#include <chrono>
#include "Trie.h"
using namespace std;

int main(){

    std::cout << " INSERTA TRIE " << std::endl;
    Trie trie;
    trie.index("filePaths.txt");
    /*
    auto start = std::chrono::high_resolution_clock::now ();
    for (int i = 0; i < 10; i++) {
	    trie.consulta("Con");
	    trie.consulta("Emergency");
	    trie.consulta("jasper");
	    trie.consulta("CS");
	    trie.consulta("Software");
	    trie.consulta("EDA");
	    trie.consulta("Initial");
	    trie.consulta("classified");
	    trie.consulta("standard");
	    trie.consulta("s");
    }
    auto end = std::chrono::high_resolution_clock::now ();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
    std::cout << "duration: " << duration << "us" << std::endl;
*/
    std::cout << " BUSCA TRIE " << std::endl;
    cout<<"Visuazilar archivos con conjunto de letras: ";
    std::string var;
    cin>>var ;
    trie.consulta(var);

    std::cout << "Size in bytes: " << trie.getBytes () << std::endl;
    return 0;
}
