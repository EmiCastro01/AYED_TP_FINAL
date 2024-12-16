#pragma once
#include <iostream>
#include <limits>

#define INFI std::numeric_limits<int>::max()
#define ROUTER_MAX_NO 10

using namespace std;

void warshall(const int peso[ROUTER_MAX_NO][ROUTER_MAX_NO], int caminos[ROUTER_MAX_NO][ROUTER_MAX_NO]);
void floyd(const int peso[ROUTER_MAX_NO][ROUTER_MAX_NO], int A[ROUTER_MAX_NO][ROUTER_MAX_NO], int cf[ROUTER_MAX_NO][ROUTER_MAX_NO]);
void caminoFloyd(const int cf[ROUTER_MAX_NO][ROUTER_MAX_NO], int s, int t);

void warshall(const int peso[ROUTER_MAX_NO][ROUTER_MAX_NO], int caminos[ROUTER_MAX_NO][ROUTER_MAX_NO]) {
    for (int i = 0; i < ROUTER_MAX_NO; ++i) {
        for (int j = 0; j < ROUTER_MAX_NO; ++j) {
            caminos[i][j] = (peso[i][j] != INFI) ? 1 : 0;
        }
    }

    for (int k = 0; k < ROUTER_MAX_NO; ++k) {
        for (int i = 0; i < ROUTER_MAX_NO; ++i) {
            for (int j = 0; j < ROUTER_MAX_NO; ++j) {
                if (caminos[i][j] == 0) 
                    caminos[i][j] = caminos[i][k] && caminos[k][j];
            }
        }
    }
}

void floyd(const int peso[ROUTER_MAX_NO][ROUTER_MAX_NO], int A[ROUTER_MAX_NO][ROUTER_MAX_NO], int cf[ROUTER_MAX_NO][ROUTER_MAX_NO]) {
    for (int i = 0; i < ROUTER_MAX_NO; ++i) {
        for (int j = 0; j < ROUTER_MAX_NO; ++j) {
            A[i][j] = peso[i][j];
            cf[i][j] = -1;
        }
        A[i][i] = 0;
    }

    for (int k = 0; k < ROUTER_MAX_NO; ++k) {
        for (int i = 0; i < ROUTER_MAX_NO; ++i) {
            for (int j = 0; j < ROUTER_MAX_NO; ++j) {
                if (A[i][k] != INFI && A[k][j] != INFI && (A[i][k] + A[k][j] < A[i][j])) {
                    A[i][j] = A[i][k] + A[k][j];
                    cf[i][j] = k;
                }
            }
        }
    }
}

void caminoFloyd(const int cf[ROUTER_MAX_NO][ROUTER_MAX_NO], int s, int t) {
    int k = cf[s][t];
    if (k != -1) {
        caminoFloyd(cf, s, k);
        cout << " " << k;
        caminoFloyd(cf, k, t);
    }
}

int next_hop(int cf[ROUTER_MAX_NO][ROUTER_MAX_NO], int s, int t) {
    int k = cf[s][t];
    if (k == -1) {
        // Si no hay intermediario, el siguiente salto es el destino directo.
        return t;
    } else {
        // Si hay intermediario, seguimos recursivamente.
        return next_hop(cf, s, k);
    }
}