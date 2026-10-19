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

class Pilha {
private:
    No* topo;

public:
    Pilha() {
        topo = nullptr;
    }

    // TODO 4 - Guarda o atendimento mais recente no topo.
    void push(const char* nome) {
        No* novo = new No;
        strcpy(novo->nome, nome);
        novo->urgencia = 0;
        novo->prox = topo;
        topo = novo;
    }

    // TODO 5 - Retira o registro do topo.
    bool pop(char* nome) {
        if (topo == nullptr) return false;
        No* antigo = topo;
        strcpy(nome, antigo->nome);
        topo = topo->prox;
        delete antigo;
        return true;
    }

    // TODO 6 - Consulta o ultimo registro sem remover.
    const No* peek() const {
        return topo;
    }

    ~Pilha() {
        char nome[256];
        while (pop(nome)) {}
    }
};

class ListaMedicos {
private:
    No* inicio;

public:
    ListaMedicos() {
        inicio = nullptr;
    }

    // TODO 7 - Adiciona o medico no final da lista.
    void adicionarMedico(const char* nome) {
        No* novo = new No;
        strcpy(novo->nome, nome);
        novo->urgencia = 0;
        novo->prox = nullptr;
        if (inicio == nullptr) {
            inicio = novo;
        } else {
            No* atual = inicio;
            while (atual->prox != nullptr) atual = atual->prox;
            atual->prox = novo;
        }
    }

    // TODO 8 - Chama e retira o primeiro medico.
    bool chamarMedico(char* nome) {
        if (inicio == nullptr) return false;
        No* antigo = inicio;
        strcpy(nome, antigo->nome);
        inicio = inicio->prox;
        delete antigo;
        return true;
    }

    // TODO 9 - Mostra a ordem dos medicos.
    void percorrer() const {
        if (inicio == nullptr) cout << "Nenhum medico cadastrado.\n";
        No* atual = inicio;
        while (atual != nullptr) {
            cout << atual->nome << "\n";
            atual = atual->prox;
        }
    }

    ~ListaMedicos() {
        char nome[256];
        while (chamarMedico(nome)) {}
    }
};
