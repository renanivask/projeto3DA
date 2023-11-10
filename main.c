#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto.h"

// Renan Ivaskevicius Vieira - 24.123.069-7

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
        printf(" 4 - Alterar tarefas\n");
        printf(" 5 - Filtrar Tarefas por Prioridade\n");
        printf(" 6 - Filtrar Tarefas por Estado\n");
        printf(" 7 - Filtrar Tarefas por Categoria\n");
        printf(" 8 - Filtrar Tarefas por Prioridade e Categoria\n");
        printf(" 9 - Exportar Tarefas por Prioridade\n");
        printf(" 10 - Exportar Tarefas por Categoria\n");
        printf(" 11 - Exportar Tarefas por Prioridade e Categoria\n");
        printf(" 12 - Sair\n");
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
                printf("Descricao: %s\n", t[x].descricao);

                switch (t[x].estado) {
                    case NAO_INICIADO:
                        printf("Estado: Não Iniciado\n\n");
                        break;
                    case EM_ANDAMENTO:
                        printf("Estado: Em Andamento\n\n");
                        break;
                    case COMPLETO:
                        printf("Estado: Completo\n\n");
                        break;
                    default:
                        printf("Estado: Desconhecido\n\n");
                        break;
                }
            }
            // le e printa todas as tarefas do arquivo, chamando a opcao 3
        }

          
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        // Alterar tarefas.
        else if (opcao == 4) {
              alterar_tarefa(t, cont);
        }
          
        // Filtrar tarefas por prioridade.
        else if (opcao == 5) {
                printf("Digite a prioridade para filtrar as tarefas: ");
                int prioridade_filtro;
                // Recebe a prioridade que o usuário deseja filtrar.
                fgets(s_posicao, sizeof(s_posicao), stdin);
                prioridade_filtro = strtol(s_posicao, &p_posicao, 10);

                // Verifica se a prioridade digitada é válida.
                if (p_posicao == s_posicao || *p_posicao != '\n') {
                    printf("Digite um valor válido para a prioridade.\n\n");
                } else {
                    filtrar_por_prioridade(t, cont, prioridade_filtro);
                }
          }

          // Filtra tarefas por estado.
          else if (opcao == 6) {
              printf("Digite o estado para filtrar as tarefas: ");
              int estado_filtro;
              fgets(s_posicao, sizeof(s_posicao), stdin);
              estado_filtro = strtol(s_posicao, &p_posicao, 10);

              if (p_posicao == s_posicao || *p_posicao != '\n') {
                  printf("Digite um valor válido para o estado.\n\n");
              } else {
                  filtrar_por_estado(t, cont, estado_filtro);
              }
          }

          // Filtra tarefas por categoria.  
          else if (opcao == 7) {
              // Recebe a categoria que o usuário deseja filtrar.
              char categoria_filtro[100];
              printf("Digite a categoria para filtrar as tarefas: ");
              fgets(categoria_filtro, sizeof(categoria_filtro), stdin);
            
              // Remover a quebra de linha do final da categoria
              categoria_filtro[strcspn(categoria_filtro, "\n")] = '\0';
              filtrar_por_categoria(t, cont, categoria_filtro);
          }

          // Filtrar tarefas por prioridade e categoria.
          else if (opcao == 8) {
              char categoria_filtro[100];
              int prioridade_filtro;

              printf("Digite a categoria para filtrar as tarefas: ");
              fgets(categoria_filtro, sizeof(categoria_filtro), stdin);
              // Remover a quebra de linha do final da categoria
              categoria_filtro[strcspn(categoria_filtro, "\n")] = '\0';

              printf("Digite a prioridade para filtrar as tarefas: ");
              fgets(s_posicao, sizeof(s_posicao), stdin);
              prioridade_filtro = strtol(s_posicao, &p_posicao, 10);

              // Verifica se a prioridade digitada é válida.
              if (p_posicao == s_posicao || *p_posicao != '\n') {
                  printf("Digite um valor válido para a prioridade.\n\n");
              } else {
                  filtrar_por_prioridade_e_categoria(t, cont, categoria_filtro, prioridade_filtro);
              }
          }

          // Exportar por prioridade.
          else if (opcao == 9) {
              int prioridade_exportar;

              // Recebe a prioridade que o usuário deseja exportar.
              printf("Digite a prioridade das tarefas que deseja exportar: ");
              fgets(s_posicao, sizeof(s_posicao), stdin);
              prioridade_exportar = strtol(s_posicao, &p_posicao, 10);

              // Verifica se a prioridade digitada é válida.
              if (p_posicao == s_posicao || *p_posicao != '\n') {
                  printf("Digite um valor válido para a prioridade.\n\n");
              } else {
                  exportar_por_prioridade(t, cont, prioridade_exportar);
              }
          }

          // Exportar por categoria.
          else if (opcao == 10) {
              char categoria_exportar[100];

              // Recebe a categoria que o usuário deseja exportar.
              printf("Digite a categoria das tarefas que deseja exportar: ");
              fgets(categoria_exportar, sizeof(categoria_exportar), stdin);
              
              // Remover a quebra de linha do final da categoria
              categoria_exportar[strcspn(categoria_exportar, "\n")] = '\0';

              // Exporta as tarefas da categoria escolhida.
              exportar_por_categoria(t, cont, categoria_exportar);
          }

          // Exportar por prioridade e categoria.
          else if (opcao == 11) {
              int prioridade_exportar;
              char categoria_exportar[100];

              // Recebe a prioridade que o usuário deseja exportar.
              printf("Digite a prioridade das tarefas que deseja exportar: ");
              fgets(s_posicao, sizeof(s_posicao), stdin);
              prioridade_exportar = strtol(s_posicao, &p_posicao, 10);

              // Verifica se a prioridade digitada é válida.
              if (p_posicao == s_posicao || *p_posicao != '\n') {
                  printf("Digite um valor válido para a prioridade.\n\n");
              } else {
                  printf("Digite a categoria das tarefas que deseja exportar: ");
                  fgets(categoria_exportar, sizeof(categoria_exportar), stdin);
                
                  // Remover a quebra de linha do final da categoria
                  categoria_exportar[strcspn(categoria_exportar, "\n")] = '\0';

                  // Exporta as tarefas da prioridade e categoria escolhida.
                  exportar_por_prioridade_e_categoria(t, cont, prioridade_exportar, categoria_exportar);
              }
          }

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        else if (opcao == 12) {
            arquivo_binario = fopen("tarefas.txt", "wb");
            if (arquivo_binario) {
                fwrite(t, sizeof(struct Tarefa), cont, arquivo_binario);
                fclose(arquivo_binario);
            }
            printf("Ate logo\n");
            break;
            // fecha o arquivo e encerra o programa
        } else {
            printf("Por favor, digite um valor entre 1 - 5.\n");
        }
    }

    return 0;
}
