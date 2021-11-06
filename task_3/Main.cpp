#include <iostream>

using namespace std;

struct Node {
    double info;

    Node *lNode, *rNode;
};

class BinaryTree {

public:
    Node *tree;

    void push(double a, Node **curr) {
        if (*curr == NULL) {
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

    double average(Node *t) {
        double sum = sumElem(t);
        int quantity = getQuantity(t);
        return sum / quantity;
    }

    void treeClear(Node *t) {
        if(t != nullptr){
            if(t->lNode != nullptr)
                treeClear(t->lNode);
            if(t->rNode != nullptr)
                treeClear(t->rNode);
            delete t;
        }
    }

private:

    double sumElem(Node *t) {
        int l, r;
        if(t != nullptr){
            l = (t->lNode  != nullptr) ? sumElem(t->lNode)  : 0;
            r = (t->rNode != nullptr) ? sumElem(t->rNode) : 0;
            return l + r + t->info;
        }
        return 0;
    }

    int getQuantity(Node *t) {
        if (t->lNode == NULL && t->rNode == NULL)
            return 1;

        int left, right;

        if (t->lNode != NULL)
            left = getQuantity(t->lNode);
        else
            left = 0;

        if (t->rNode != NULL)
            right = getQuantity(t->rNode);
        else
            right = 0;

        return left + right + 1;
    }
};

int main() {
    int n; //Количество элементов
    double s; //Число, передаваемое в дерево


    cout << "Enter the quantity of elements: ";
    cin >> n; //Вводим количество элементов
    BinaryTree bt;

    for (int i = 0; i < n; ++i) {
        cout << "Enter the number  ";
        cin >> s; //Считываем элемент за элементом

        bt.push(s, &bt.tree); //И каждый кладем в дерево
    }

    cout << "Entire tree\n";
    bt.printTree(bt.tree, 0);

    cout << "Entire average of left subtree\n";
    cout << bt.average(bt.tree->lNode) << endl;

    cout << "Entire average of right subtree\n";
    cout << bt.average(bt.tree->rNode) << endl;

    bt.treeClear(bt.tree);

    cout << "Entire tree\n";
    cout << bt.tree->info;
}