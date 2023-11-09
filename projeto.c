#include "projeto.h"
#include <stdio.h>

//Renan Ivaskevicius Vieira - 24.123.069-7

void limpa() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
// para o bem do decorrer do codigo, criamos essa funcao para apagar o conteudo da variavel de contagem

void ler(struct Tarefa *armazena) {
    printf("Prioridade: ");
    scanf("%d", &armazena->prioridade);
    limpa();
    printf("Descricao: ");
    scanf("%299[^\n]", armazena->descricao);
    limpa();
    printf("Categoria: ");
    scanf("%99[^\n]", armazena->categoria);
    limpa();
}
// essa funcao le o que foi digitado pelo usuario e escreve no arquivo binario

void excluir_tarefa(struct Tarefa *tarefas, int *cont, int posicao) {
    if (posicao >= 1 && posicao <= *cont) {
        for (int i = posicao - 1; i < *cont - 1; i++) {
            tarefas[i] = tarefas[i + 1];
        }
        (*cont)--;
        printf("Tarefa deletada\n\n");
    }
}
// essa funcao exclui uma tarefa desejada do arquivo binario

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Filtrar tarefas por prioridade
void filtrar_por_prioridade(struct Tarefa *tarefas, int cont, int prioridade) {
    printf("Tarefas com prioridade %d:\n", prioridade);
    
  // Variável usada para controle da condição da existência de tarefas com a prioridade descrita.
    int encontrou = 0;

  // Loop para percorrer o vetor de tarefas e imprimir as tarefas com a prioridade descrita.
    for (int i = 0; i < cont; i++) {
        if (tarefas[i].prioridade == prioridade) {
            printf("Nome da tarefa: %d\n", i + 1);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Descricao: %s\n\n", tarefas[i].descricao);
            encontrou = 1;
        }
    }

  // Caso não encontre tarefas com a prioridade descrita, imprime uma mensagem de erro.
    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com prioridade %d.\n\n", prioridade);
    }
}
