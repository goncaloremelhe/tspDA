#include <iostream>
#include "Headers/Salesperson.h"
#include <chrono>
#include "Headers/Menu.h"

using namespace std;

int main() {
    Salesperson salesperson;
    cout << "Which graph do you want to use?" << endl;
    cout << "1. Toy Graph" << endl;
    cout << "2. Real World Graphs" << endl;
    cout << "3. Extra fully connected Graphs" << endl;
    char input = '0';
    cin >> input;
    salesperson.readGraph(input);
    Menu menu(&salesperson);

    menu.runAlgorithmChoiceMenu();
    return 0;
}
