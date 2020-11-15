#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;

const int rangeOfChars = 256;

struct RadixNode { 
  string prefix; 
  bool isTerminal;
  vector<unsigned long long> memoryLocations;
  RadixNode * children[rangeOfChars];

  RadixNode (string newPrefix, bool terminal) {
    prefix = newPrefix;
    isTerminal = terminal;
  }
  RadixNode (string newPrefix, bool terminal, unsigned long long memoryLocation) { 
    prefix = newPrefix;
    isTerminal = terminal;
    memoryLocations.push_back(memoryLocation);
  }

  RadixNode * insertAux(string newPrefix, int wordLocation, unsigned long long memoryLocation) { 
    RadixNode * currentNode = this;
    int index = wordLocation;
    string samePrefix = "";
    int i = 0;
    while (i < currentNode -> prefix.size() && index < newPrefix.size()) { 
      if (currentNode -> prefix[i++] != newPrefix[index]) {
        samePrefix.push_back(newPrefix[index]);
        index++;
      }
      else {
        RadixNode * newNode = new RadixNode(samePrefix, false);
        string restOfPrefix = currentNode -> prefix.substr(i); 
        currentNode -> prefix = restOfPrefix;
        string restOfWord = newPrefix.substr(wordLocation + i);
        newNode -> children[(int) restOfWord[0]] = new RadixNode(restOfPrefix, true, memoryLocation);
        newNode -> children[(int) restOfPrefix[0]] = this;
        return newNode;
      }
    }

    if (index == newPrefix.size()) { 
      if (index == this -> prefix.size()) {
        this -> isTerminal = true;
        this -> memoryLocations.push_back(memoryLocation);
        return this;
      }
      else {
        auto newNode = new RadixNode(samePrefix, true);
        this -> prefix = currentNode -> prefix.substr(i);
        newNode -> children[(int) (this -> prefix[0])] = this; 
        newNode -> memoryLocations.push_back(memoryLocation);
        return newNode;
      }
    }

    if (index < newPrefix.size()) { 
      if (!this -> children[(int) newPrefix[index]]) {
        string restOfPrefix = newPrefix.substr(i);
        this -> children[(int) newPrefix[index]] = new RadixNode(restOfPrefix, true, memoryLocation);
      }
      else
        this -> children[(int) newPrefix[index]] = (this -> children[(int) newPrefix[index]]) -> insertAux(newPrefix, index, memoryLocation);
    }
    return this;
  }

  RadixNode * search(string wordToSearch, int wordLocation) { 
    int i, j;
    for(i = wordLocation, j = 0; j < this -> prefix.size() && i < wordToSearch.size(); i++) {
      if (wordToSearch[i] != this -> prefix[j++])
        return nullptr;
    }
    if (j < this -> prefix.size())
      return nullptr;
    if (i >= wordToSearch.size()) {
      if (this -> isTerminal)
        return this;
      else
        return nullptr;
    }
    if (this -> children[(int) wordToSearch[i]])
      return this -> children[(int) wordToSearch[i]] -> search(wordToSearch, i);
    else
      return nullptr;
  }

  void bytesDFS(RadixNode * currentNode, unsigned long long& sumOfBytes) {
    sumOfBytes += sizeof(RadixNode);
    sumOfBytes += sizeof(char) * currentNode -> prefix.size();
    if (currentNode -> isTerminal) {
      sumOfBytes += sizeof(unsigned long long) * memoryLocations.size();
    }
    else {
      for(int i = 0; i < 256; i++) { 
        if (currentNode -> children[i])
          bytesDFS(currentNode -> children[i], sumOfBytes);
      }
    }
  } 

  /* vector<RadixNode *> startsWith(string wordToSearch, int wordLocation) { 
    RadixNode * currentNode = this;
    vector<RadixNode *> allNodes;

    for(i = 0; i < this -> prefix.size() && i < wordToSearch.size(); i++) {
      if (wordToSearch[i] != this -> prefix[i])
        return allNodes;
    }

    if (i < this -> prefix.size())
      dfs(currentNode, allNodes);
      
    if (i >= wordToSearch.size()) {
      if (this -> isTerminal)
        return allNodes;
      else
        return allNodes;
    }

    if (this -> children[(int) wordToSearch[i]])
      return this -> children[(int) wordToSearch[i]] -> startsWith(wordToSearch, i);
    else
      return allNodes;

    dfs(this, allNodes);
    return allNodes;
  }*/

  void dfs(RadixNode * currentNode, vector<RadixNode*>& nodes) {
    if (currentNode -> isTerminal)
      nodes.push_back(currentNode);
    else {
      for(int i = 0; i < 256; i++) { 
        if (currentNode -> children[i])
          dfs(currentNode -> children[i], nodes);
      }
    }
  }

  void print(string fileName) { 
    ifstream data;
    data.open(fileName, ios::binary);
    string dataLine;
    for(int i = 0; i < memoryLocations.size(); i++) {
      data.seekg(memoryLocations[i]);
      getline(data, dataLine);
      cout << dataLine << endl;
    }
  }
};

class RadixTree {
  private:
    RadixNode * root;
    string fileName;
    unsigned long long bytes;
  public:
    RadixTree(string dataFile) {
      fileName = dataFile;
      root = nullptr; 
    }
    void readFromFile() {
      ifstream data;
      data.open(fileName, ios::binary);
      string dataLine;
      unsigned long long memoryPosition = 0;
      while(data.peek() != EOF) { 
        memoryPosition = data.tellg();
        getline(data, dataLine);
        dataLine = obtainFileName(dataLine);
        insert(dataLine, memoryPosition);
      }
    }

    string obtainFileName(string dirtyName) {
      int lastSlash = dirtyName.find_last_of('/');
      int lastPoint = dirtyName.find_last_of('.');
      return dirtyName.substr(lastSlash + 1, lastPoint - lastSlash - 1);
    }

    void insert(string dataPath, unsigned long long memory) {
      if(!root)
        root = new RadixNode(dataPath, true, memory);
      else 
        root = root -> insertAux(dataPath, 0, memory);
      bytes += sizeof(RadixNode);
    }

    RadixNode * search(string wordToSearch) {
      return root -> search(wordToSearch, 0);
    }

    unsigned long long getSize() {
      unsigned long long bytesUsed = 0;
      root -> bytesDFS(root, bytesUsed);
      return bytesUsed;
    }
};

int main() {
  RadixTree testTree("filePaths.txt");
  testTree.readFromFile();

  //TO DO: Change the querues;
  auto start = std::chrono::high_resolution_clock::now ();
  RadixNode *testNode;
  for (int i = 0; i < 100; i++) {
  	testNode = testTree.search("topsecret");
  }
  auto end = std::chrono::high_resolution_clock::now ();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
  cout << "Execution time: " << duration << " us" << endl;
  testNode->print ("filePaths.txt");
  cout << "Size in bytes: " << testTree.getSize() << endl;
}
