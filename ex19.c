#include <stdio.h>
#include <pthread.h>
#include <time.h>
#define MAX 1080  /*valor maximo de linhas e tambem colunas das matrizes*/

typedef struct mt_matriz    /* definindo um tipo struct composto por duas matrizes de float*/
{
    float mat1[MAX][MAX], mat2[MAX][MAX];
}Mcalc;
void* preenche1(void* arg1);
void* preenche2(void* arg2);

int main(void)
{
    clock_t t1, t2;
    float tempo;  /*variavel que armazena o tempo de execução do programa*/

    Mcalc *matriz;
    pthread_t *th1,*th2,t[8];
    
    srand(time(NULL));

    pthread_create(th1, NULL, preenche1, (void*) matriz);
    pthread_create(th2, NULL, preenche2, (void*) matriz);
}

void* preenche1(void* arg1)   /*função que prenche matriz*/
{
    int i,j;
    Mcalc *matriz = (Mcalc*) arg1 ;

    for(i=0;i<MAX;i++)
        for(j=0;j<MAX;j++)
            matriz->mat1[i][j] = rand()%MAX;
    return NULL;
}

void* preenche2(void* arg2)   /*função que prenche a matriz 2*/
{
    int i,j;
    Mcalc *matriz = (Mcalc*) arg2 ;

    for(i=0;i<MAX;i++)
        for(j=0;j<MAX;j++)
            matriz->mat2[i][j] = rand()%MAX;
    return NULL;
}

