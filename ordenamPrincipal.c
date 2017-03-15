#include "ordenamPrincipal.h"
void ordenaInterno(Biblioteca *livro, int tamanho )
{
    int i=0, j=0;
    unsigned int atual_disponibilidade=0;
    char stringAtual[51];

    for ( i = 1; i < tamanho; i++ )
    {
        strcpy(stringAtual,livro[i].livro_titulo);
        atual_disponibilidade = livro[i].disponibilidade;
        j = i - 1;
        while ( j >=0 && strcmp(stringAtual,livro[j].livro_titulo)<0)
        {
            livro[j+1] = livro[j];
            j--;
        }
        strcpy(livro[j+1].livro_titulo,stringAtual);
        livro[j+1].disponibilidade = atual_disponibilidade;
    }
}


