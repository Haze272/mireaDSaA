#include <iostream>
#include <string>

using namespace std;

struct Node {
    int key;
    char value;

    Node* left = nullptr;
    Node* right = nullptr;

    bool isEmpty() const {
        return key && value;
    }
};

static Node* createNode(int key, char value) {
    Node* node = new Node;
    node->key = key;
    node->value = value;

    return node;
}

class Tree {

public:
    Node* root;

    Tree(string toTree) {
        root = new Node;
    }

    void test() {
        cout << root->isEmpty() << endl;
    }

    void insertTree() {

    }
};

int main() {
    string expression = "((1+2)*(4-3))";

    Tree tree(expression);
    tree.test();
}