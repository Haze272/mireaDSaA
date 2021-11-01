#include <iostream>

using namespace std;

struct Node {
    double info;

    Node *lNode, *rNode;
};
Node *tree;

void push(double a, Node **t) {
    if ((*t) == NULL) {
        (*t) = new Node;
        (*t)->info  = a;
        (*t)->lNode = (*t)->rNode = NULL;
        return;
    }

    if (a > (*t)->info) {
        push(a, &(*t)->rNode);
    } else {
        push(a, &(*t)->lNode);
    }
}

void printTree(Node *t, int u) {
    if (t == NULL) return;

    printTree(t->rNode, ++u);

    for (int i = 0; i < u; ++i) {
        cout << "  ";
    }

    cout << t->info << endl;
    u--;

    printTree(t->lNode, ++u);
}

// TODO average function

// TODO deleteTree function

int main() {
    int n; //Количество элементов
    double s; //Число, передаваемое в дерево
    cout << "Enter the quantity of elements: ";
    cin >> n; //Вводим количество элементов

    for (int i = 0; i < n; ++i) {
        cout << "Enter the number  ";
        cin >> s; //Считываем элемент за элементом

        push(s, &tree); //И каждый кладем в дерево
    }
    cout << "Entire tree\n";
    printTree(tree,0);
}