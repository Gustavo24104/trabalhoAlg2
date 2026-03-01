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

// adiciona arestas aleatórias no grafo
void PopulaGrafo(list<int> adj[], int v) {
    srand(time(NULL));
    for(int i = 0; i < v; ++i) {
        for(int j = i + 1; j < v; ++j) {
            if(rand() % 100 <= 30) colocaAresta(adj, i, j);
        }
    }
}


int main() {


    bool v[7] = {false};
    list<int> adj[7];
    vector<int> resposta;
    PopulaGrafo(adj, 7);

    resposta = CoberturaAproximada(adj, 7, v);

    for(auto &j : resposta) {
        cout << j << "\n";
    }

}