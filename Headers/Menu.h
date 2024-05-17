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
    /**
     * Menu constructor
     * @param s
     */
    Menu(Salesperson *s);
    /**
     * Prints the menu to choose an algorithm
     */
    void printAlgorithmChoiceMenu();
    /**
     * Parses user inputs in the menu and prints results
     */
    void runAlgorithmChoiceMenu();
    /**
     * Waits for user input in order to show results
     */
    void waitForInput() const;
    /**
     * Shows the results after running the backtracking algorithm
     * @details Time complexity:O(V!) + O(V+1), V being the number of vertices in the graph
     */
    void showBacktrackingResults();

    void showOtherHeuristicResults();
};


#endif //HEADERS_MENU_H
