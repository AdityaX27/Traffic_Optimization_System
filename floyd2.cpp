#include <bits/stdc++.h>
#include "gnuplot-iostream.h" // Include gnuplot-iostream header
using namespace std;
const int N = 1000;
const int INF = 1e9 + 10;

int dist[N][N];
int td[N][N];
double ko[N][N];
int net[N][N];

void initializeMatrices() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j) {
                dist[i][j] = 0;
                td[i][j] = 0;
                ko[i][j] = 0;
            } else {
                dist[i][j] = INF;
                td[i][j] = INF;
                ko[i][j] = INF;
            }
            net[i][j] = -1; // Initialize net with -1 to indicate no path
        }
    }
}

void floydWarshall(int n) {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (ko[i][j] > ko[i][k] + ko[k][j]) {
                    ko[i][j] = ko[i][k] + ko[k][j];
                    net[i][j] = net[i][k];
                }
            }
        }
    }
}

void plotMatrix(int n) {
    Gnuplot gp;
    gp << "set title 'Optimized Shortest Time Matrix (hrs)'\n";
    gp << "set xlabel 'Nodes'\n";
    gp << "set ylabel 'Nodes'\n";
    gp << "set zlabel 'Time'\n";
    gp << "set xrange [1:" << n << "]\n";
    gp << "set yrange [1:" << n << "]\n";
    gp << "set zrange [0:]\n";
    gp << "set dgrid3d " << n << "," << n << "\n";
    gp << "set hidden3d\n";
    gp << "splot '-' with lines\n";

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (ko[i][j] == INF) {
                gp << i << " " << j << " " << 0 << "\n";
            } else {
                gp << i << " " << j << " " << ko[i][j] << "\n";
            }
        }
    }
    gp << "e\n";
}

void printMatrix(int n) {
    cout << "-----OPTIMIZED SHORTEST TIME MATRIX(hrs)----" << endl << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (ko[i][j] == INF) {
                cout << "I ";
            } else {
                cout << ko[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void printPath(int u, int v) {
    if (net[u][v] == -1) {
        cout << "No path exists between " << u << " and " << v << endl;
        return;
    }
    cout << u;
    while (u != v) {
        u = net[u][v];
        cout << " --> " << u;
    }
    cout << endl;
}

int main() {
    initializeMatrices();

    int n, m; // n vertices, m number of edges
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    cout << "Enter edges (x, y, weight, traffic density):" << endl;
    for (int i = 0; i < m; ++i) {
        int x, y, wt, kt;
        cin >> x >> y >> wt >> kt;

        if (x <= 0 || x > n || y <= 0 || y > n || x == y) {
            cout << "Invalid input for edge. Please enter valid nodes." << endl;
            continue;
        }

        dist[x][y] = wt;
        td[x][y] = kt;
        ko[x][y] = (wt / (60 - (0.05 * kt)));
        net[x][y] = y;
    }

    // Running the Floyd-Warshall algorithm
    floydWarshall(n);

    // Printing the optimized shortest time matrix
    printMatrix(n);

    // Plotting the matrix
    plotMatrix(n);

    char choice;
    do {
        int u, v;
        cout << "Enter starting and ending node respectively to find the shortest path: ";
        cin >> u >> v;
        if (u <= 0 || u > n || v <= 0 || v > n) {
            cout << "Invalid nodes. Please enter valid nodes." << endl;
        } else {
            printPath(u, v);
        }

        cout << "Do you want to find another path? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

