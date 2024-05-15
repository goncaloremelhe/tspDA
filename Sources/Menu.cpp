#include "../Headers/Menu.h"


void Menu::printAlgorithmChoiceMenu() {
    cout << endl;
    cout    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout    << "      Travelling Salesperson Problem    " << endl;
    cout    << "               Main Menu                " << endl;
    cout    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout    << endl;
    cout    << "Which algorithm would you like to run?" << endl;
    cout    << "1. Backtracking algorithm"<< endl;
    cout    << "2. Triangular approximation algorithm"<< endl;
    cout    << "4. Exit" << endl;
}

void Menu::runAlgorithmChoiceMenu(){
    while(true){
        system("clear");
        printAlgorithmChoiceMenu();

        int option;
        cin >> option;

        switch(option){
            case 1:
                //run backtracking algo
                return;
            case 2:
                //run triangular approx.
                return;
            case 4:
                cout << "Goodbye ! (˶ᵔ ᵕ ᵔ˶)"<< endl;
                return;
            default:
                cout << "Invalid Input" << endl;

        }
    }

}