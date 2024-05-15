#include <iostream>
#include "Headers/Salesperson.h"
#include "Headers/Menu.h"

using namespace std;

int main() {
    Salesperson salesperson;
    Menu menu;
    cout << "Which graph do you want to use?" << endl;
    cout << "1. Toy Graph" << endl;
    cout << "2. Real World Graphs" << endl;
    cout << "3. Extra fully connected Graphs" << endl;
    char input = '0';
    cin >> input;
    salesperson.readGraph(input);
    menu.runAlgorithmChoiceMenu();
    return 0;
}
