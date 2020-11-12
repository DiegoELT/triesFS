#include <bits/stdc++.h>

using namespace std;

struct RadixNode { 
  string currentPrefix;
  bool isTerminal;
  vector<unsigned long long> memoryLocation; 
  unordered_map<string, RadixNode*> children;
};

int main(){
  return 0;
}