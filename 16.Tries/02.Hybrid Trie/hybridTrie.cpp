#include<bits/stdc++.h>
using namespace std;

const int MAX_SUFFIXES = 50; // Maximum number of suffixes in a leaf node

class HybridTrieNode {
public:
    unordered_map<char, HybridTrieNode*> children;
    vector<pair<string, int>> suffixes; // Store suffixes and associated values
    bool isLeaf;

    HybridTrieNode() : isLeaf(true) {}
};

class HybridTrie {
private:
    HybridTrieNode* root;

    void splitLeafNode(HybridTrieNode* node) {
        unordered_map<char, HybridTrieNode*> newChildren;
        
        // Distribute suffixes to new child nodes
        for (const auto& suffix_pair : node->suffixes) {
            char firstLetter = suffix_pair.first[0];
            if (newChildren.find(firstLetter) == newChildren.end()) {
                newChildren[firstLetter] = new HybridTrieNode();
            }
            newChildren[firstLetter]->suffixes.emplace_back(suffix_pair.first.substr(1), suffix_pair.second);
        }

        // Update the current node
        node->children = newChildren;
        node->suffixes.clear();
        node->isLeaf = false;
    }

public:
    HybridTrie() {
        root = new HybridTrieNode();
    }

    void insert(const string& key, int value) {
        HybridTrieNode* node = root;

        for (char ch : key) {
            if (node->isLeaf) {
                if (node->suffixes.size() < MAX_SUFFIXES) {
                    node->suffixes.emplace_back(key.substr(key.find(ch)), value);
                    return;
                } else {
                    // Node has reached the maximum suffixes, transform it into a regular trie node
                    splitLeafNode(node);
                }
            }

            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new HybridTrieNode();
            }
            node = node->children[ch];
        }
    }

    bool search(const string& key, int& value) {
        HybridTrieNode* node = root;

        for (char ch : key) {
            if (node->isLeaf) {
                for (const auto& suffix_pair : node->suffixes) {
                    if (suffix_pair.first == key.substr(key.find(ch))) {
                        value = suffix_pair.second;
                        return true;
                    }
                }
                return false;
            }

            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }

        return false;
    }

    bool startsWith(const string& prefix) {
        HybridTrieNode* node = root;

        for (char ch : prefix) {
            if (node->isLeaf) {
                for (const auto& suffix_pair : node->suffixes) {
                    if (suffix_pair.first.find(prefix.substr(prefix.find(ch))) == 0) {
                        return true;
                    }
                }
                return false;
            }

            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }

        return true;
    }
};

int main() {
    HybridTrie trie;
    trie.insert("apple", 100);
    trie.insert("app", 50);
    trie.insert("banana", 200);
    trie.insert("band", 150);
    trie.insert("bandana", 250);

    int value;

    if (trie.search("apple", value)) {
        cout << "Found 'apple' with value: " << value << endl;
    } else {
        cout << "'apple' not found" << endl;
    }

    if (trie.startsWith("ban")) {
        cout << "There is a word that starts with 'ban'" << endl;
    } else {
        cout << "No word starts with 'ban'" << endl;
    }

    return 0;
}
