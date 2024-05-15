#include <iostream>
#include "Headers/Salesperson.h"
#include <chrono>

using namespace std;

int main() {
    Salesperson salesperson;
    cout << "Which graph do you want to use?" << endl;
    cout << "1. Toy Graph" << endl;
    cout << "2. Real World Graphs" << endl;
    cout << "3. Extra fully connected Graphs" << endl;
    char input = '0';
    cin >> input;

    std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now();
    salesperson.readGraph(input);

    auto end_time = std::chrono::steady_clock::now();
    cout << std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count() << "s\n";
    cout << "Read!\n";
    start_time = std::chrono::steady_clock::now();

    salesperson.completeGraph();

    end_time = std::chrono::steady_clock::now();
    cout << std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count() << "s\n";
    start_time = std::chrono::steady_clock::now();

    double cost = salesperson.otherHeuristicFast();

    end_time = std::chrono::steady_clock::now();
    cout << std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count() << "s\n";

    cout << cost << "\n";
    return 0;
}
