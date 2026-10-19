# Sistema de Atendimento Hospitalar

Trabalho de C++ para cadastrar pacientes e médicos e organizar os atendimentos.

Os pacientes são atendidos por ordem de chegada. Depois de atender, o médico volta para o final da lista. Os atendimentos ficam guardados no histórico, que pode ser mostrado sem apagar os registros.

Foram usadas uma fila para os pacientes, uma pilha para o histórico e uma lista encadeada para os médicos, com `new` e `delete`, sem STL.

## Como rodar

Com o g++ instalado, abra o terminal na pasta do projeto e execute:

```powershell
g++ -std=c++17 -Wall -o atendimento.exe atendimento_template.cpp
.\atendimento.exe
```

## Como usar

No menu, cadastre os médicos e os pacientes. Para cada paciente, informe a urgência: 1 para baixa, 2 para média ou 3 para alta. A urgência fica registrada, mas a fila continua seguindo a ordem de chegada.

Use a opção 3 para atender e a opção 7 para ver o histórico. A opção 0 encerra o programa. Os dados não ficam salvos depois de fechar.

## Exemplo de saída

Com os médicos Carlos e Maria e os pacientes Ana e Bruno cadastrados nessa ordem, os atendimentos aparecem assim:

```text
Paciente: Ana | Urgencia: 1 | Medico: Carlos
Paciente: Bruno | Urgencia: 3 | Medico: Maria
```

No histórico, o atendimento mais recente aparece primeiro:

```text
--- Historico (mais recente primeiro) ---
Paciente: Bruno | Urgencia: 3 | Medico: Maria
Paciente: Ana | Urgencia: 1 | Medico: Carlos
```
