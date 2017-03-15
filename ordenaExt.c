#include "ordenaExt.h"
#include "ordenamPrincipal.h"
#include "bib.h"

void OrdenaExterno(int M, int N)
{
    remove("livros_ordenados");
    int nfitas = 0,cont=0,nlivros=0;
    int i;
    FILE *pf_Entrada;
    pf_Entrada = fopen ( "entrada.dat", "rb" );
    char nomeArq[50], nomeArqIntercal[50], nomeArqSaida[50];
    char novoNome[] = {"livros_ordenados"};
    Biblioteca *livro;
    livro = ( Biblioteca* )malloc(M*sizeof(Biblioteca) );
    if(livro==NULL)
    {
        printf("Erro ao Alocar estrutura Livro");exit(0);
    }
    while (nlivros < N) //Cria blocos ordenados
    {
        fread (&livro[cont],sizeof(Biblioteca),1,pf_Entrada);
        cont++;
        nlivros++;
        if ( cont == M )
        {
            nfitas++;
            ordenaInterno(livro,M);
            sprintf ( nomeArq, "fita%d.dat", nfitas );
            escreveFita(livro,nomeArq,M);
            cont=0;
        }
    }
    if(cont > 0)//Escreve mais uma fita caso N%M !=0
    {
        nfitas++;
        ordenaInterno(livro,cont);
        sprintf(nomeArq,"fita%d.dat",nfitas);
        escreveFita(livro,nomeArq,cont);
    }
    free(livro);
    livro =NULL;
    fclose(pf_Entrada);
    remove ("Entrada.dat");
    if (nfitas == 1)
    {
        sprintf(nomeArqSaida,"livros_ordenados");
        escreveFita(livro,nomeArqSaida,cont);
    }
    else
    {
        sprintf (nomeArqIntercal,"fita%d.dat",nfitas+1);
        Intercalacao ("fita1.dat","fita2.dat",nomeArqIntercal);
        strcpy (nomeArqSaida,nomeArqIntercal);
        if ( nfitas > 2 )
        {
            for ( i = 3; i <= nfitas; i++ )
            {
                sprintf ( nomeArq, "fita%d.dat", i );
                sprintf ( nomeArqSaida, "fita%d.dat", nfitas+i-1);
                Intercalacao ( nomeArq, nomeArqIntercal, nomeArqSaida );
                strcpy ( nomeArqIntercal, nomeArqSaida );
            }
        }
    }
    rename(nomeArqSaida, novoNome);
}

void Intercalacao ( char *nomefita1, char *nomefita2, char *nomefita3 )
{
    FILE *fita1, *fita2, *fita3;
    Biblioteca livro_aux1, livro_aux2;
    char stringFlag[] = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    fita1 = fopen(nomefita1,"rb");
    fita2 = fopen(nomefita2,"rb");
    fita3 = fopen(nomefita3,"wb");
    fread (&livro_aux1,sizeof(Biblioteca),1,fita1);
    fread (&livro_aux2,sizeof(Biblioteca),1,fita2);
    while (!feof( fita1 ) || !feof( fita2 ))
    {
        if ( strcmp(livro_aux1.livro_titulo,livro_aux2.livro_titulo) <= 0 || ( feof( fita2 ) && !feof( fita1 ) ) )
        {
            fwrite (&livro_aux1, sizeof(livro_aux1),1,fita3);
            fread (&livro_aux1, sizeof(Biblioteca),1,fita1);
            if (feof(fita1))
            {
                strcpy(livro_aux1.livro_titulo,stringFlag);
            }
        }
        else if ( strcmp(livro_aux1.livro_titulo,livro_aux2.livro_titulo) > 0 || ( feof( fita1 ) && !feof( fita2 ) ) )
        {
            fwrite (&livro_aux2,sizeof( livro_aux2 ),1,fita3);
            fread (&livro_aux2,sizeof( Biblioteca ), 1,fita2);
            if (feof(fita2))
            {
                strcpy(livro_aux2.livro_titulo,stringFlag);
            }
        }
    }
    fclose (fita1 );
    fclose (fita2 );
    fclose (fita3 );
    remove (nomefita1);
    remove (nomefita2);

}
