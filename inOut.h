#ifndef INOUT_H_INCLUDED
#define INOUT_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct op
{
    int N,M,E,L,K;
}parametro;

void getParametros(parametro *op);
void le_escreveEntrada(int N);


#endif // INOUT_H_INCLUDED
