#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Graph {
private:
    map<T, list<pair<T, float>>> adjList;

public:
    list<T> path;

    void addEdge(T u, T v, float dist, bool isBidirectional = true) {
        adjList[u].push_back(make_pair(v, dist));
        if (isBidirectional) {
            adjList[v].push_back(make_pair(u, dist));
        }
    }

    int timetaken(float dist) {
        float speed = 0.55;
        return ceil(dist / speed);
    }

    int money(float dist) {
        if (dist <= 2)
            return 10;
        else if (dist > 2 && dist <= 5)
            return 20;
        else if (dist > 5 && dist <= 12)
            return 30;
        else if (dist > 12 && dist <= 21)
            return 40;
        else if (dist > 21 && dist <= 32)
            return 50;
        else
            return 60;
    }

    void dijkstra(T src, T dest, map<T, float>& dist, map<T, T>& prev) {
        set<pair<float, T>> s;
        dist.clear();
        prev.clear();

        for (auto node : adjList) {
            dist[node.first] = numeric_limits<float>::infinity();
            prev[node.first] = "";
        }

        dist[src] = 0;
        s.insert({0, src});

        while (!s.empty()) {
            auto p = *(s.begin());
            T node = p.second;
            float nodeDist = p.first;
            s.erase(s.begin());

            for (auto child : adjList[node]) {
                T destNode = child.first;
                float edgeDist = child.second;

                if (nodeDist + edgeDist < dist[destNode]) {
                    auto f = s.find({dist[destNode], destNode});
                    if (f != s.end()) {
                        s.erase(f);
                    }
                    dist[destNode] = nodeDist + edgeDist;
                    prev[destNode] = node;
                    s.insert({dist[destNode], destNode});
                }
            }
        }
    }
    void bfsShortestPath(T src, T dest, list<T>& bfsPath, float& totalDist) {
        map<T, bool> visited;
        map<T, T> parent;
        map<T, float> dist;
        queue<T> q;

        for (auto node : adjList) {
            visited[node.first] = false;
            parent[node.first] = "";
            dist[node.first] = numeric_limits<float>::infinity();
        }

        q.push(src);
        visited[src] = true;
        dist[src] = 0;

        while (!q.empty()) {
            T node = q.front();
            q.pop();

            for (auto neighbor : adjList[node]) {
                T neighborNode = neighbor.first;
                float edgeDist = neighbor.second;

                if (!visited[neighborNode]) {
                    visited[neighborNode] = true;
                    parent[neighborNode] = node;
                    dist[neighborNode] = dist[node] + edgeDist;
                    q.push(neighborNode);

                    if (neighborNode == dest) {
                        totalDist = dist[dest];
                        break;
                    }
                }
            }
        }
        T temp = dest;
        while (temp != "") {
            bfsPath.push_front(temp);
            temp = parent[temp];
        }
    }
    void printPath(T destination, map<T, T>& prev) {
        for (; destination != ""; destination = prev[destination]) {
            path.push_front(destination);
        }

        for (const auto& station : path) {
            cout << station;
            if (station != path.back()) cout << " -> ";
        }
        cout << endl;
    }
      void printPath(list<T>& bfsPath) {
        for (const auto& station : bfsPath) {
            cout << station;
            if (station != bfsPath.back()) cout << " -> ";
        }
        cout << endl;
    }

    void listStations() {
        cout << endl << "                                               Available Stations: " << endl;
        for (auto& pair : adjList) {
            cout << "                                            - " << pair.first << endl;
        }
    }
};

int main() {
    Graph<string> metro;

     metro.addEdge("Gec", "IIUC", 19.2);
    metro.addEdge("Muradpur", "IIUC", 27.2);
    metro.addEdge("Bahaddarhat", "IIUC", 27.0);
    metro.addEdge("Chawkbazar", "IIUC", 25.8);
    metro.addEdge("Agrabad", "IIUC", 20.6);
    metro.addEdge("2 No Gate", "IIUC", 20.4);
    metro.addEdge("Bhatiari", "IIUC", 8.4);
    metro.addEdge("Ak khan", "IIUC", 16.5);
    metro.addEdge("Wasa", "Gec", 2.4);
    metro.addEdge("Bhatiari", "Ak khan", 8.1);
    metro.addEdge("2 No Gate", "Muradpur", 3.0);
    metro.addEdge("Bahaddarhat", "Agrabad", 5.7);
    metro.addEdge("2 No Gate", "Bayezid link Road", 5.0);
    metro.addEdge("IIUC", "Bayezid link Road", 15.2);
    metro.addEdge("Gec", "Ak khan", 14.1);

    while (true) {
        cout << endl;
        cout << "                                       -------------------------------------------" << endl;
        cout << "                                                       IIUC METRO                " << endl;
        cout << "                                       -------------------------------------------" << endl;
        cout << "                                       1. View Path and Cost" << endl;
        cout << "                                       2. View Stations" << endl;
        cout << "                                       3. Exit" << endl;
        cout << "                                       Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << endl;
            string source, destination;
            cout << "                                       Enter source station: ";
            getline(cin, source);
            cout << "                                       Enter destination station: ";
            getline(cin, destination);

            cout << "                                       Choose method (1: Dijkstra, 2: BFS): ";
            int method;
            cin >> method;
            if (method == 1) {
            map<string, float> dist;
            map<string, string> prev;
            metro.dijkstra(source, destination, dist, prev);

            if (dist[destination] < numeric_limits<float>::infinity()) {
                cout << endl
                     << endl
                     << "                                       Shortest distance: " << dist[destination] << " kms";
                cout << endl
                     << "                                       Path: ";
                metro.printPath(destination, prev);
                cout << endl
                     << "                                       Total Time: " << metro.timetaken(dist[destination]) << " min";
                cout << endl
                     << "                                       Total Fare: " << metro.money(dist[destination]) << " Tk" << endl;
            } else {
                cout << "                                       No path found between " << source << " and " << destination << "." << endl;
            }
            }
            else if (method == 2) {
                list<string> bfsPath;
                float totalDist = 0;
                metro.bfsShortestPath(source, destination, bfsPath, totalDist);

                if (!bfsPath.empty() && bfsPath.front() == source) {
                    cout << endl
                         << "                                       Shortest distance (BFS): " << totalDist << " kms";
                    cout << endl
                         << "                                       Path: ";
                    metro.printPath(bfsPath);
                    cout << endl
                         << "                                       Total Time: " << metro.timetaken(totalDist) << " min";
                    cout << endl
                         << "                                       Total Fare: " << metro.money(totalDist) << " Tk" << endl;
                } else {
                    cout << "                                       No path found between " << source << " and " << destination << "." << endl;
                }
            } else {
                cout << "                                       Invalid method choice." << endl;
            }
        } else if (choice == 2) {
            metro.listStations();
        } else if (choice == 3) {
            cout << endl << "                                       Thank you for using IIUC Metro!" << endl;
            break;
        } else {
            cout << "                                        Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
