#pragma once
#include <iostream>
#include <vector>
#include <limits>

#define INFI std::numeric_limits<int>::max()

using namespace std;

void warshall(const vector<vector<int>>& peso, vector<vector<int>>& caminos);
void floyd(const vector<vector<int>>& peso, vector<vector<int>>& A, vector<vector<int>>& cf);
void caminoFloyd(const vector<vector<int>>& cf, int s, int t);

void warshall(const vector<vector<int>>& peso, vector<vector<int>>& caminos) {
    int n = peso.size();
    caminos = vector<vector<int>>(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (peso[i][j] != INFI) caminos[i][j] = 1;
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (caminos[i][j] == 0) 
                    caminos[i][j] = caminos[i][k] && caminos[k][j];
            }
        }
    }
}

void floyd(const vector<vector<int>>& peso, vector<vector<int>>& A, vector<vector<int>>& cf) {
    int n = peso.size();
    A = peso;
    cf = vector<vector<int>>(n, vector<int>(n, -1));

    for (int i = 0; i < n; ++i) A[i][i] = 0;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (A[i][k] != INFI && A[k][j] != INFI && (A[i][k] + A[k][j] < A[i][j])) {
                    A[i][j] = A[i][k] + A[k][j];
                    cf[i][j] = k;
                }
            }
        }
    }
}

void caminoFloyd(const vector<vector<int>>& cf, int s, int t) {
    int k = cf[s][t];
    if (k != -1) {
        caminoFloyd(cf, s, k);
        cout << " " << k;
        caminoFloyd(cf, k, t);
    }
}