#include <algorithm>
#include <iostream>
#include <cmath>
#include <list>
#include <vector>

using namespace std;


vector<int> CoberturaAproximada(list<int> adj[], int v, bool visitado[]) {
    vector<int> retorno;

    for(int i = 0; i < v; ++i) {

        if(!visitado[i]) {
            for(int &j : adj[i]) {

                if(!visitado[j]) {
                    visitado[i] = true;
                    visitado[j] = true;
                    retorno.push_back(i);
                    retorno.push_back(j);
                    break;
                }
            }
        }
    }
    return retorno;
}

void colocaAresta(list<int> adj[], int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}


int main() {
    bool v[7] = {false};
    list<int> adj[7];
    vector<int> resposta;
    colocaAresta(adj, 0, 1);
    colocaAresta(adj, 0, 2);
    colocaAresta(adj, 1, 3);
    colocaAresta(adj, 3, 4);
    colocaAresta(adj, 4, 5);
    colocaAresta(adj, 5, 6);

    resposta = CoberturaAproximada(adj, 7, v);

    for(auto &j : resposta) {
        cout << j << "\n";
    }

}