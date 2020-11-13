#include <bits/stdc++.h>

using namespace std;

struct RadixNode { 
  string currentPrefix;
  bool isTerminal;
  vector<unsigned long long> memoryLocation; 
  unordered_map<string, RadixNode*> children;

  RadixNode() {
    this -> isTerminal = false; 
  }
};

struct RadixTree {
  RadixNode * rootNode;
  int size;
  string fileSystem;

  RadixTree(string fileName) { 
    this -> fileSystem = fileName;
    this -> size = 0;
  }
  
  void firstInsert(unsigned long long memory, string rootPrefix) { 
    RadixNode * firstRoot = new RadixNode();
    firstRoot -> currentPrefix = rootPrefix; 
    firstRoot -> isTerminal = true;
    firstRoot -> memoryLocation.push_back(memory);
    rootNode = firstRoot;
  }

  void insertString(unsigned long long memory) {
    string newPrefix = obtainFileName(memory);
    if (!size) 
      this -> firstInsert(memory, newPrefix);
    else {
      RadixNode * currentNode = rootNode;
      int i = 0;
      for (; i < newPrefix.size() && i < currentNode -> currentPrefix.size(); i++) {
        if (newPrefix[i] != currentNode -> currentPrefix[i]) 
          break;
      }
      if (i < newPrefix.size() && i < currentNode -> currentPrefix.size()) { // First case, there's a difference withing the nodes.
        RadixNode * newRoot = new RadixNode();
        RadixNode * newSon = new RadixNode();
        newRoot -> currentPrefix = newPrefix.substr(0, i);
        newSon -> currentPrefix = newPrefix.substr(i);
        currentNode -> currentPrefix = currentNode -> currentPrefix.substr(i);
        // cout << newRoot -> currentPrefix << endl << newSon -> currentPrefix << endl << currentNode -> currentPrefix;
        newRoot -> children[currentNode -> currentPrefix] = currentNode;
        this -> rootNode = newRoot;
      }
      else { 
        if (i == newPrefix.size() && i < currentNode -> currentPrefix.size()) { // Second case, the new string is a prefix of the current one.
          
        }
        else { // Third case, recursive, so far, the prefixes are the same, but there is part of the string left to process

        }
      }
    }
    size++;
  }

  string obtainFileName(unsigned long long memory) {
    ifstream dataSet;
    dataSet.open(fileSystem, ios::binary);
    dataSet.seekg(memory);
    string pathToFile;
    getline(dataSet, pathToFile);
    int lastSlash = pathToFile.find_last_of('/');
    int lastPoint = pathToFile.find_last_of('.');
    return pathToFile.substr(lastSlash + 1, lastPoint - lastSlash - 1);
  }

  ~RadixTree() {
    delete rootNode;
  }
};

int main(){
  RadixTree testingTree("allPdfDataset.txt");
  testingTree.insertString(0);
  testingTree.insertString(71);
  cout << testingTree.rootNode -> children["ngo_18_Users_Manual"] -> currentPrefix;
}