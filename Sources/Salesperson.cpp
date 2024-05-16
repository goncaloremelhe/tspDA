#include "../Headers/Salesperson.h"

void Salesperson::readGraph(char option) {
    switch (option) {
        case '1':
            readToy();
            break;
        case '2':
            readRealWorld();
            break;
        case '3':
            readExtra();
            break;
        default:
            cout << "Invalid option." << endl;
            break;
    }
}

void Salesperson::readToy() {
    cout << "You chose the Toy Graphs!" << endl;
    cout << "Which graph do you want to read?" << endl;
    cout << "1. Shipping" << endl;
    cout << "2. Stadiums" << endl;
    cout << "3. Tourism" << endl;
    char option = '0';
    cin >> option;
    switch (option) {
        case '1':
            readToyCSV("../Toy-graph/shipping.csv", false);
            break;
        case '2':
            readToyCSV("../Toy-graph/stadiums.csv", false);
            break;
        case '3':
            //Nao li os valores label
            readToyCSV("../Toy-graph/tourism.csv", true);
            break;
        default:
            return;
    }
}

void Salesperson::readRealWorld() {
    cout << "You chose the Real World Graphs!" << endl;
    cout << "Which graph do you want to read?" << endl;
    cout << "1st Graph - 1000 nodes (fast)" << endl;
    cout << "2nd Graph - 5000 nodes (very slow)" << endl;
    string option;
    cin >> option;
    if (option < "0" or option > "2") {
        cout << "Invalid number.";
        return;
    }

    readCSV("../Real-world-Graphs/graph" + option + "/nodes.csv", true);
    readCSV("../Real-world-Graphs/graph" + option + "/edges.csv", false);
}

void Salesperson::readExtra() {
    cout << "You chose the Real World Graphs!" << endl;
    cout << "How many nodes do you want to read?" << endl;
    cout << "Options: 25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800 or 900" << endl;
    vector<string> options = {"25", "50", "75", "100", "200", "300", "400", "500", "600", "700", "800", "900"};
    string option;
    cin >> option;
    int lines = stoi(option);
    for (const string& val : options) {
        if (val == option) {
            readExtraCSV("../Extra_Fully_Connected_Graphs/nodes.csv", lines);
            readCSV("../Extra_Fully_Connected_Graphs/edges_" + option + ".csv", false);
            return;
        }
    }
    cout << "Invalid number" << endl;
}


void Salesperson::readToyCSV(const string& path, bool hasName) {
    std::ifstream input(path);

    if (!input.is_open()) {
        cout << "Could not read CSV\n";
        return;
    }

    string line;
    getline(input, line);

    while (getline(input, line)) {
        istringstream iss(line);
        string origem, destino, distancia;
        getline(iss, origem, ',');
        getline(iss, destino, ',');
        getline(iss, distancia, ',');

        int origemINT = stoi(origem);
        int destinoINT = stoi(destino);
        double distanciaDOUBLE = stod(distancia);

        if (salesperson.findVertex(origemINT) == nullptr) {
            salesperson.addVertex(origemINT);
        }

        if (salesperson.findVertex(destinoINT) == nullptr) {
            salesperson.addVertex(destinoINT);
        }

        salesperson.addBidirectionalEdge(origemINT, destinoINT, distanciaDOUBLE);


        if (hasName) {
            string nomeOrigem, nomeDestino;
            getline(iss, nomeOrigem, ',');
            getline(iss, nomeDestino, ',');
            Vertex<int>* vertexOrigem = salesperson.findVertex(origemINT);
            Vertex<int>* vertexDestino = salesperson.findVertex(destinoINT);
            vertexOrigem->setName(nomeOrigem);
            vertexDestino->setName(nomeDestino);
        }

    }
}

void Salesperson::readCSV(const string& path, bool isNode) {
    std::ifstream input(path);

    if (!input.is_open()) {
        cout << "Could not read CSV\n";
        return;
    }

    string line;
    getline(input, line);

    while (getline(input, line)) {
        istringstream iss(line);
        string i1, i2, i3;
        getline(iss, i1, ',');
        getline(iss, i2, ',');
        getline(iss, i3, ',');

        if (isNode) {
            int inti1 = stoi(i1);
            double doublei2 = stod(i2);
            double doublei3 = stod(i3);
            salesperson.addVertex(inti1);
            nodeMap.insert({inti1, make_pair(doublei2, doublei3)});
        } else {
            int inti1 = stoi(i1);
            int inti2 = stoi(i2);
            double doublei3 = stod(i3);
            salesperson.addBidirectionalEdge(inti1, inti2, doublei3);
        }
    }
}

void Salesperson::readExtraCSV(const string& path, int lines) {
    std::ifstream input(path);

    if (!input.is_open()) {
        cout << "Could not read CSV\n";
        return;
    }

    string line;
    getline(input, line);

    while (getline(input, line) && lines > 0) {
        istringstream iss(line);
        string node, latitude, longitude;
        getline(iss, node, ',');
        getline(iss, longitude, ',');
        getline(iss, latitude, ',');
        int intNode = stoi(node);
        double doubleLat = stod(latitude);
        double doubleLon = stod(longitude);
        salesperson.addVertex(intNode);
        nodeMap.insert({intNode, make_pair(doubleLon, doubleLat)});
        lines--;
    }
}


Graph<int> Salesperson::getGraph() {
    return salesperson;
}

void Salesperson::tsp(Vertex<int>* curr, Vertex<int>* start, vector<int>& path, double& pathCost, vector<int>& bestPath, double& bestCost) {
    curr->setVisited(true);
    path.push_back(curr->getInfo());

    if (path.size() == salesperson.getNumVertex()) {
        for (auto e : curr->getAdj()) {
            if (e->getDest() == start) {
                double totalCost = pathCost + e->getWeight();
                if (totalCost < bestCost) {
                    bestPath = path;
                    bestPath.push_back(start->getInfo());
                    bestCost = totalCost;
                }
                break;
            }
        }
    } else {
        for (auto e : curr->getAdj()) {
            Vertex<int>* next = e->getDest();
            if (!next->isVisited()) {
                pathCost += e->getWeight();
                tsp(next, start, path, pathCost, bestPath, bestCost);
                pathCost -= e->getWeight();
            }
        }
    }

    path.pop_back();
    curr->setVisited(false);
}

pair<vector<int>, double> Salesperson::tspBacktracking(Vertex<int>* startVertex, long& timeTaken) {

    auto time_start = chrono::high_resolution_clock::now();

    double currentCost = 0,bestCost = numeric_limits<double>::infinity();
    vector<int> currentPath, bestPath;

    tsp(startVertex, startVertex, currentPath, currentCost, bestPath, bestCost);


    auto time_stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time_stop - time_start);

    timeTaken = duration.count();

    return {bestPath,bestCost};
}
