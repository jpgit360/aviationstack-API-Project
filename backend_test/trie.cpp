#include "trie.h"

/* 
------------------------------------------------------------------
TrieNode Methods
------------------------------------------------------------------
*/

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
std::map<char, TrieNode*>& TrieNode::getChildren() { return children; }

// setters
void TrieNode::setIsEnd(bool val) { isEnd = val; }

/* 
------------------------------------------------------------------
Trie Methods
------------------------------------------------------------------
*/

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
        std::map<char, TrieNode *>::iterator childIt = node->getChildren().find(letter);

        // if letter is not in trie
        if(childIt == node->getChildren().end()) {
            //create node
            TrieNode* newNode = new TrieNode(letter);
            node->getChildren()[letter] = newNode;
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

//finds the node that corresponds to the last letter of partialWord
TrieNode* Trie::searchHelper(std::string partialWord) {
    TrieNode* node = root;
    for (auto it = partialWord.begin(); it != partialWord.end(); it++) {
        char letter = *it;
        std::map<char, TrieNode *>::iterator childIt = node->getChildren().find(letter);
        
        // if letter is not in trie
        if(childIt == node->getChildren().end()) {
            return nullptr;
        }
        else {
            //traverse to next child node
            node = childIt->second;
        }
    }
    return node;
}

//append to autocompleted word list based on partial string
bool Trie::autocomplete(std::string partialWord) {    
    TrieNode* startingNodePtr = searchHelper(partialWord);
    if(startingNodePtr != nullptr) { recursiveTraverse(startingNodePtr, partialWord); }
    else { return false; }
    return true;
}

void Trie::recursiveTraverse(TrieNode* node, std::string currentString) {
    //check if reached end of word
    if(node->getIsEnd()) {
        //append string to vector of autocompleted words
        autocompleteWords.push_back(currentString);
    }

    std::map<char, TrieNode *> childrenMap = node->getChildren();
    
    //loop through children nodes
    for(auto it = childrenMap.begin(); it != childrenMap.end(); it++) {
        TrieNode* child = it->second;
        currentString += child->getData();
        recursiveTraverse(child, currentString);
        currentString.pop_back(); //while going back up trie, pop the corresponding letter
    }
    return;
}

std::vector<std::string> Trie::getAutocompleteWords() { return autocompleteWords; }