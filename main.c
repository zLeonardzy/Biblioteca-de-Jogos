#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[100];
    char genero[20];
    int ano;
} Jogo;

// Funções auxiliares
void salvarDados(Jogo *jogos, int n);
int carregarDados(Jogo *jogos);
void cadastrarJogos(Jogo *jogos, int *n);
void pesquisarJogos(Jogo *jogos, int n);
void listarJogos(Jogo *jogos, int n);
void menu();

#define ARQUIVO "jogos.dat"
#define MAX_JOGOS 100

int main()
{
    Jogo jogos[MAX_JOGOS];
    int n = 0; // Quantidade de jogos cadastrados

    // Carrega dados do arquivo, se existirem
    n = carregarDados(jogos);

    int opcao;
    do
    {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do teclado

        switch (opcao)
        {
        case 1:
            cadastrarJogos(jogos, &n);
            break;
        case 2:
            pesquisarJogos(jogos, n);
            break;
        case 3:
            listarJogos(jogos, n);
            break;
        case 4:
            printf("Saindo do sistema...\n");
            salvarDados(jogos, n);
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}

// Função para exibir o menu
void menu()
{
    printf("\n=== Sistema de Gerenciamento de Jogos ===\n");
    printf("1. Cadastrar Jogo\n");
    printf("2. Pesquisar Jogo\n");
    printf("3. Listar Jogos\n");
    printf("4. Sair\n");
    printf("=========================================\n");
}

// Função para salvar os dados em arquivo
void salvarDados(Jogo *jogos, int n)
{
    FILE *file = fopen(ARQUIVO, "wb");
    if (file == NULL)
    {
        printf("Erro ao salvar os dados.\n");
        return;
    }
    fwrite(jogos, sizeof(Jogo), n, file);
    fclose(file);
    printf("Dados salvos com sucesso!\n");
}

// Função para carregar os dados do arquivo
int carregarDados(Jogo *jogos)
{
    FILE *file = fopen(ARQUIVO, "rb");
    if (file == NULL)
    {
        printf("Nenhum dado encontrado. Iniciando com lista vazia.\n");
        return 0;
    }
    int n = fread(jogos, sizeof(Jogo), MAX_JOGOS, file);
    fclose(file);
    printf("Dados carregados com sucesso!\n");
    return n;
}

// Função para cadastrar um novo Jogo
void cadastrarJogos(Jogo *jogos, int *n)
{
    if (*n >= MAX_JOGOS)
    {
        printf("Limite de jogos atingido.\n");
        return;
    }
    Jogo novoJogo;

    printf("Digite o nome do jogo: ");
    fgets(novoJogo.nome, sizeof(novoJogo.nome), stdin);
    novoJogo.nome[strcspn(novoJogo.nome, "\n")] = 0; // Remover o '\n'

    printf("Digite o genero do jogo: ");
    fgets(novoJogo.genero, sizeof(novoJogo.genero), stdin);
    novoJogo.genero[strcspn(novoJogo.genero, "\n")] = 0;

    printf("Digite o ano do jogo: ");
    scanf("%d", &novoJogo.ano);
    getchar(); // Limpar buffer

    jogos[*n] = novoJogo;
    (*n)++;
    printf("Jogo cadastrado com sucesso!\n");
}

// Função para pesquisar um jogo pelo nome
void pesquisarJogos(Jogo *jogos, int n)
{
    char busca[100];
    printf("Digite o nome do jogo para pesquisar: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = 0;

    for (int i = 0; i < n; i++)
    {
        if (strcmp(jogos[i].nome, busca) == 0)
        {
            printf("\nJogo encontrado:\n");
            printf("Nome: %s\n", jogos[i].nome);
            printf("Ano: %d\n", jogos[i].ano);
            printf("Gênero: %s\n", jogos[i].genero);
            return;
        }
    }
    printf("Jogo não encontrado.\n");
}

// Função para listar os jogos cadastrados
void listarJogos(Jogo *jogos, int n)
{
    if (n == 0)
    {
        printf("Nenhum jogo cadastrado.\n");
        return;
    }
    printf("\n=== Lista de jogos ===\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d. Nome: %s | Ano: %d | Genero: %s\n",
               i + 1, jogos[i].nome, jogos[i].ano, jogos[i].genero);
    }
}
