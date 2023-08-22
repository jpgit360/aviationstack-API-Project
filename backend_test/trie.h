#ifndef TRIE_GUARD
#define TRIE_GUARD

#include <iostream>
#include <vector>
#include <map>

class TrieNode {
public:
    TrieNode(char letter);
    ~TrieNode();
    char getData();
    bool getIsEnd();
    void setIsEnd(bool val);
    std::map<char, TrieNode*>& getChildren();
private:
    std::map<char, TrieNode*> children;
    char data;
    bool isEnd;
    
};

class Trie {
public:
    Trie();
    ~Trie();
    bool insert(std::string word);
    TrieNode* searchHelper(std::string partialWord);
    bool autocomplete(std::string partialWord);
    void recursiveTraverse(TrieNode* node, std::string word="");
    std::vector<std::string> getAutocompleteWords();
private:
    TrieNode* root;
    std::vector<std::string> autocompleteWords;
};

#endif