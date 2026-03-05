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
                res += 2;
            }
        }
    }
    return res;
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

bool BuscaCobertura(list<int> adj[], const vector<bool>& visitado, int n, int k, int E) {
    if(E > 0 && k == 0) return false;
    if(E == 0) return true;
    for(int u = 0; u < n; ++u) {
        if(!visitado[u]) {
            for(auto &v : adj[u]) {
                if(!visitado[v]) {
                    vector<bool> Gu(visitado);
                    vector<bool> Gv(visitado);
                    E -= adj[u].size() + adj[v].size();
                    E++;
                    Gu[u] = true;
                    Gv[v] = true;
                    if(BuscaCobertura(adj, Gu, n - 1, k - 1, E)) return true;
                    if(BuscaCobertura(adj, Gv, n - 1, k - 1, E)) return true;
                    return false;
                }
            }
        }
    }
    return false;
}

vector<int> CoberturaAproximada(list<int> adj[], int v) {
    vector<int> retorno;
    vector<bool> visitado;
    visitado.resize(v);
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

vector<int> CoberturaExataMelhor(list<int> adj[], int n, int E) {
    for(int i = 0; i < n; ++i) {
        vector<bool> b(n);
        bool achou = BuscaCobertura(adj, b, n, i, E);
        if(achou) {
            vector<vector<int>> candidatos = GeraSubconjunto(n, i);
            for(auto &j : candidatos) {
                if(VerificaCobertura(adj, j, n)) return j;
            }
        }
    }
    vector<int> a;
    return a;
}


void TesteTotal() {
    // Vertice | Aresta | Tempo Exato | Tempo Exato 2 | Tempo Aproximado | Resposta Exata | Resposta Exata 2 | Resposta Aproximada
    cout << "Vertic\t|\t Aresta \t|\t TempoE \t|\t TempoE2 \t|\t TempoAp \t||\t RespEx \t|\t RespE2 \t|\t RespAp\t| \n";
    int n = 1;

    while (n <= 30) {
        list<int> adj[n];
        vector<int> respostaExata, respostaAproximada, respostaExata2;
        int qtdA = PopulaGrafo(adj, n);

        auto t1 = chrono::high_resolution_clock::now();
        respostaExata = CoberturaExata(adj, n);
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<long double, milli> tempoExato = t2 - t1;

        t1 = chrono::high_resolution_clock::now();
        respostaAproximada = CoberturaAproximada(adj, n);
        t2 = chrono::high_resolution_clock::now();
        chrono::duration<long double, milli> tempoAprox = t2 - t1;

        t1 = chrono::high_resolution_clock::now();
        respostaExata2 = CoberturaExataMelhor(adj, n, qtdA);
        t2 = chrono::high_resolution_clock::now();
        chrono::duration<long double, milli> tempoExato2 = t2 - t1;


        cout << setprecision(4) << fixed << setw(6);

        cout << n << "\t" << qtdA << "\t" << tempoExato.count()  << "\t" << tempoExato2.count() << "\t" <<
            tempoAprox.count() << "\t" << respostaExata.size() << "\t"
            << respostaExata2.size() << "\t" << respostaAproximada.size() << endl;
        n++;
    }
}

void TesteAproximado() {
    // Vertice | Aresta | Tempo Aproximado | Resposta Aproximada |
    cout << "Vertice\t|\t Aresta \t|\t TempoAp \t|\t RespAp\t|\n";
    int n = 30;

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





int main() {
    srand(time(NULL));
    TesteTotal();
    return 0;
}
