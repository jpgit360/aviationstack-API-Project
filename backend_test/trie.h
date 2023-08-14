#ifndef TRIE_GUARD
#define TRIE_GUARD

#include <iostream>
#include <map>

class TrieNode {
public:
    TrieNode(char letter);
    ~TrieNode();
    char getData();
    bool getIsEnd();
    void setIsEnd(bool val);
    std::map<char, TrieNode*> children;
    std::map<char, TrieNode*> getChildren();
private:
    char data;
    bool isEnd;
    
};

class Trie {
public:
    Trie();
    ~Trie();
    bool insert(std::string word);
    bool search(std::string word);
private:
    TrieNode* root;
};

#endif