#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

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

    void push(const char* nome) {
        No* novo = new No;
        strcpy(novo->nome, nome);
        novo->urgencia = 0;
        novo->prox = topo;
        topo = novo;
    }

    bool pop(char* nome) {
        if (topo == nullptr) return false;
        No* antigo = topo;
        strcpy(nome, antigo->nome);
        topo = topo->prox;
        delete antigo;
        return true;
    }

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

    bool chamarMedico(char* nome) {
        if (inicio == nullptr) return false;
        No* antigo = inicio;
        strcpy(nome, antigo->nome);
        inicio = inicio->prox;
        delete antigo;
        return true;
    }

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

void imprimirHistorico(Pilha& historico) {
    if (historico.peek() == nullptr) {
        cout << "Historico vazio.\n";
        return;
    }
    Pilha auxiliar;
    char registro[256];
    cout << "--- Historico (mais recente primeiro) ---\n";
    while (historico.pop(registro)) {
        cout << registro << "\n";
        auxiliar.push(registro);
    }
    while (auxiliar.pop(registro)) {
        historico.push(registro);
    }
}

bool lerNumero(int& numero) {
    while (!(cin >> numero)) {
        if (cin.eof()) return false;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Digite um numero: ";
    }
    cin.ignore(10000, '\n');
    return true;
}

bool lerNome(char* nome) {
    while (true) {
        cin.getline(nome, 100);
        if (cin.eof()) return false;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Nome muito longo. Use ate 99 caracteres: ";
        } else if (nome[0] == '\0' || strspn(nome, " \t\r") == strlen(nome)) {
            cout << "O nome nao pode ficar vazio. Digite novamente: ";
        } else {
            return true;
        }
    }
}

int main() {
    Fila pacientes;
    Pilha historico;
    ListaMedicos medicos;
    int opcao;
    int urgencia;
    char nome[256];
    char medico[256];
    char registro[256];

    while (true) {
        cout << "\n=== Atendimento Hospitalar ===\n"
             << "1 - Cadastrar paciente\n"
             << "2 - Cadastrar medico\n"
             << "3 - Atender proximo paciente\n"
             << "4 - Consultar frente e tamanho da fila\n"
             << "5 - Listar medicos\n"
             << "6 - Consultar ultimo atendimento\n"
             << "7 - Imprimir historico\n"
             << "0 - Sair\nOpcao: ";
        if (!lerNumero(opcao) || opcao == 0) break;

        if (opcao == 1) {
            cout << "Nome do paciente: ";
            if (!lerNome(nome)) break;
            cout << "Urgencia (1=baixa, 2=media, 3=alta): ";
            if (!lerNumero(urgencia)) break;
            if (urgencia < 1 || urgencia > 3) {
                cout << "Urgencia invalida. Paciente nao cadastrado.\n";
            } else {
                pacientes.enqueue(nome, urgencia);
                cout << "Paciente cadastrado.\n";
            }
        } else if (opcao == 2) {
            cout << "Nome do medico: ";
            if (!lerNome(nome)) break;
            medicos.adicionarMedico(nome);
            cout << "Medico cadastrado.\n";
        } else if (opcao == 3) {
            if (pacientes.frente_peak() == nullptr) {
                cout << "Fila vazia.\n";
            } else if (!medicos.chamarMedico(medico)) {
                cout << "Nenhum medico cadastrado. Paciente continua na fila.\n";
            } else {
                pacientes.dequeue(nome, urgencia);
                snprintf(registro, sizeof(registro),
                         "Paciente: %.99s | Urgencia: %d | Medico: %.99s",
                         nome, urgencia, medico);
                historico.push(registro);
                cout << registro << "\n";
                medicos.adicionarMedico(medico);
            }
        } else if (opcao == 4) {
            const No* primeiro = pacientes.frente_peak();
            if (primeiro == nullptr) {
                cout << "Fila vazia.\n";
            } else {
                cout << "Proximo: " << primeiro->nome
                     << " | Urgencia: " << primeiro->urgencia << "\n";
            }
            cout << "Pacientes na fila: " << pacientes.tamanho() << "\n";
        } else if (opcao == 5) {
            medicos.percorrer();
        } else if (opcao == 6) {
            const No* ultimo = historico.peek();
            if (ultimo == nullptr) cout << "Historico vazio.\n";
            else cout << ultimo->nome << "\n";
        } else if (opcao == 7) {
            imprimirHistorico(historico);
        } else {
            cout << "Opcao invalida.\n";
        }
    }
    cout << "Sistema encerrado.\n";
    return 0;
}
