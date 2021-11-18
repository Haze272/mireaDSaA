#include <iosteam>

using namespace std;

struct Cell {
    string name = "N/A";
    string article = "N/A";

    struct Cell* nextCell = nullptr;

    bool isEmpty() const {
        return article == "N/A" && name == "N/A";
    }
};

class BinarySearchTree() {

    Cell* root;
public:
    BinarySearchTree() {
        root = new root();
    }

    void insertElem() {
        
    }
    Cell* findElem() {}
    void deleteElem() {}
    void printElem() {}

}

int Main() {
    BinarySearchTree bTree;


    return 0;
}