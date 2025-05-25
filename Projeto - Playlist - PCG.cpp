#include <stdio.h> // Biblioteca padrão para entrada e saída (ex: printf, scanf)
#include <string.h> // Biblioteca para manipular strings (ex: strcpy, strcmp)

#define MAX_GENEROS 6 // Número máximo de gêneros musicais
#define MAX_MUSICAS 100 // Número máximo de músicas que podem ser armazenadas

// Função para trocar dois elementos (nomes e durações) de lugar
void swap(char *str1, char *str2, int *dur1, int *dur2) {
    char temp_str[100]; // Variável temporária para guardar um nome ou gênero
    int temp_dur; // Variável temporária para guardar a duração

    // Troca os textos (nomes ou gêneros)
    strcpy(temp_str, str1);
    strcpy(str1, str2);
    strcpy(str2, temp_str);

     // Troca as durações
    temp_dur = *dur1;
    *dur1 = *dur2;
    *dur2 = temp_dur;
}

// Função para ordenar a playlist por ordem alfabética dos nomes das músicas
void sort_playlist(char nomes[][100], char generos[][50], int duracoes[], int quantidade) {
    int i, j;
    for (i = 0; i < quantidade - 1; i++) {
        for (j = 0; j < quantidade - i - 1; j++) {
            // Compara nomes e troca se estiverem fora de ordem
            if (strcmp(nomes[j], nomes[j + 1]) > 0) {
                swap(nomes[j], nomes[j + 1], &duracoes[j], &duracoes[j + 1]);
                swap(generos[j], generos[j + 1], &duracoes[j], &duracoes[j + 1]);
            }
        }
    }
}

int main() {
    char nomes[MAX_MUSICAS][100]; // Armazena os nomes das músicas
    char generos[MAX_MUSICAS][50]; // Armazena os gêneros das músicas
    int duracoes[MAX_MUSICAS]; // Armazena a duração das músicas (em segundos)
    int quantidade = 0; // Conta quantas músicas já foram adicionadas
    int opcao; // Guarda a opção escolhida no menu
    int i, j; // Contadores para loops

    char generos_preestabelecidos[MAX_GENEROS][50] = {
        "Eletronica",
        "Funk",
        "Rock",
        "Jazz",
        "Pop",
        "Hip-Hop"
    };

    do {
        // Mostra as opções do menu
        printf("\n----- Menu -----\n");
        printf("1. Adicionar musica\n");
        printf("2. Listar musicas\n");
        printf("3. Montar playlist por tempo maximo\n");
        printf("4. Montar playlist por genero\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao); // Lê a escolha do usuário

        if (opcao == 1) {
            if (quantidade >= MAX_MUSICAS) { // Verifica se já chegou ao limite
                printf("A playlist esta cheia!\n");
            } else {
                printf("Digite o nome da musica: ");
                scanf(" %[^\n]s", nomes[quantidade]); // Lê o nome da música com espaços

                printf("Escolha o genero:\n");
                for (i = 0; i < MAX_GENEROS; i++) {
                    printf("%d. %s\n", i + 1, generos_preestabelecidos[i]);
                }
                printf("Escolha uma opcao de genero (1-%d): ", MAX_GENEROS);
                int genero_opcao;
                scanf("%d", &genero_opcao);

                if (genero_opcao >= 1 && genero_opcao <= MAX_GENEROS) {
                    // Copia o gênero escolhido para a lista
                    strcpy(generos[quantidade], generos_preestabelecidos[genero_opcao - 1]);
                } else {
                    // Se o usuário digitar um número inválido
                    printf("Opcao de genero invalida. Genero nao atribuido.\n");
                    strcpy(generos[quantidade], "Indefinido");
                }

                printf("Digite a duracao (em segundos): ");
                scanf("%d", &duracoes[quantidade]); // Lê a duração

                quantidade++; // Adiciona 1 à quantidade total de músicas
                printf("Musica adicionada com sucesso!\n");
            }

        } else if (opcao == 2) {
            if (quantidade == 0) {
                printf("A playlist esta vazia.\n");
            } else {
                sort_playlist(nomes, generos, duracoes, quantidade); // Ordena músicas por nome

                printf("\n--- Playlist ---\n");
                for (i = 0; i < quantidade; i++) {
                    printf("Musica %d:\n", i + 1);
                    printf("Nome: %s\n", nomes[i]);
                    printf("Genero: %s\n", generos[i]);
                    printf("Duracao: %d minutos\n\n", duracoes[i] / 60); // Converte segundos em minutos
                }
            }

        } else if (opcao == 3) {
            int tempo_maximo_minutos;
            printf("Digite o tempo maximo da playlist (em minutos): ");
            scanf("%d", &tempo_maximo_minutos);
            int tempo_maximo = tempo_maximo_minutos * 60; // Converte para segundos

            // Ordena músicas
            sort_playlist(nomes, generos, duracoes, quantidade);

            int tempo_total = 0;
            printf("\n--- Playlist por Tempo Maximo ---\n");
            for (i = 0; i < quantidade; i++) {
                if (tempo_total + duracoes[i] <= tempo_maximo) {
                    printf("Musica %d:\n", i + 1);
                    printf("Nome: %s\n", nomes[i]);
                    printf("Genero: %s\n", generos[i]);
                    printf("Duracao: %d minutos\n\n", duracoes[i] / 60);
                    tempo_total += duracoes[i];
                }
            }
            printf("Tempo total da playlist: %d minutos\n", tempo_total / 60);

        } else if (opcao == 4) {
            int generos_escolhidos[MAX_GENEROS] = {0}; // Vetor para marcar quais gêneros foram escolhidos
            int genero_opcao;

            printf("Escolha os generos para a playlist (digite 0 para terminar):\n");
            for (i = 0; i < MAX_GENEROS; i++) {
                printf("%d. %s\n", i + 1, generos_preestabelecidos[i]);
            }

            while (1) {
                printf("Escolha uma opcao de genero (1-%d) ou 0 para terminar: ", MAX_GENEROS);
                scanf("%d", &genero_opcao);

                if (genero_opcao == 0) {
                    break; // Sai do loop se o usuário digitar 0
                }

                if (genero_opcao >= 1 && genero_opcao <= MAX_GENEROS) {
                    generos_escolhidos[genero_opcao - 1] = 1;
                    printf("Genero %s adicionado à playlist.\n", generos_preestabelecidos[genero_opcao - 1]);
                } else {
                    printf("Opcao invalida! Tente novamente.\n");
                }
            }

            sort_playlist(nomes, generos, duracoes, quantidade);

            printf("\n--- Playlist por Generos Escolhidos ---\n");
            int tempo_total = 0;
            for (i = 0; i < quantidade; i++) {
                for (j = 0; j < MAX_GENEROS; j++) {
                    if (generos_escolhidos[j] == 1 && strcmp(generos[i], generos_preestabelecidos[j]) == 0) {
                        printf("Musica %d:\n", i + 1);
                        printf("Nome: %s\n", nomes[i]);
                        printf("Genero: %s\n", generos[i]);
                        printf("Duracao: %d minutos\n\n", duracoes[i] / 60);
                        tempo_total += duracoes[i];
                        break; // Sai do loop interno após encontrar o gênero
                    }
                }
            }
            printf("Tempo total da playlist: %d minutos\n", tempo_total / 60);

        } else if (opcao == 5) {
            printf("Saindo do programa...\n");
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 5); // Repete o menu até a opção ser 5 (sair)

    return 0; // Encerra o programa
}
