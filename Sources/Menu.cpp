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
    cout    << "3. Other heuristic (Nearest neighbour)"<< endl;
    cout    << "4. TSP in the real world"<< endl;
    cout    << "5. Exit" << endl;
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
                showTwoApproxResults();
                waitForInput();
                break;
            case 3:
                showOtherHeuristicResults();
                waitForInput();
                break;
            case 4:
                //run tsp in real world
                break;
            case 5:
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
    cout << "Best Cost: " << results.second << endl;
    cout << "Time taken: " <<  timeTaken << " seconds" << endl;
}

void Menu::showOtherHeuristicResults() {
    double time;
    pair<vector<int>, double> result = salesperson->nearestNeighbour(time);

    if (result.second == -1) {
        cout << "This graph cannot be completed!" << endl;
        return;
    }

    cout << result.second << endl;
    cout << "Path: ";
    for (int i = 0; i < result.first.size(); i++) {
        cout << result.first[i];
        if(i == result.first.size() - 1){
            cout << endl;
        }
        else{
            cout << " -> ";
        }
    }
    cout << "Cost: " << result.second << "\n";
    cout << "Time taken: " << time << " seconds" << endl;
}

void Menu::showTwoApproxResults() {
    double time;

    pair<vector<Vertex<int>*>, double> result = salesperson->twoApprox(time);

    if (result.second == -1) {
        cout << "This graph cannot be completed!" << endl;
        return;
    }

    cout << "Path: ";
    for (int i = 0; i < result.first.size(); i++) {
        cout << result.first[i]->getInfo();
        if(i == result.first.size() - 1){
            cout << endl;
        }
        else{
            cout << " -> ";
        }
    }
    cout << "Cost: " << result.second << endl;
    cout << "Time taken: " << time << " seconds" << endl;
}
