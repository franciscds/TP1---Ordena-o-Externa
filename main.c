#include "inOut.h"
#include "bib.h"
#include "ordenaExt.h"

int main()
{
    parametro op;
    getParametros(&op);//Parametros N,M,E,L,K
    indice *index;

    le_escreveEntrada(op.N);//Le entrada e salva entrada em arquivo
    OrdenaExterno(op.M-1,op.N);
    index = OrganizaEstantes(op.E,op.L,op.N); //escreve livros nas estantes;
    fazConsulta(op.K,index);

    free(index);
    index = NULL;
    return 0;
}
