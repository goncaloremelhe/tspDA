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

double Salesperson::haversineDistance(double latA, double lonA, double latB, double lonB) {
    latA = (latA) * M_PI / 180.0;
    latB = (latB) * M_PI / 180.0;

    lonA = (lonA) * M_PI / 180.0;
    lonB = (lonB) * M_PI / 180.0;

    double vlat = latB - latA;
    double vlon = lonB - lonA;

    double a = pow(sin(vlat / 2), 2) + pow(sin(vlon / 2), 2) * cos(latA) * cos(latB);
    double rad = 6365000;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void Salesperson::completeGraph() {
    int size = salesperson.getNumVertex();
    for (auto v : salesperson.getVertexSet()) {
        if (v->getAdj().size() != size - 1) {
            bool hasEdge[size];
            for (int i = 0; i < size; i++) {
                hasEdge[i] = false;
            }
            hasEdge[v->getInfo()] = true;
            for (auto edge : v->getAdj()) {
                hasEdge[edge->getDest()->getInfo()] = true;
            }
            for (int i = 0; i < size; i++) {
                if (!hasEdge[i]) {
                    nodeMap[v->getInfo()].first;
                    double latA = nodeMap[v->getInfo()].second, lonA = nodeMap[v->getInfo()].first;
                    double latB = nodeMap[i].second, lonB = nodeMap[i].first;
                    double cost = haversineDistance(latA, lonA, latB, lonB);
                    salesperson.addBidirectionalEdge(v->getInfo(), i, cost);
                }
            }
        }
    }
}

double Salesperson::otherHeuristicFast() {
    double cost = 0.0;
    for (auto v : salesperson.getVertexSet()) {
        v->setPath(NULL);
        v->setVisited(false);
    }
    Vertex<int>* vertex = salesperson.findVertex(0);
    vertex->setVisited(true);
    for (int i = 0; i < salesperson.getNumVertex(); i++) {
        Edge<int>* nearestNeighbour = nullptr;
        double nearestDistance = INF;
        for (auto edge : vertex->getAdj()) {
            if (!edge->getDest()->isVisited() and edge->getWeight() < nearestDistance) {
                nearestDistance = edge->getWeight();
                nearestNeighbour = edge;
            }

            if (i == salesperson.getNumVertex() - 1 && edge->getDest()->getInfo() == 0) {
                nearestDistance = edge->getWeight();
                nearestNeighbour = edge;
            }
        }

        vertex->setPath(nearestNeighbour);
        vertex = nearestNeighbour->getDest();
        vertex->setVisited(true);
        cost += nearestDistance;
    }

    return cost;
}
