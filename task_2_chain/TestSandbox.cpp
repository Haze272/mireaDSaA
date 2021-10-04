#include <iostream>
#include <string>

using namespace std;

struct Cell
{
    string name = "N/A";
    string article = "N/A";

    struct Cell* nextCell;

    bool isEmpty() const {
        return article == "N/A" && name == "N/A";
    }
};

