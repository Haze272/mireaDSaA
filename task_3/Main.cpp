#include <iostream>

using namespace std;

struct Node {
    double info;

    Node *lNode, *rNode;
};

class BinaryTree {
    double summary;
    int qElem;

public:
    Node *tree;

    BinaryTree() {
        tree = NULL;
        qElem = 0;
    }

    void push(double a, Node **curr) {
        if (*curr == NULL) {
            qElem++;
            (*curr) = new Node;
            (*curr)->info  = a;
            (*curr)->lNode = (*curr)->rNode = NULL;
            return;
        }

        if (a > (*curr)->info) {
            push(a, &(*curr)->rNode);
        } else {
            push(a, &(*curr)->lNode);
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

    double average() {
        sumTree(tree, 0);
        return summary/(double)qElem;
    }

private:
    void sumTree(Node *t, int u) {
        if (t == NULL) return;

        sumTree(t->rNode, ++u);

        summary += t->info;
        u--;

        sumTree(t->lNode, ++u);
    }
};

// TODO deleteTree function

int main() {
    int n; //Количество элементов
    double s; //Число, передаваемое в дерево
    BinaryTree bt;

    cout << "Enter the quantity of elements: ";
    cin >> n; //Вводим количество элементов\

    for (int i = 0; i < n; ++i) {
        cout << "Enter the number  ";
        cin >> s; //Считываем элемент за элементом

        bt.push(s, &bt.tree); //И каждый кладем в дерево
    }

    cout << "Entire tree\n";
    bt.printTree(bt.tree, 0);

    cout << "Entire average\n";
    cout << bt.average();
}