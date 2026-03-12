#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <chrono>


using namespace std;

void colocaAresta(list<int> adj[], int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}


int PopulaGrafo(list<int> adj[], int v) {
    int res = 0;
    for(int i = 0; i < v; ++i) {
        for(int j = i + 1; j < v; ++j) {
            if(rand() % 100 <= 50) {
                colocaAresta(adj, i, j);
                res += 1;
           }
        }
    }
    return res;
}


bool VerificaCobertura(list<int> adj[], const vector<int>& cobertura, int n) {
    bool visitados[n];
    for(int i = 0; i < n; ++i) visitados[i] = false;
    for(auto &i : cobertura) visitados[i] = true;

    for(int i = 0; i < n; ++i) {
        for(auto &j : adj[i]) {
            if(!visitados[i] && !visitados[j]) return false;
        }
    }
    return true;
}

void CoberturaExata(int t, list<int> adj[], int n,
    vector<int>& subs, vector <int>& sol) {
    if(t == n) {
        if(VerificaCobertura(adj, subs, t)) {
            if(subs.size() < sol.size() || sol.empty()) sol = subs; //copia
        } return;
    }
    subs.push_back(t);
    CoberturaExata(t + 1, adj, n, subs, sol);
    subs.pop_back();
    CoberturaExata(t + 1, adj, n,subs, sol);
}


void CoberturaExata(list<int> adj[], int n, vector<int>& s) {
    vector<int> subs;
    CoberturaExata(0, adj, n, subs, s);
}


vector<int> CoberturaAproximada(list<int> adj[], int v) {
    vector<int> retorno;
    vector<bool> visitado(v);
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

void TesteExato() {
    // Vertice | Aresta | Tempo Exato | Tempo Exato 2 | Tempo Aproximado | Resposta Exata | Resposta Exata 2 | Resposta Aproximada
    cout << "Vertic\t|\t Aresta \t|\t TempoE |\t Resp \t|\n";
    int n = 1;
    while (n <= 40) {
        list<int> adj[n];
        vector<int> respostaExata, respostaExata2;
        int qtdA = PopulaGrafo(adj, n);

        auto t1 = chrono::high_resolution_clock::now();
        CoberturaExata(adj, n, respostaExata);
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<long double, milli> tempoExato = t2 - t1;

        cout << setprecision(4) << fixed << setw(6);

        cout << n << "\t" << qtdA << "\t" << tempoExato.count()  << "\t"
        << respostaExata.size() << "\t" << endl;
        n++;
    }
}

void TesteAproximado() {
    // Vertice | Aresta | Tempo Aproximado | Resposta Aproximada |
    cout << "Vertice\t|\t Aresta \t|\t TempoAp \t|\t RespAp\t|\n";
    int n = 1;

    while (1) {
        list<int> adj[n];
        vector<int> respostaAproximada;
        int qtdA = PopulaGrafo(adj, n);
        auto t1 = chrono::high_resolution_clock::now();
        respostaAproximada = CoberturaAproximada(adj, n);
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<long double, milli> tempoAprox = t2 - t1;
        cout << setprecision(4) << fixed << setw(6);
        cout << n << "\t" << qtdA << "\t" << respostaAproximada.size() << "\t" << tempoAprox.count() << "\t" << "\t" << endl;
        n++;
    }
}


void TesteTotal() {
    cout << "Vertice\t|\t Aresta \t|\t TempoE |\t RespE \t|\t TempoA \t|\t RespostaA \t| \n";
    int n = 1;
    while (1) {
        list<int> adj[n];
        vector<int> respostaExata, respostaAp;
        int qtdA = PopulaGrafo(adj, n);

        auto t1 = chrono::high_resolution_clock::now();
        CoberturaExata(adj, n, respostaExata);
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<long double, milli> tempoExato = t2 - t1;

        t1 = chrono::high_resolution_clock::now();
        respostaAp = CoberturaAproximada(adj, n);
        t2 = chrono::high_resolution_clock::now();
        chrono::duration<long double, milli> tempoAP = t2 - t1;

        cout << setprecision(4) << fixed << setw(6);

        cout << n << "\t" << qtdA << "\t" << tempoExato.count()  << "\t"
        << respostaExata.size() << "\t" << tempoAP.count() << respostaAp.size() << endl;
        n++;
    }
}


int main() {
    srand(time(NULL));
    TesteTotal();
    return 0;
}
