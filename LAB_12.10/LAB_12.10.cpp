#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Structure representing a tree node
struct TreeNode {
    string word;
    int count;
    vector<TreeNode*> children;

    TreeNode(string w, int c) : word(w), count(c) {}
};

// Function to compare nodes based on their counts
bool compareNodes(const TreeNode* a, const TreeNode* b) {
    return a->count > b->count;
}

// Function to print the tree as nested lists
void printTree(TreeNode* root, int level, ostream& out) {
    if (!root) return;

    for (int i = 0; i < level; ++i) {
        out << "  ";
    }
    out << root->word << " (" << root->count << ")" << endl;

    for (TreeNode* child : root->children) {
        printTree(child, level + 1, out);
    }
}

map<string, int> countWords(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open the file!" << endl;
        return {};
    }

    map<string, int> wordCount;
    string word;
    while (file >> word) {
        ++wordCount[word];
    }
    file.close();

    return wordCount;
}

int main() {
    string filePath;
    cout << "Enter the path to the text file: ";
    getline(cin, filePath);

    map<string, int> wordCount = countWords(filePath);
    if (wordCount.empty()) {
        return 1;
    }

    set<TreeNode*, decltype(compareNodes)*> nodes(compareNodes);
    for (const auto& pair : wordCount) {
        TreeNode* node = new TreeNode(pair.first, pair.second);
        nodes.insert(node);
    }

    TreeNode* root = nullptr;
    for (auto node : nodes) {
        if (!root) {
            root = node;
        }
        else {
            root->children.push_back(node);
        }
    }

    cout << "Word Tree:" << endl;
    printTree(root, 0, cout);

    cout << endl << "Count of each word:" << endl;
    for (const auto& pair : wordCount) {
        cout << pair.first << ": " << pair.second << endl;
    }

    for (auto node : nodes) {
        delete node;
    }

    return 0;
}
