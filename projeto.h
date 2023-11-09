#ifndef PROJETO_H
#define PROJETO_H

// Renan Ivaskevicius Vieira - 24.123.069-7

struct Tarefa {
  int prioridade;
  char categoria[100];
  char descricao[300];
};
// cria a struct, que será retomada no arquivo main.c

void limpa();
// declara a funcao que excluira o conteudo da variavel para armazenar novos
void ler(struct Tarefa *armazena);
// declara a funcao que escreve no arquivo binario as tarefas do usuario
void excluir_tarefa(struct Tarefa *tarefas, int *cont, int posicao);
// declara a funcao que sera usada para apagar tarefas do arquivo binario

#endif // PROJETO_H
