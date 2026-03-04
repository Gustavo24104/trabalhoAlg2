#include <algorithm>
#include <iostream>
#include <cmath>
#include <list>
#include <vector>

using namespace std;
#define N 30


void colocaAresta(list<int> adj[], int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// adiciona arestas aleatórias no grafo
void PopulaGrafo(list<int> adj[], int v) {
    srand(time(NULL));
    for(int i = 0; i < v; ++i) {
        for(int j = i + 1; j < v; ++j) {
            if(rand() % 100 <= 50) colocaAresta(adj, i, j);
            // colocaAresta(adj, i, j);
        }
    }
}



bool contains(const vector<int>& s, int a, int b) {
    for(auto &i : s) {
        if(i == a || i == b) return true;
    }
    return false;
}


bool VerificaCobertura(list<int> adj[], const vector<int>& cobertura, int n) {
    for(int i = 0; i < n; ++i) {
        for(auto &j : adj[i]) {
            if(!contains(cobertura, i , j)) return false;
        }
    }
    return true;
}


void GeraSubconjunto(int ate, vector<int>& subconjunto, vector<vector<int>>& retorno, int tamanhoSub, int prox) {
    if(tamanhoSub == subconjunto.size()) {
        retorno.push_back(subconjunto);
        return;
    }
    for(int i = prox; i < ate; ++i) {
        subconjunto[tamanhoSub] = i;
        GeraSubconjunto(ate, subconjunto, retorno, tamanhoSub + 1, i + 1);
    }
}

vector<vector<int>> GeraSubconjunto(int ate, int t) {
    vector<int> subconjunto;
    subconjunto.resize(t);
    vector<vector<int>> retorno;
    GeraSubconjunto(ate, subconjunto, retorno, 0, 0);
    return retorno;
}


vector<int> CoberturaExata(list<int> adj[], int n) {
    for(int i = 0; i < n; ++i) {
        vector<vector<int>> sub = GeraSubconjunto(n, i);
        for(auto &j : sub) {
            if(VerificaCobertura(adj, j, n)) return j;
        }
    }
    vector<int> retorno;
    retorno.push_back(-1);
    return retorno;
}


vector<int> CoberturaAproximada(list<int> adj[], int v) {
    vector<int> retorno;
    vector<bool> visitado;
    visitado.resize(v);

    for(int i = 0; i < v; ++i) {
        if(!visitado[i]) {

            for(int &j : adj[i]) {
                //cout << "Vertice: (" << i << ", " << j << ")\n";
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


int main() {
    list<int> adj[N];
    vector<int> respostaExata, respostaAproximada;
    PopulaGrafo(adj, N);


    respostaAproximada = CoberturaAproximada(adj, N);
    respostaExata = CoberturaExata(adj, N);


    bool verifica = VerificaCobertura(adj, respostaExata, N);

    if(!verifica) {
        cout << "que\n";
        return -1;
    }


    cout << "Exata achou com: " << respostaExata.size() << " elementos\n";
    for(auto &j : respostaExata) {
        cout << j << ", ";
    }


    cout << "\nAproximada achou com: " << respostaAproximada.size() << " elementos\n";

    for(auto &j : respostaAproximada) {
        cout << j << ", ";
    }
    return 0;
}
