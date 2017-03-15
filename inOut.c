#include "inOut.h"
#include "bib.h"

void getParametros(parametro* op)
{
    scanf("%d %d %d %d %d",&(op->N),&(op->M),&(op->E),&(op->L),&(op->K));
}
void le_escreveEntrada(int N)
{
    int count=0;
    Biblioteca livro_temp;
    FILE *fp = fopen("entrada.dat","wb");
    while( count < N)
    {
        scanf("%s %d",livro_temp.livro_titulo,&livro_temp.disponibilidade);
        fwrite(&livro_temp,sizeof(Biblioteca),1,fp);
        count++;
    }
    fclose(fp);
}

void escreveFita(Biblioteca *livro,char* nome,int nRegistros)
{
    int k=0;
    FILE* pfile = fopen(nome,"wb");
    for( k=0; k< nRegistros; k++)
    {
        fwrite(&livro[k],sizeof(Biblioteca),1,pfile);
    }
    fclose(pfile);
}
