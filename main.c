#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto.h"

//Renan Ivaskevicius Vieira - 24.123.069-7

int main() {
    // abre o arquivo binário e anuncia a struct que será utilizada para armazenar as tarefas
    struct Tarefa t[100];
    FILE *arquivo_binario = fopen("tarefas.txt", "rb");
    int cont = 0;
    if (arquivo_binario) {
        while (fread(&t[cont], sizeof(struct Tarefa), 1, arquivo_binario) == 1) {
            cont++;
        }
        fclose(arquivo_binario);
    }

    int posicao = 0;

    while (1) {
        printf(" 1 - Criar\n");
        printf(" 2 - Excluir\n");
        printf(" 3 - Listar\n");
        printf(" 4 - Sair\n");
        printf("Escreva apenas o numero da opcao que deseja: ");
        // denomina as opcoes a serem utilizadas
        char *p, s_opcao[100];
        char *p_posicao, s_posicao[100];
        int opcao;
        fgets(s_opcao, sizeof(s_opcao), stdin);
        opcao = strtol(s_opcao, &p, 10);

        if (opcao == 1) {
            ler(&t[cont]);
            printf("Tarefa criada!\n\n");
            cont++;
            // escreve no arquivo, chamando a funcao 1
        } else if (opcao == 2) {
            printf("Digite o numero da tarefa que deseja excluir: ");
            fgets(s_posicao, sizeof(s_posicao), stdin);
            posicao = strtol(s_posicao, &p_posicao, 10);
            if (p_posicao == s_posicao || *p_posicao != '\n') {
                printf("Nao foi possivel, tente novamente!\n\n");
            } else {
                excluir_tarefa(t, &cont, posicao);
                // apaga a tarefa desejada, chamando a funcao 2
        }
        } else if (opcao == 3) {
            printf("Lista:\n\n");
            for (int x = 0; x < cont; x++) {
                printf("Nome da tarefa: %d\n", x + 1);
                printf("Prioridade: %d\n", t[x].prioridade);
                printf("Categoria: %s\n", t[x].categoria);
                printf("Descricao: %s\n\n", t[x].descricao);
            }
            // le e printa todas as tarefas do arquivo, chamando a opcao 3
        } else if (opcao == 4) {
            arquivo_binario = fopen("tarefas.txt", "wb");
            if (arquivo_binario) {
                fwrite(t, sizeof(struct Tarefa), cont, arquivo_binario);
                fclose(arquivo_binario);
            }
            printf("Ate logo\n");
            break;
            // fecha o arquivo e encerra o programa
        } else {
            printf("Por favor, digite um valor entre 1 - 4.\n");
        }
    }

    return 0;
}
