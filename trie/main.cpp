#include <iostream>
#include <string>
#include "Trie.h"
using namespace std;

int main(){
    string str= "hola";
    string str2= "hey";
    string str3= "holambre";
    string str4= "halo";
    string str6= "hombre";
    string str5= "holii";
    Trie tr;
    tr.insert(str);
    tr.insert(str2);
    tr.insert(str3);
    tr.insert(str4);
    tr.insert(str5);
    tr.insert(str6);
    tr.withPrefix ("ho");

   return 0;
}
