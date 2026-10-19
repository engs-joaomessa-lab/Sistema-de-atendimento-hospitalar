#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

// Versao equivalente: o template original nao estava disponivel.
// A mesma struct e usada nas tres estruturas, sem classes da STL.
struct No {
    char nome[256];
    int urgencia;
    No* prox;
};

class Fila {
private:
    No* inicio;
    No* fim;

public:
    Fila() {
        inicio = nullptr;
        fim = nullptr;
    }

    // TODO 1 - Coloca o paciente no final da fila.
    void enqueue(const char* nome, int urgencia) {
        No* novo = new No;
        strcpy(novo->nome, nome);
        novo->urgencia = urgencia;
        novo->prox = nullptr;
        if (fim == nullptr) {
            inicio = novo;
        } else {
            fim->prox = novo;
        }
        fim = novo;
    }

    // TODO 2 - Retira o paciente que chegou primeiro.
    bool dequeue(char* nome, int& urgencia) {
        if (inicio == nullptr) return false;
        No* antigo = inicio;
        strcpy(nome, antigo->nome);
        urgencia = antigo->urgencia;
        inicio = inicio->prox;
        if (inicio == nullptr) fim = nullptr;
        delete antigo;
        return true;
    }

    // TODO 3 - Consulta sem retirar.
    const No* frente_peak() const {
        return inicio;
    }

    int tamanho() const {
        int total = 0;
        No* atual = inicio;
        while (atual != nullptr) {
            total++;
            atual = atual->prox;
        }
        return total;
    }

    ~Fila() {
        char nome[256];
        int urgencia;
        while (dequeue(nome, urgencia)) {}
    }
};
