#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

#include "graph_interface.h"
#include "graph.h"

using namespace std;
using std::string;

void populateMatrix();
void displayMatrix(int vertices);
void addEdge(int vertex1, int vertex2);
map<int, string> cityMap();
int getNumVertices(map<int, string>cities);
int getNumEdges();
void bruteForce(map<int, string>cityMap);

int verticesArr[10][10];
int count = 0;

int main() {

    map<int, string> cities = cityMap();
    int numVertices = getNumVertices(cities);

    populateMatrix();
    displayMatrix(numVertices);
    bruteForce(cities);

    return 0;
}

void populateMatrix() {
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(0, 3);
    addEdge(0, 4);
    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 3);
    addEdge(2, 4);
    addEdge(3, 4);
}

void displayMatrix(int vertices) {
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            cout << verticesArr[i][j] << " ";
        }
        cout << endl;
    }
}

void addEdge(int vertex1, int vertex2) {
    map<int, string> cityAt = cityMap();
    string temp1 = cityAt[vertex1];
    string temp2 = cityAt[vertex2];
    int tempEdgeWeight = getEdgeWeight(temp1, temp2);
    verticesArr[vertex1][vertex2] = tempEdgeWeight;
    verticesArr[vertex2][vertex1] = tempEdgeWeight;
}

map<int, string> cityMap() {
    map<int, string> cityMap;
    cityMap[0] = "Reno";
    cityMap[1] = "Seattle";
    cityMap[2] = "Las Vegas";
    cityMap[3] = "Salt Lake City";
    cityMap[4] = "San Francisco";
    return cityMap;
}

int getNumVertices(map<int, string> cities) {
    return cities.size();
}

int getNumEdges() {
    int numEdges = 0;
    fstream milesFile;
    milesFile.open("miles.txt");
    string line;
    while(getline(milesFile, line)) {
        numEdges++;
    }
    numEdges--;
    milesFile.close();
    return numEdges;
}
  

void bruteForce(map<int, string> cityMap) {
    fstream paths;
    paths.open("paths.txt");

    vector<int> costsVector;

    int reno_index = 0;
    for(int a = 0; a < 5; a++) {
        int first_leg_edge_weight = 0;
        int second_leg_edge_weight = 0;
        int third_leg_edge_weight = 0;
        int fourth_leg_edge_weight = 0;
        int fifth_leg_edge_weight = 0;

        // Get distance between city 0 and 1
        first_leg_edge_weight = getEdgeWeight(cityMap[reno_index], cityMap[a]);
        if (first_leg_edge_weight == 0) {
            continue;
        }
        for(int b = 0; b < 5; b++) {
            // Get distance between city 1 and 2
            second_leg_edge_weight = getEdgeWeight(cityMap[a], cityMap[b]);
            if (second_leg_edge_weight == 0 || cityMap[a] == cityMap[b]) {
                continue;
            }
            for(int c = 0; c < 5; c++) {
                // Get distance between city 2 and 3
                third_leg_edge_weight = getEdgeWeight(cityMap[b], cityMap[c]);
                if (third_leg_edge_weight == 0 || cityMap[a] == cityMap[c] || cityMap[b] == cityMap[c]) {
                    continue;
                }
                for(int d = 0; d < 5; d++) {
                    // Get distance between city 3 and 4
                    fourth_leg_edge_weight = getEdgeWeight(cityMap[c], cityMap[d]);
                    if (fourth_leg_edge_weight == 0 || cityMap[c] == cityMap[d] || cityMap[a] == cityMap[d] 
                    || cityMap[b] == cityMap[d]) {
                        continue;
                    }
                    // Get distance between 5 and 0
                    fifth_leg_edge_weight = getEdgeWeight(cityMap[d], cityMap[reno_index]);
                    if (fifth_leg_edge_weight == 0 || cityMap[d] == cityMap[reno_index] || cityMap[c] == cityMap[reno_index]
                     || cityMap[a] == cityMap[reno_index] || cityMap[b] == cityMap[reno_index]) {
                        continue;
                    }
                    // add route to txt file
                    int total_distance = first_leg_edge_weight + second_leg_edge_weight + third_leg_edge_weight + 
                    fourth_leg_edge_weight + fifth_leg_edge_weight;
                    int total_cost = total_distance/40;
                    costsVector.push_back(total_cost);
                    paths << cityMap[reno_index] << " --> "  << cityMap[a] << " --> "  << cityMap[b]
                     << " --> "  << cityMap[c] << " --> "  << cityMap[d] << " --> "  << cityMap[reno_index]
                      << ": Total Distance: " << total_distance << " -- Total Cost: " << total_cost << endl << endl;
                }
            }
        }
    }
    int min_cost = *min_element(costsVector.begin(), costsVector.end());
    paths << "Most cost efficient route: " << min_cost;
    paths.close();
}
