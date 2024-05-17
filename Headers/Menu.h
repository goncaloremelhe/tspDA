#ifndef HEADERS_MENU_H
#define HEADERS_MENU_H

#include "iostream"
#include <iomanip>
#include "../Headers/Salesperson.h"
using namespace std;

class Menu {
private:
    Salesperson *salesperson;

public:
    Menu(Salesperson *s);
    void printAlgorithmChoiceMenu();
    void runAlgorithmChoiceMenu();

    void waitForInput() const;

    void showBacktrackingResults();

    void showOtherHeuristicResults();

    void showTwoApproxResults();
};


#endif //HEADERS_MENU_H
