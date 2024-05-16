#include "../Headers/Menu.h"

Menu::Menu(Salesperson *s) {
    salesperson = s;
}

void Menu::waitForInput() const {
    cout << "Input any value to continue" << endl;
    string input;
    getline(cin >> input, input);
}


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
                showBacktrackingResults();
                waitForInput();
                break;
            case 2:
                //run triangular approx.
                break;
            case 4:
                cout << "Goodbye ! (˶ᵔ ᵕ ᵔ˶)"<< endl;
                return;
            default:
                cout << "Invalid Input" << endl;

        }
    }

}

void Menu::showBacktrackingResults(){
    double timeTaken;
    pair<vector <int>,double> results = salesperson->tspBacktracking(salesperson->getGraph().getVertexSet()[0],timeTaken);
    cout << "Best Cost: ";
    cout << results.second << endl;
    cout << "Best Path: ";
    for (int i =0; i< results.first.size(); i++) {
        cout << results.first[i];
        if(i == results.first.size()-1){
            cout << endl;
        }
        else{
            cout << " -> ";
        }
    }
    cout << "Time taken: " <<  timeTaken << " seconds" << endl;
}
