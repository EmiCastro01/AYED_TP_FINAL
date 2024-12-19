#include <cstdlib>
#include <iostream>
#include <limits>

#define INFI std::numeric_limits<int>::max()
#define ROUTER_MAX_NO 256

#define MIEMBRO 1
#define NO_MIEMBRO 0

using namespace std;

int *dijkstra(const int C[][ROUTER_MAX_NO], int s, int t, int Pre[],
              int endpoint) {
    static int D[ROUTER_MAX_NO];
    int S[ROUTER_MAX_NO];
    int actual, i, k, b;
    int menordist, nuevadist;

    for (i = 0; i < endpoint; i++) {
        S[i] = NO_MIEMBRO;
        D[i] = INFI;
        Pre[i] = -1;
    }
    S[s] = MIEMBRO;
    D[s] = 0;
    actual = s;
    b = 1;
    k = 0;
    while ((actual != t) && (b == 1)) {
        b = 0;
        menordist = INFI;
        for (i = 0; i < endpoint; i++) {
            if (S[i] == NO_MIEMBRO) {
                nuevadist = D[actual] + C[actual][i];
                if (nuevadist < D[i]) {
                    D[i] = nuevadist;
                    Pre[i] = actual;
                    b = 1;
                }
                if (D[i] < menordist) {
                    menordist = D[i];
                    k = i;
                    b = 1;
                }
            }
        }
        actual = k;
        S[actual] = MIEMBRO;
    }
    return D;
}

void camino(int P[], int s, int t) {
    if (t == s)
        cout << s << "  ";
    else {
        camino(P, s, P[t]);
        cout << t << "  ";
    }
}

int next_opt(int Pre[], int s, int t) {
    if (s == t) return s;
    if (Pre[t] == s) {
        return t;
    } else {
        return next_opt(Pre, s, Pre[t]);
    }
}