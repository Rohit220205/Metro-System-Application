#include <bits/stdc++.h>
using namespace std;

class MetroMap {
private:
    vector<pair<int, int>> adj[100];
    map<string, int> mp;
    map<int, string> i2s;
    vector<string> keys;
    int sz;

    vector<int> metro_map;

    void dfs(int src, vector<bool>& vis) {
        vis[src] = true;
        metro_map.push_back(src);
        for (auto x : adj[src]) {
            if (!vis[x.first]) {
                dfs(x.first, vis);
            }
        }
    }

    void bfs(vector<int> parent[], int src) {
        vector<int> dist(sz, INT_MAX);
        queue<int> q;
        q.push(src);
        parent[src] = {-1};
        dist[src] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto x : adj[u]) {
                int v = x.first;
                int dis_v = x.second;
                if (dist[v] > dist[u] + dis_v) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    parent[v].clear();
                    parent[v].push_back(u);
                } else if (dist[v] == dist[u] + dis_v) {
                    parent[v].push_back(u);
                }
            }
        }
    }

    void find_paths(vector<vector<int>>& paths, vector<int>& path, vector<int> parent[], int u) {
        if (u == -1) {
            paths.push_back(path);
            return;
        }
        for (auto par : parent[u]) {
            path.push_back(u);
            find_paths(paths, path, parent, par);
            path.pop_back();
        }
    }

public:
    MetroMap() {
        sz = 0;
    }

    void addEdge(const string& a, const string& b, int dis) {
        int x = mp[a];
        int y = mp[b];
        adj[x].push_back({y, dis});
        adj[y].push_back({x, dis});
    }

    void createMetroMap() {
        keys = {
            "Noida Sector 62~B","Botanical Garden~B","Yamuna Bank~B","Rajiv Chowk~BY",
            "Vaishali~B","Moti Nagar~B","Janak Puri West~BO","Dwarka Sector 21~B",
            "Huda City Center~Y","Saket~Y","Vishwavidyalaya~Y","Chandni Chowk~Y",
            "New Delhi~YO","AIIMS~Y","Shivaji Stadium~O","DDS Campus~O",
            "IGI Airport~O","Rajouri Garden~BP","Netaji Subhash Place~PR","Punjabi Bagh West~P"
        };
        
        for (int i = 0; i < keys.size(); i++) {
            mp[keys[i]] = i;
            i2s[i] = keys[i];
        }
        sz = keys.size();

        // Add edges
        addEdge("Noida Sector 62~B", "Botanical Garden~B", 8);
        addEdge("Botanical Garden~B", "Yamuna Bank~B", 10);
        addEdge("Yamuna Bank~B", "Vaishali~B", 8);
        addEdge("Yamuna Bank~B", "Rajiv Chowk~BY", 6);
        addEdge("Rajiv Chowk~BY", "Moti Nagar~B", 9);
        addEdge("Moti Nagar~B", "Janak Puri West~BO", 7);
        addEdge("Janak Puri West~BO", "Dwarka Sector 21~B", 6);
        addEdge("Huda City Center~Y", "Saket~Y", 15);
        addEdge("Saket~Y", "AIIMS~Y", 6);
        addEdge("AIIMS~Y", "Rajiv Chowk~BY", 7);
        addEdge("Rajiv Chowk~BY", "New Delhi~YO", 1);
        addEdge("New Delhi~YO", "Chandni Chowk~Y", 2);
        addEdge("Chandni Chowk~Y", "Vishwavidyalaya~Y", 5);
        addEdge("New Delhi~YO", "Shivaji Stadium~O", 2);
        addEdge("Shivaji Stadium~O", "DDS Campus~O", 7);
        addEdge("DDS Campus~O", "IGI Airport~O", 8);
        addEdge("Moti Nagar~B", "Rajouri Garden~BP", 2);
        addEdge("Punjabi Bagh West~P", "Rajouri Garden~BP", 2);
        addEdge("Punjabi Bagh West~P", "Netaji Subhash Place~PR", 3);
    }

    void displayStations() {
        for (int i = 0; i < keys.size(); i++) {
            cout << i + 1 << ". " << keys[i] << endl;
        }
    }

    void displayMap() {
        metro_map.clear();
        vector<bool> vis(sz, false);
        dfs(0, vis);
        for (int i = 0; i < metro_map.size(); i++) {
            cout << i2s[metro_map[i]];
            if (i != metro_map.size() - 1) cout << " => ";
        }
        cout << endl;
    }

    int shortestDistance(int src, int dest) {
        vector<int> dist(sz, INT_MAX);
        dist[src] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto x = pq.top();
            pq.pop();
            int u = x.second;
            int dis = x.first;
            for (auto y : adj[u]) {
                int v = y.first;
                int w = y.second;
                if (dist[v] > dis + w) {
                    dist[v] = dis + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist[dest];
    }

    void printPath(int src, int dest) {
        vector<vector<int>> paths;
        vector<int> path;
        vector<int> parent[sz];

        bfs(parent, src);
        find_paths(paths, path, parent, dest);

        if (!paths.empty()) {
            reverse(paths[0].begin(), paths[0].end());
            for (int u : paths[0]) {
                cout << i2s[u] << " => ";
            }
            cout << "END" << endl;
        }
    }
};

int main() {
    MetroMap metro;
    metro.createMetroMap();

    cout << "\n\t\t\t****WELCOME TO THE METRO APP*****\n";

    while (true) {
        cout << "\n\t\t\t\t~~LIST OF ACTIONS~~\n\n";
        cout << "1. LIST ALL THE STATIONS IN THE MAP\n";
        cout << "2. SHOW THE METRO MAP\n";
        cout << "3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "4. GET SHORTEST TIME TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "5. GET SHORTEST PATH TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "6. EXIT THE MENU\n\n";
        cout << "ENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 6) : \n";

        int choice;
        cin >> choice;

        if (choice == 1) {
            metro.displayStations();
        } else if (choice == 2) {
            metro.displayMap();
        } else if (choice >= 3 && choice <= 5) {
            cout << "Enter the serial no. of Source and Destination" << endl;
            metro.displayStations();
            int x, y;
            cin >> x >> y;
            x--; y--;
            if (choice == 3 || choice == 4) {
                int p = metro.shortestDistance(x, y);
                if (choice == 3)
                    cout << "Shortest distance between source and destination is " << p << " KM\n";
                else
                    cout << "Shortest time between source and destination is " << p << " Minutes\n";
            } else {
                metro.printPath(x, y);
            }
        } else {
            break;
        }
    }
    return 0;
}
