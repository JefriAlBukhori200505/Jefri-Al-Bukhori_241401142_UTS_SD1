#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int to;
    int jarak;
};

const int MAX = 5;

vector<Edge> graph[MAX];

string kodeKota[MAX] = {"A", "B", "C", "D", "E"};
string namaKota[MAX] = {
    "Ikan Bakar Pak Harry",
    "Gudang Kaleng Bekas",
    "Sushi Kucing Alya",
    "Kedai IKLC",
    "Pasar Ikan Tengah Malam"
};

bool visited[MAX];
vector<int> urutanDFS;

void DFS(int awal) {
    visited[awal] = true;
    urutanDFS.push_back(awal);

    for (int i = graph[awal].size() - 1; i >= 0; i--) {
        int next = graph[awal][i].to;
        if (!visited[next]) {
            DFS(next);
        }
    }
}

void BFS(int start, int goal, int parent[]) {
    bool visit[MAX];
    for (int i = 0; i < MAX; i++) {
        visit[i] = false;
        parent[i] = -1;
    }

    int q[MAX];
    int front = 0, rear = -1;

    q[++rear] = start;
    visit[start] = true;

    while (front <= rear) {
        int cur = q[front++];
        if (cur == goal) break;

        for (int i = graph[cur].size() - 1; i >= 0; i--) {
            int next = graph[cur][i].to;
            if (!visit[next]) {
                visit[next] = true;
                parent[next] = cur;
                q[++rear] = next;
            }
        }
    }
}

int cariJarak(int a, int b) {
    for (int i = 0; i < graph[a].size(); i++) {
        if (graph[a][i].to == b) {
            return graph[a][i].jarak;
        }
    }
    return 0;
}

int main() {
    
    graph[0].push_back({1, 5}); 
    graph[1].push_back({0, 5});

    graph[0].push_back({2, 2}); 
    graph[2].push_back({0, 2});

    graph[1].push_back({3, 4}); 
    graph[3].push_back({1, 4});

    graph[2].push_back({3, 1}); 
    graph[3].push_back({2, 1});

    graph[3].push_back({4, 3}); 
    graph[4].push_back({3, 3});

    for (int i = 0; i < MAX; i++) visited[i] = false;
    urutanDFS.clear();
    DFS(0);

    cout << "PENJELAJAHAN PARUL (DFS dari A):\n";
    for (int i = 0; i < urutanDFS.size(); i++) {
        cout << kodeKota[urutanDFS[i]];
        if (i != urutanDFS.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl << endl;

    int parent[MAX];
    BFS(0, 4, parent);

    int path[MAX];
    int panjang = 0;
    int posisi = 4;
    while (posisi != -1) {
        path[panjang++] = posisi;
        posisi = parent[posisi];
    }

    cout << "JALUR TERCEPAT PARUL (BFS):\n";
    for (int i = panjang - 1; i >= 0; i--) {
        int kota = path[i];
        cout << namaKota[kota] << " (" << kodeKota[kota] << ")\n";
        if (i > 0) {
            int next = path[i - 1];
            cout << cariJarak(kota, next) << "m\n";
        }
    }
    cout << endl;

    cout << "Jalur terpendek: ";
    for (int i = panjang - 1; i >= 0; i--) {
        cout << kodeKota[path[i]];
        if (i != 0) cout << " -> ";
    }
    cout << endl;
    cout << "Total langkah: " << panjang - 1 << " edge" << endl;

    int totalJarak = 0;
    for (int i = panjang - 1; i > 0; i--) {
        int a = path[i];
        int b = path[i - 1];
        totalJarak += cariJarak(a, b);
    }
    cout << "Total jarak: " << totalJarak << " meter" << endl;

    return 0;
}
