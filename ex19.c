#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#define MAX 1000  /*valor maximo de linhas e tambem colunas das matrizes*/

typedef struct mt     /* definindo um tipo struct */
{
    float mat1[MAX][MAX], mat2[MAX][MAX], mat3[MAX][MAX];
    int md[8];  /*vetor do numero de linhas das "matrizes" 1 e colunas da "matrizes" 2 */
    int l , conta;  /* l indica a linha atual e conta indica o numero de linhas totais para aquela thread */
};

};
void* preenche1(void* arg1);
void* preenche2(void* arg2);
void divide(int n, struct mt *m);
void *runner (void* arg3);
int main(void)
{
    int i,j,k;
    clock_t t1, t2;
    float tempo[8];  /*variavel que armazena o tempo de execução do programa*/

    struct mt *matriz = (struct mt*) malloc(sizeof(struct mt));
    pthread_t *th1,*th2,t[8];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    srand((unsigned) time(NULL));

    printf("Processando, aguarde alguns segundos... \n");

    pthread_create(th1, &attr, preenche1, (void*) matriz);
    pthread_create(th2, &attr, preenche2, (void*) matriz);


    matriz->l=0;
    matriz->conta=0;
    for( i=0;i<8;i++)
    {
        matriz->md[i]=0;
    }


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
    struct mt *matriz = arg1 ;

    for(i=0;i<MAX;i++)
        for(j=0;j<MAX;j++)
            matriz->mat1[i][j] = rand()%MAX;
    return NULL;
}

void* preenche2(void* arg2)   /*função que prenche a matriz 2*/
{
    int i,j;
    struct mt *matriz = arg2 ;

    for(i=0;i<MAX;i++)
        for(j=0;j<MAX;j++)
            matriz->mat2[i][j] = rand()%MAX;
    return NULL;
}

void divide(int n,struct mt *m)
{
    int div=0; int resto=0,i;
    div  = MAX/n;
    resto = MAX%n;

    if(resto ==0)
    {
        for(i=0;i<n;i++)
            m->md[i]=div;
    }
    else if(resto != 0)
    {
        for(i=0;i<n;i++)
            m->md[i]=div;
        m->md[n]+= resto;
    }
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
