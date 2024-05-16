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
    cout    << "3. Other heuristic"<< endl;
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
                //run triangular approx.
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

void Menu::showOtherHeuristicResults() {
    bool toConnect = false;
    for (auto v : salesperson->getGraph().getVertexSet()) {
        if (v->getAdj().size() != salesperson->getGraph().getVertexSet().size() - 1) {
            cout << endl << "This graph is not fully connected!" << endl;
            cout << "Do you want to make it connected? (y/n)" << endl;
            string input;
            cin >> input;
            if (input == "y") {
                toConnect = true;
            }
            break;
        }
    }

    if (toConnect) {
        cout << "Completing the graph..." << endl;
        salesperson->completeGraph();
        cout << "Complete!" << endl << endl;
    }

    double timeTaken;
    double cost = salesperson->otherHeuristicFast(0, timeTaken);
    cout << "Cost: " << cost << endl;
    cout << "Path: ";

    Vertex<int>* vertex = salesperson->getGraph().findVertex(0);
    cout << "Time taken: " <<  timeTaken << " seconds" << endl;

    if (salesperson->getGraph().getNumVertex() >= 100) {
        cout << endl << "Do you want to see the path? (y/n)" << endl;
        cout << "There are " << salesperson->getGraph().getNumVertex() << " nodes!" << endl;
        string input;
        cin >> input;

        if (input != "y") {
            return;
        }
    }

    for (int i = 0; i <= salesperson->getGraph().getNumVertex(); i++) {
        cout << vertex->getInfo();
        vertex = vertex->getPath()->getDest();
        if(i == salesperson->getGraph().getNumVertex()){
            cout << endl;
        }
        else{
            cout << " -> ";
        }
    }
}
