#ifndef BIB_H_INCLUDED
#define BIB_H_INCLUDED
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "inOut.h"

typedef struct
{
    char livro_titulo[51];
    int disponibilidade;
} Biblioteca;

typedef struct
{
    int inicio,fim,nLivros;
}indice;

indice* OrganizaEstantes(int nEstantes,int nLivros,int N);
void fazConsulta(int nConsultas,indice* index);
void criaIndice(indice *index,int nEstantes,int eOcupadas);
void pesquisaBin(indice index,char* tituloLivro,int i);

#endif // BIB_H_INCLUDED
