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
