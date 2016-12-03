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

    srand(time(NULL)); /*recebendo um valor aleatorio da função time*/

    pthread_create(th1, NULL, preenche1, (void*) matriz);
    pthread_create(th2, NULL, preenche2, (void*) matriz);
    for(k=0; k<8;k++)
    {
        t1=clock() ;
        divide(k+1,matriz);
        matriz->l=0;
        matriz->conta = 0;
        for(i=0;i<k;i++)
        {
            matriz->conta += matriz->md[i];
            pthread_create(&t[i], &attr, runner, matriz);
        }

        for(j=0;j <k ;j++)
            pthread_join(t[j],NULL);

        t2=clock();
        tempo[i]= ((double)(t2-t1)/CLOCKS_PER_SEC);
    }
    for(i=0;i<8;i++)
        printf("com %d threads | %.4f segundos\n",i+1,tempo[i]);

    return 0;
}
}

void* preenche1(void* arg1)   /*função que prenche matriz*/
{
    int i,j;
    Mcalc *matriz = (Mcalc*) arg1 ;

    for(i=0;i<MAX;i++)
    {
        for(j=0;j<MAX;j++)
        {
            matriz->mat1[i][j] = rand()%MAX;
        }
    }
    return NULL;
}



void* runner (void* arg3)
{
    struct mt *matriz = arg3;
    int n,k, valor=0;
    while((matriz->l) < (matriz->conta))
    {
        for(k=0; k<MAX; k++)
        {
            for(n=0; n<MAX; n++)
                valor += matriz->mat1[matriz->l][n] * matriz->mat2[n][k];
            matriz->mat3[matriz->l][k];
        }
        matriz->l++;
    }
    return NULL;
}




