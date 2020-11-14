#include <iostream>
#include <string>
#include "Trie.h"
using namespace std;

int main(){
    string str= " hola! #1";
    string str2= "heyy";
    Trie tr;
    tr.insert(str);
    tr.insert(str2);
    tr.withPrefix ("h");

   return 0;
}
