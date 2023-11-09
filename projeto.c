#include "projeto.h"
#include <stdio.h>

// Renan Ivaskevicius Vieira - 24.123.069-7

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
    printf("Estado (0 - Não Iniciado, 1 - Em Andamento, 2 - Completo): ");
    scanf("%d", (int*)&armazena->estado);
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

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


// Alterar tarefas
void alterar_tarefa(struct Tarefa *tarefas, int cont) {
    int posicao;
    char escolha[100];
    char novo_valor[300];

    // Solicitar a posição da tarefa a ser alterada.
    printf("Digite o numero da tarefa que deseja alterar: ");
    fgets(escolha, sizeof(escolha), stdin);
    posicao = strtol(escolha, NULL, 10);

    // Verifica se a posição é válida.
    if (posicao < 1 || posicao > cont) {
        printf("Tarefa nao encontrada.\n\n");
        return;
    }

    // Solicitar o campo a ser alterado.
    printf("Escolha o campo que deseja alterar:\n");
    printf("1 - Prioridade\n");
    printf("2 - Categoria\n");
    printf("3 - Descricao\n");
    printf("4 - Estado\n");

    int opcao;
    fgets(escolha, sizeof(escolha), stdin);
    opcao = strtol(escolha, NULL, 10);

    // Verifica se a opção é válida.
    if (opcao < 1 || opcao > 4) {
        printf("Opcao invalida.\n\n");
        return;
    }

    // Solicitar o novo valor.
    printf("Digite o novo valor: ");
    fgets(novo_valor, sizeof(novo_valor), stdin);

    // Remove a quebra de linha do final do novo valor.
    novo_valor[strcspn(novo_valor, "\n")] = '\0';

    // Altera o valor do campo escolhido.
    switch (opcao) {
        case 1:
            tarefas[posicao - 1].prioridade = atoi(novo_valor);
            break;
        case 2:
            strncpy(tarefas[posicao - 1].categoria, novo_valor, sizeof(tarefas[posicao - 1].categoria));
            break;
        case 3:
            strncpy(tarefas[posicao - 1].descricao, novo_valor, sizeof(tarefas[posicao - 1].descricao));
            break;
        case 4:
            tarefas[posicao - 1].estado = atoi(novo_valor);
            break;
    }

    printf("Tarefa alterada com sucesso.\n\n");
}



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


// Filtrar tarefas por estado.
void filtrar_por_estado(struct Tarefa *tarefas, int cont, enum Estado estado) {
    printf("Tarefas com estado %d:\n", estado);
    int encontrou = 0;

    // Loop para percorrer o vetor de tarefas e imprimir as tarefas com o estado descrito.
    for (int i = 0; i < cont; i++) {
        if (tarefas[i].estado == estado) {
            printf("Nome da tarefa: %d\n", i + 1);
            printf("Prioridade: %d\n", tarefas[i].prioridade);
            printf("Categoria: %s\n", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
            printf("Estado: %d\n\n", tarefas[i].estado);
            encontrou = 1;
        }
    }

    // Caso não encontre tarefas com o estado descrito, imprime uma mensagem de erro.
    if (!encontrou) {
        printf("Nenhuma tarefa encontrada com estado %d.\n\n", estado);
    }
}


// Filtrar tarefas por categoria.
// Função auxiliar para comparar as prioridades para ordenação
int comparar_prioridades(const void *a, const void *b) {
    return ((struct Tarefa*)b)->prioridade - ((struct Tarefa*)a)->prioridade;
}

void filtrar_por_categoria(struct Tarefa *tarefas, int cont, const char *categoria) {
    struct Tarefa tarefas_filtradas[100];
    int cont_filtradas = 0;

    // Filtrar tarefas pela categoria
    for (int i = 0; i < cont; i++) {
        if (strcmp(tarefas[i].categoria, categoria) == 0) {
            tarefas_filtradas[cont_filtradas++] = tarefas[i];
        }
    }

    // Ordenar tarefas filtradas por prioridade (da maior para a menor)
    qsort(tarefas_filtradas, cont_filtradas, sizeof(struct Tarefa), comparar_prioridades);

    // Imprimir tarefas filtradas
    printf("Tarefas na categoria '%s', ordenadas por prioridade (da maior para a menor):\n", categoria);
    for (int i = 0; i < cont_filtradas; i++) {
        printf("Prioridade: %d\n", tarefas_filtradas[i].prioridade);
        printf("Categoria: %s\n", tarefas_filtradas[i].categoria);
        printf("Descricao: %s\n", tarefas_filtradas[i].descricao);
        printf("Estado: %d\n\n", tarefas_filtradas[i].estado);
    }

    // Caso não encontre tarefas com a categoria descrita, imprime uma mensagem de erro.
    if (cont_filtradas == 0) {
        printf("Nenhuma tarefa encontrada na categoria '%s'.\n\n", categoria);
    }
}


// Filtrar tarefas por prioridade e categoria.
void filtrar_por_prioridade_e_categoria(struct Tarefa *tarefas, int cont, const char *categoria, int prioridade) {
    struct Tarefa tarefas_filtradas[100];
    int cont_filtradas = 0;

    // Filtrar tarefas pela categoria e prioridade
    for (int i = 0; i < cont; i++) {
        if (strcmp(tarefas[i].categoria, categoria) == 0 && tarefas[i].prioridade == prioridade) {
            tarefas_filtradas[cont_filtradas++] = tarefas[i];
        }
    }

    // Ordenar tarefas filtradas por prioridade (da maior para a menor)
    qsort(tarefas_filtradas, cont_filtradas, sizeof(struct Tarefa), comparar_prioridades);

    // Imprimir tarefas filtradas
    printf("Tarefas na categoria '%s' e com prioridade %d, ordenadas por prioridade (da maior para a menor):\n", categoria, prioridade);
    for (int i = 0; i < cont_filtradas; i++) {
        printf("Prioridade: %d\n", tarefas_filtradas[i].prioridade);
        printf("Categoria: %s\n", tarefas_filtradas[i].categoria);
        printf("Descricao: %s\n", tarefas_filtradas[i].descricao);
        printf("Estado: %d\n\n", tarefas_filtradas[i].estado);
    }

    if (cont_filtradas == 0) {
        printf("Nenhuma tarefa encontrada na categoria '%s' com prioridade %d.\n\n", categoria, prioridade);
    }
}


// Exportar por prioridade.
void exportar_por_prioridade(struct Tarefa *tarefas, int cont, int prioridade) {
    char nome_arquivo[100];
    FILE *arquivo_exportado;

    // Solicitar o nome do arquivo para exportar
    printf("Digite o nome do arquivo para exportar as tarefas: ");
    fgets(nome_arquivo, sizeof(nome_arquivo), stdin);
    // Remover a quebra de linha do final do nome do arquivo
    nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';

    // Abrir o arquivo para escrita
    arquivo_exportado = fopen(nome_arquivo, "w");

    if (arquivo_exportado == NULL) {
        printf("Erro ao abrir o arquivo para exportar as tarefas.\n\n");
        return;
    }

    // Escrever as tarefas da prioridade escolhida no arquivo
    for (int i = 0; i < cont; i++) {
        if (tarefas[i].prioridade == prioridade) {
            fprintf(arquivo_exportado, "%d, %s, %d, %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].estado, tarefas[i].descricao);
        }
    }

    // Fechar o arquivo
    fclose(arquivo_exportado);

    printf("Tarefas exportadas com sucesso para o arquivo '%s'.\n\n", nome_arquivo);
}
