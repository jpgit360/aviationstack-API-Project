#include "trie.h"

TrieNode::TrieNode(char letter) {
    data = letter;
    isEnd = false;
}

TrieNode::~TrieNode() {
    //recursively delete children dfs
    std::map<char, TrieNode*>::iterator it;
    for(it = children.begin(); it != children.end(); ++it) {
        delete it->second;
    }
}

// getters
char TrieNode::getData() { return data; }
bool TrieNode::getIsEnd() { return isEnd; }
std::map<char, TrieNode*> TrieNode::getChildren() { return children; }

// setters
void TrieNode::setIsEnd(bool val) { isEnd = val; }


Trie::Trie() {
    root = new TrieNode(' ');
}

Trie::~Trie() {
    delete root;
}

bool Trie::insert(std::string word) {
    TrieNode* node = root;
    for (auto it = word.begin(); it != word.end(); it++) {
        char letter = *it;
        std::map<char, TrieNode *>::iterator childIt = node->children.find(letter);

        // if letter is not in trie
        if(childIt == node->children.end()) {
            //create node
            TrieNode* newNode = new TrieNode(letter);
            node->children[letter] = newNode;
            node = newNode;
        }
        else {
            //traverse to next child node
            node = childIt->second;
        }
    }
    node->setIsEnd(true);
    return true;
}

bool Trie::search(std::string word) {
    return true;
}