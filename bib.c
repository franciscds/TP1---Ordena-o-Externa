#include "bib.h"
#include "ordenaExt.h"


indice* OrganizaEstantes(int nEstantes,int nLivros,int N)
{
    int i=0,cont=0,n_estantes=0,nl=0;
    char nome[50];
    FILE *livrosOrdenados = fopen("livros_ordenados","rb");
    FILE *temp;
    if(livrosOrdenados == NULL)
    {
        exit(0);
    }
    Biblioteca* livro = (Biblioteca*)malloc(nLivros*sizeof(Biblioteca));
    if(livrosOrdenados == NULL)
    {
        exit(0);
    }
    indice *index = (indice*)malloc(nEstantes*sizeof(indice));
    for(i=0; i<nEstantes; i++)
    {
        index[i].nLivros=0;
    }
    while( nl < N )
    {   /*se cont=0, significa que a proxima leitura e o incio de uma estante*/
        if(cont == 0)index[n_estantes].inicio = ftell(livrosOrdenados);
        index[n_estantes].fim = ftell(livrosOrdenados);
        fread (&livro[cont],sizeof(Biblioteca),1,livrosOrdenados);
        cont++;
        nl++;
        if(cont == nLivros)
        {
            sprintf(nome,"estante%d",n_estantes);
            escreveFita(livro,nome,nLivros);
            index[n_estantes].nLivros += cont;
            cont =0;
            n_estantes++;
        }
    }
    if(cont >0)
    {
        sprintf(nome,"estante%d",n_estantes);
        escreveFita(livro,nome,cont);
        index[n_estantes].fim = ftell(livrosOrdenados);
        index[n_estantes].nLivros += cont;
        n_estantes++;
    }
    if( n_estantes < nEstantes)
    {
        for( i=0; i< nEstantes; i++)
        {
            sprintf(nome,"estante%d",n_estantes);
            temp = fopen(nome,"wb");
            fclose(temp);
            n_estantes++;
        }
    }
    criaIndice(index,nEstantes,n_estantes);
    fclose(livrosOrdenados);
    free(livro);
    livro = NULL;
    return index;
}
void fazConsulta(int nConsultas,indice* index)
{
    int cont=0,estante_i=0,estante=0;
    char livroTemp[52],aux1[51],aux2[51];
    FILE* f_indice = fopen("indice","rb");
    while( cont < nConsultas )
    {
        scanf("%s",livroTemp);
        cont++;
        fseek(f_indice,0,SEEK_SET);
        while( !feof(f_indice) )
        {
            fread(aux1,sizeof(aux1),1,f_indice);
            fread(aux2,sizeof(aux2),1,f_indice);
            if( strcmp(livroTemp,aux1) >= 0 && strcmp(livroTemp,aux2) <= 0 )
            {
                estante = estante_i;
                break;
            }
            else estante_i++;
        }
        pesquisaBin(index[estante],livroTemp,estante);
        estante_i=0;
    }
    fclose(f_indice);
}
void pesquisaBin(indice index,char* tituloLivro,int i)
{
    char nomeEstante[10];
    FILE *estante;
    int meio=0,ini=0,fim=0,cont=0;
    bool livroEncontrado = false;
    Biblioteca livro_temp;
    sprintf(nomeEstante,"estante%d",i);
    estante = fopen(nomeEstante,"rb");
    ini = 0;
    fim = index.nLivros-1;
    meio = (ini+fim)/2;/*inicialisa meio pra iniciar a busca no meio da estante*/
    fseek(estante,meio*sizeof(Biblioteca),SEEK_SET);
    while( cont < index.nLivros)
    {

        fread(&livro_temp,sizeof(Biblioteca),1,estante);
        if( strcmp(tituloLivro,livro_temp.livro_titulo) < 0 )
        {
            fim = meio - 1;
        }
        else if( strcmp(tituloLivro,livro_temp.livro_titulo) > 0)
        {
            ini = meio+1;
        }
        else//econtrou
        {
            livroEncontrado = true;
            break;
        }
        cont++;
        meio = (ini+fim)/2;
        fseek(estante,(meio)*sizeof(Biblioteca),SEEK_SET);/*reposiciona ponteiro*/
    }
    if( livroEncontrado == true)
    {
        if(livro_temp.disponibilidade == 1)
        {
            printf("disponivel na posicao %d da estante %d\n",meio,i);
        }
        else
        {
            printf("emprestado\n");
        }
    }
    else
    {
        printf("livro nao encontrado\n");
    }
    fclose(estante);
}
void criaIndice(indice *index,int nEstantes,int eOcupadas)
{
    FILE* f_indice = fopen("indice","wb");
    FILE *livros_ordenados = fopen("livros_ordenados","rb");
    Biblioteca temp;
    char hashtag[] = "#\n";
    int cont=0,k=0;
    if(f_indice==NULL)
    {
        exit(0);
    }
    while( cont < nEstantes)
    {
        if(cont>= eOcupadas)
        {
            fwrite(&hashtag,strlen(temp.livro_titulo),1,f_indice);
            cont++;
        }
        else
        { /*cria indice de livros utilizando vetor de index*/
            fseek(livros_ordenados,index[k].inicio,SEEK_SET);
            fread(&temp,sizeof(Biblioteca),1,livros_ordenados);
            fwrite(&temp.livro_titulo,51*sizeof(char),1,f_indice);

            fseek(livros_ordenados,0,SEEK_SET);

            fseek(livros_ordenados,index[k].fim,SEEK_SET);
            fread(&temp,sizeof(Biblioteca),1,livros_ordenados);
            fwrite(&temp.livro_titulo,51*sizeof(char),1,f_indice);

            fseek(livros_ordenados,0,SEEK_SET);
            cont++;
            k++;
        }
    }
    fclose(f_indice);
    fclose(livros_ordenados);
}
