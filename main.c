#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXIMO_DE_LIVROS 30
#define MAXIMO_DE_CARACTERES 100
#define TAMANHO_ISBN 14

typedef struct
{
  char isbn[TAMANHO_ISBN];
  char titulo[MAXIMO_DE_CARACTERES];
  char autor[MAXIMO_DE_CARACTERES];
  int disponivel;
} Livro;

int livroExiste(Livro arr[MAXIMO_DE_LIVROS], char isbn[TAMANHO_ISBN], int livrosCadastrados)
{
  for (int i = 0; i < livrosCadastrados; i++)
  {
    if (strcmp(arr[i].isbn, isbn) == 0)
      return i;
  }
  return -1;
}

void limpa()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void proximo()
{
  printf("\nPressione enter para continuar...");
  while ((getchar()) != '\n' && getchar() != EOF)
    ;
  char ch = getchar();

  limpa();
}

int main()
{
  Livro livros[MAXIMO_DE_LIVROS];
  int livrosCadastrados = 0;

  int opcao;

  do
  {
    printf("############################\n");
    printf("######## BIBLIOTECA ########\n");
    printf("############################\n\n");
    printf("1 - Cadastrar livro\n");
    printf("2 - Devolver livro\n");
    printf("3 - Emprestar livro\n");
    printf("4 - Listar livros\n");
    printf("0 - Sair\n");
    printf("Opção: ");
    scanf("%i", &opcao);

    limpa();

    switch (opcao)
    {
    case 1:
    {
      int quantidade;

      printf("Informe a quantidade de livros que você irá cadastrar: ");
      scanf("%d", &quantidade);

      while (quantidade <= 0 || (livrosCadastrados + quantidade) > MAXIMO_DE_LIVROS)
      {
        printf("Quantidade inválida. Informe um valor entre 1 e %d: ", MAXIMO_DE_LIVROS - livrosCadastrados);
        scanf("%d", &quantidade);
      }

      limpa();

      for (int i = 0; i < quantidade; i++)
      {
        char isbn[14];
        char titulo[MAXIMO_DE_CARACTERES];
        char autor[MAXIMO_DE_CARACTERES];
        int disponivel = 1;

        printf("Livro #%d\n", livrosCadastrados + 1);

        printf("Informe o ISBN do livro (13 caracteres): ");
        scanf("%s", isbn);

        while (strlen(isbn) != 13)
        {
          printf("ISBN inválido. Informe exatamente 13 caracteres: ");
          scanf("%s", isbn);
        }

        if (livroExiste(livros, isbn, livrosCadastrados) != -1)
        {
          printf("Livro com este ISBN já cadastrado. Pulando...\n\n");
          continue;
        }

        printf("Informe o título do livro: ");
        getchar(); // limpa buffer do teclado
        scanf(" %[^\n]", titulo);

        while (strlen(titulo) >= MAXIMO_DE_CARACTERES)
        {
          printf("O título não pode conter mais que %d caracteres. Tente novamente: ", MAXIMO_DE_CARACTERES - 1);
          scanf(" %[^\n]", titulo);
        }

        printf("Informe o autor do livro: ");
        scanf(" %[^\n]", autor);

        while (strlen(autor) >= MAXIMO_DE_CARACTERES)
        {
          printf("O nome do autor não pode conter mais que %d caracteres. Tente novamente: ", MAXIMO_DE_CARACTERES - 1);
          scanf(" %[^\n]", autor);
        }

        Livro *livro = &livros[livrosCadastrados];

        strcpy(livro->isbn, isbn);
        strcpy(livro->titulo, titulo);
        strcpy(livro->autor, autor);
        livro->disponivel = disponivel;

        livrosCadastrados++;

        printf("Livro cadastrado com sucesso!\n");
        proximo();
      }
    }
    break;

    case 2:
      limpa();

      if (livrosCadastrados == 0)
      {
        printf("Nenhum livro cadastrado ainda.\n\n");
        proximo();
        break;
      }

      char isbn[TAMANHO_ISBN];

      printf("Informe o ISBN do livro para devolver: ");
      scanf("%s", isbn);

      int indice = livroExiste(livros, isbn, livrosCadastrados);

      if (indice == -1)
      {
        limpa();
        printf("Livro não encontrado.\n");
        proximo();
      }
      else
      {
        Livro *livro = &livros[indice];

        if (livro->disponivel == 1)
        {
          printf("Livro \"%s\" já foi devolvido.\n", livro->titulo);
          proximo();
        }
        else
        {
          livro->disponivel = 1;
          printf("Livro \"%s\" devolvido com sucesso!\n", livro->titulo);
          proximo();
        }
      }

      break;

    case 3:
    {
      limpa();

      if (livrosCadastrados == 0)
      {
        printf("Nenhum livro cadastrado ainda.\n\n");
        proximo();
        break;
      }

      char isbn[TAMANHO_ISBN];

      printf("Informe o ISBN do livro para empréstimo: ");
      scanf("%s", isbn);

      int livroIndice = livroExiste(livros, isbn, livrosCadastrados);
      if (livroIndice == -1)
      {
        limpa();
        printf("Livro não encontrado.\n");
        proximo();
      }
      else
      {
        Livro *livro = &livros[livroIndice];

        if (!livro->disponivel)
        {
          limpa();
          printf("Livro '%s' está indisponível no momento.\n\n", livro->titulo);
          proximo();
        }
        else
        {
          livro->disponivel = 0;
          limpa();
          printf("Livro '%s' emprestado com sucesso.\n", livro->titulo);
          proximo();
        }
      }
    }
    break;

    case 4:
      limpa();

      if (livrosCadastrados == 0)
      {
        printf("Nenhum livro cadastrado ainda.\n\n");
        proximo();
        break;
      }

      getchar(); // limpa buffer do teclado

      char opcao;

      printf("Deseja listar apenas livros disponíveis?[s/n] ");
      scanf("%c", &opcao);

      limpa();

      if (opcao == 'S' || opcao == 's')
      {
        int nenhumLivroDisponivel = 1;

        printf("Livros disponíveis:\n");

        for (int i = 0; i < livrosCadastrados; i++)
        {
          if (livros[i].disponivel == 1)
          {
            nenhumLivroDisponivel = 0;

            printf("Livro #%i\n\n", i + 1);
            printf("ISBN: %s\n", livros[i].isbn);
            printf("Título: %s\n", livros[i].titulo);
            printf("Autor: %s\n", livros[i].autor);
          }
        }
        if (nenhumLivroDisponivel)
        {
          printf("Nenhum livro está disponível\n");
        }
      }
      else
      {
        for (int i = 0; i < livrosCadastrados; i++)
        {
          printf("Livro #%i\n\n", i + 1);
          printf("ISBN: %s\n", livros[i].isbn);
          printf("Título: %s\n", livros[i].titulo);
          printf("Autor: %s\n", livros[i].autor);
          if (livros[i].disponivel == 1)
          {
            printf("Disponível: Sim\n");
          }
          else
          {
            printf("Disponível: Não\n");
          }
        }
      }

      proximo();
      break;

    case 0:
      printf("Saindo...\n");
      break;

    default:
      printf("Opção inválida.\n");
      proximo();
      break;
    }

  } while (opcao != 0);

  return 0;
}
