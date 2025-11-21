#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct paciente {
    string senha;
    char prioridade;
    int chegada;
};

vector<paciente> vermelho;
vector<paciente> amarelo;
vector<paciente> verde;
vector<paciente> branco;

int atendidos = 0;
int atendidosv = 0;
int atendidosa = 0;
int atendidosd = 0;
int atendidosb = 0;
int picofila = 0;
int esperamaxima = 0;

void chegada(string senha, char prior, int hh, int mm) {
    int chegada = hh * 60 + mm;
    paciente p = {senha, prior, chegada};
    if (prior == 'V') {
        vermelho.push_back(p);
    } else if (prior == 'A') {
        amarelo.push_back(p);
    } else if (prior == 'D') {
        verde.push_back(p);
    } else if (prior == 'B') {
        branco.push_back(p);
    }

    int totalfilas = vermelho.size() + amarelo.size() + verde.size() + branco.size();
    if (totalfilas > picofila) {
        picofila = totalfilas;
    }
}

void atendimento(int hh, int mm) {
    int agora = hh * 60 + mm;
    if (vermelho.empty() && amarelo.empty() && verde.empty() && branco.empty()) {
        cout << (hh < 10 ? "0" : "") << hh << " " << (mm < 10 ? "0" : "") << mm << " Sem pacientes aguardando atendimento" << endl;
        return;
    }

    paciente p;
    if (!vermelho.empty()) {
        p = vermelho[0];
        vermelho.erase(vermelho.begin());
        atendidosv++;
    } else if (!amarelo.empty()) {
        p = amarelo[0];
        amarelo.erase(amarelo.begin());
        atendidosa++;
    } else if (!verde.empty()) {
        p = verde[0];
        verde.erase(verde.begin());
        atendidosd++;
    } else if (!branco.empty()) {
        p = branco[0];
        branco.erase(branco.begin());
        atendidosb++;
    }

    atendidos++;
    int espera = agora - p.chegada;
    if (espera > esperamaxima) {
        esperamaxima = espera;
    }
}

void exibicao() {
    cout << "V:" << vermelho.size() << " A:" << amarelo.size() << " D:" << verde.size() << " B:" << branco.size() << " | Atendidos:" << atendidos << endl;
}

void relatorio() {
    cout << "--- RELATÓRIO FINAL ---" << endl;
    cout << "Total atendidos: " << atendidos << endl;
    cout << "Por prioridade: V=" << atendidosv << " A=" << atendidosa << " D=" << atendidosd << " B=" << atendidosb << endl;
    cout << "Pico de lotação: " << picofila << endl;
    cout << "Espera máxima: " << esperamaxima << " min" << endl;
}

int main() {
    string linha;
    while (getline(cin, linha) && linha != "Q") {
        stringstream ss(linha);
        char comando;
        ss >> comando;

        if (comando == 'C') {
            string senha;
            char prior;
            int hh, mm;
            ss >> senha >> prior >> hh >> mm;
            chegada(senha, prior, hh, mm);
        } else if (comando == 'A') {
            int hh, mm;
            ss >> hh >> mm;
            atendimento(hh, mm);
        } else if (comando == 'D') {
            exibicao();
        }
    }
    relatorio();
    return 0;
}