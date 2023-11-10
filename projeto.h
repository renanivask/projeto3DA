#ifndef PROJETO_H
#define PROJETO_H

// Renan Ivaskevicius Vieira - 24.123.069-7

enum Estado {
    NAO_INICIADO,
    EM_ANDAMENTO,
    COMPLETO
};

struct Tarefa {
    int prioridade;
    char categoria[100];
    char descricao[300];
    enum Estado estado;
};
// cria a struct, que será retomada no arquivo main.c

void limpa();
// declara a funcao que excluira o conteudo da variavel para armazenar novos
void ler(struct Tarefa *armazena);
// declara a funcao que escreve no arquivo binario as tarefas do usuario
void excluir_tarefa(struct Tarefa *tarefas, int *cont, int posicao);
// declara a funcao que sera usada para apagar tarefas do arquivo binario

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Alterar tarefas.
void alterar_tarefa(struct Tarefa *tarefas, int cont);

// Filtrar tarefas por prioridade.
void filtrar_por_prioridade(struct Tarefa *tarefas, int cont, int prioridade);

// Filtra tarefas por estado.
void filtrar_por_estado(struct Tarefa *tarefas, int cont, enum Estado estado);

// Filtrar tarefas por categoria.
void filtrar_por_categoria(struct Tarefa *tarefas, int cont, const char *categoria);

// Filtrar tarefas por prioridade e categoria.
void filtrar_por_prioridade_e_categoria(struct Tarefa *tarefas, int cont, const char *categoria, int prioridade);

// Exportar por prioridade.
void exportar_por_prioridade(struct Tarefa *tarefas, int cont, int prioridade);

// Exportar por categoria.
void exportar_por_categoria(struct Tarefa *tarefas, int cont, const char *categoria);

#endif // PROJETO_H
