#include <stack>
#include <algorithm>
#include "../Headers/Salesperson.h"
#include "../Headers/MutablePriorityQueue.h"

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
    if (option < "0" or option > "3") {
        cout << "Invalid number.";
        return;
    }

    readCSV("../Real-world-Graphs/graph" + option + "/nodes.csv", true);
    readCSV("../Real-world-Graphs/graph" + option + "/edges.csv", false);
}

void Salesperson::readExtra() {
    cout << "You chose the Extra Graphs!" << endl;
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

    for (auto v : salesperson.getVertexSet()) {
        vector<double> distRow;
        for (int j = 0; j < salesperson.getNumVertex(); j++) {
            distRow.push_back(-1);
        }
        for (auto e : v->getAdj()) {
            distRow[e->getDest()->getInfo()] = e->getWeight();
        }
        distMap.push_back(distRow);
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

    if (!isNode) {
        for (auto v : salesperson.getVertexSet()) {
            vector<double> distRow;
            for (int j = 0; j < salesperson.getNumVertex(); j++) {
                distRow.push_back(-1);
            }
            for (auto e : v->getAdj()) {
                distRow[e->getDest()->getInfo()] = e->getWeight();
            }
            distMap.push_back(distRow);
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

void Salesperson::primMst(Vertex<int>* root) {

    //graph cleanup
    for (Vertex<int> *v : salesperson.getVertexSet()) {
        v->setVisited(false);
        v->setDist(INF);
        v->setPath(nullptr);
    }

    root->setDist(0);

    MutablePriorityQueue<Vertex<int>> q;
    q.insert(root);

    while (!q.empty()) {

        Vertex<int> *v = q.extractMin();
        v->setVisited(true);

        for (Edge<int> *&e: v->getAdj()) {
            Vertex<int> *dest = e->getDest();

            if (!dest->isVisited()) {

                double oldDist = dest->getDist();

                if (e->getWeight() < oldDist) {
                    dest->setDist(e->getWeight());
                    dest->setPath(e);

                    if (oldDist == INF) {
                        q.insert(dest);
                    } else {
                        q.decreaseKey(dest);
                    }
                }
            }
        }
    }

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

pair<vector<Vertex<int>*>, double> Salesperson::twoApprox(double& time) {

    std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now();

    double cost = 0;

    //start on 0 identifier node
    Vertex<int>* root = salesperson.findVertex(0);

    primMst(root);

    vector<Vertex<int>*> tour;
    mstDfs(tour, root);  //runs dfs through mst
    tour.push_back(root);   //complete tour

    Vertex<int>* currV;
    Vertex<int>* nextV;
    bool foundEdge;
    pair<double, double> currCoords;
    pair<double, double> nextCoords;
    for (int i = 0; i < salesperson.getNumVertex(); i++) {
        currV = tour[i];
        nextV = tour[i+1];
        foundEdge = false;

        for (Edge<int>* e : currV->getAdj()) {
            if (e->getDest()->getInfo() == nextV->getInfo()) {
                cost += e->getWeight();
                foundEdge = true;
                break;
            }
        }
        if (!foundEdge) {
            if (nodeMap.find(currV->getInfo()) == nodeMap.end() || nodeMap.find(nextV->getInfo()) == nodeMap.end()) {
                return {tour, -1};
            }
            currCoords = nodeMap.at(currV->getInfo());
            nextCoords = nodeMap.at(nextV->getInfo());
            cost += haversineDistance(currCoords.second, currCoords.first, nextCoords.second, nextCoords.first);
        }

    }

    auto end_time = std::chrono::steady_clock::now();

    time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();

    return {tour, cost};
}

void Salesperson::mstDfs(vector<Vertex<int>*>& res, Vertex<int>* source) {

    for (Vertex<int>* v : salesperson.getVertexSet()) {
        v->setVisited(false);
    }

    mstDfsVisit(source, res);
}

void Salesperson::mstDfsVisit(Vertex<int>* v, vector<Vertex<int>*>& res) {

    v->setVisited(true);
    res.push_back(v);

    if (res.size() == salesperson.getNumVertex()) return;

    for (Edge<int>*& e : v->getAdj()) {
        Vertex<int>* dest = e->getDest();
        if (dest->getPath() == nullptr) continue;
        if (dest->getPath()->getOrig()->getInfo() == v->getInfo() && !dest->isVisited()) {
            mstDfsVisit(dest, res);
        }
    }
}

void Salesperson::tspWork(Vertex<int>* curr, Vertex<int>* start, vector<int>& path, double& pathCost, vector<int>& bestPath, double& bestCost) {
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
                tspWork(next, start, path, pathCost, bestPath, bestCost);
                pathCost -= e->getWeight();
            }
        }
    }

    path.pop_back();
    curr->setVisited(false);
}

pair<vector<int>, double> Salesperson::tspBacktracking(Vertex<int>* startVertex, double& timeTaken) {

    std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now();

    double currentCost = 0, bestCost = numeric_limits<double>::infinity();

    vector<int> currentPath, bestPath;

    for (auto vertex: salesperson.getVertexSet()) {
        vertex->setVisited(false);
    }

    tspWork(startVertex, startVertex, currentPath, currentCost, bestPath, bestCost);


    auto end_time = std::chrono::steady_clock::now();

    timeTaken = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();

    return {bestPath, bestCost};
}


pair<vector<int>,double> Salesperson::nearestNeighbour(double &timeTaken) {
    std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now();

    for (auto v : salesperson.getVertexSet()) {
        v->setVisited(false);
    }

    vector<int> path;
    double cost = 0;
    Vertex<int>* origin = salesperson.findVertex(0);
    path.push_back(0);
    double costTemp = 0;
    for (int i = 0; i < salesperson.getNumVertex() - 1; i++) {
        costTemp = cost;
        origin->setVisited(true);
        double nearestCost = INF;
        Vertex<int>* nearestNeighbour = nullptr;
        for (auto v : salesperson.getVertexSet()) {
            double vertexCost;
            if (v == origin) {continue;}
            if (!v->isVisited()) {
                if (distMap[origin->getInfo()][v->getInfo()] >= 0) {
                    vertexCost = distMap[origin->getInfo()][v->getInfo()];
                } else {
                    double latA = nodeMap[origin->getInfo()].second, lonA = nodeMap[origin->getInfo()].first;
                    double latB = nodeMap[v->getInfo()].second, lonB = nodeMap[v->getInfo()].first;
                    vertexCost = haversineDistance(latA, lonA, latB, lonB);
                }

                if (vertexCost < nearestCost) {
                    nearestCost = vertexCost;
                    nearestNeighbour = v;
                }
            }
        }

        if (nearestNeighbour == nullptr) {
            cout << "caught nullptr!\n";
            return {vector<int>(), -1};
        }

        origin = nearestNeighbour;
        cost += nearestCost;
        path.push_back(origin->getInfo());
    }

    if (distMap[path.back()][0] > 0) {
        cost += distMap[path.back()][0];
    } else {
        double latA = nodeMap[0].second, lonA = nodeMap[0].first;
        double latB = nodeMap[path.back()].second, lonB = nodeMap[path.back()].first;
        cost += haversineDistance(latA, lonA, latB, lonB);
    }
    path.push_back(0);

    auto end_time = std::chrono::steady_clock::now();
    timeTaken = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();
    return {path, cost};
}

pair<vector<int>, double> Salesperson::christofidesAlgorithm(double &timeTaken, int start) {

    std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now();
    vector<int> tour;
    double cost = 0;

    Graph<int> newGraph;

    Vertex<int>* init = salesperson.findVertex(start);
    primMst(init);
    for (int i = 0; i < salesperson.getNumVertex(); i++) {
        newGraph.addVertex(i);
    }

    for (auto v : salesperson.getVertexSet()) {
        Edge<int>* edge = v->getPath();
        if (edge != nullptr) {
            newGraph.addBidirectionalEdge(edge->getOrig()->getInfo(), edge->getDest()->getInfo(), edge->getWeight());
        }
    }

    vector<Vertex<int>*> oddDegreeVertices;

    for (Vertex<int>* v : newGraph.getVertexSet()) {
        unsigned int degree = v->getAdj().size();
        if (degree % 2 == 1) {
            oddDegreeVertices.push_back(v);
        }
    }

    while (!oddDegreeVertices.empty()) {
        auto firstIt = oddDegreeVertices.begin();
        auto firstV = *firstIt;
        auto nearestIt = oddDegreeVertices.end();
        auto secondIt = oddDegreeVertices.begin() + 1;
        double dis = INF;
        while (secondIt != oddDegreeVertices.end()) {
            auto secondV = *secondIt;
            if (distMap[firstV->getInfo()][secondV->getInfo()] < dis and distMap[firstV->getInfo()][secondV->getInfo()] >= 0) {
                nearestIt = secondIt;
                dis = distMap[firstV->getInfo()][secondV->getInfo()];
            }

            secondIt++;
        }

        if (nearestIt == oddDegreeVertices.end()) {
            cout << "Sem solucao!\n";
            return {tour, -1};
        }

        newGraph.addBidirectionalEdge(firstV->getInfo(), (*nearestIt)->getInfo(), distMap[firstV->getInfo()][(*nearestIt)->getInfo()]);
        oddDegreeVertices.erase(nearestIt);
        oddDegreeVertices.erase(firstIt);
    }

    tour = newGraph.dfs(start);

    tour.push_back(start);

    for (int i = 0; i < tour.size() - 1; i++) {
        if (distMap[i][i+1] == -1) {
            cout << "Sem solucao!\n";
            return {tour, -1};
        }
        cost += distMap[i][i+1];
    }

    auto end_time = std::chrono::steady_clock::now();
    timeTaken = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();
    return {tour, cost};
}
