#include <stdio.h>
#include <pthread.h>
#include <time.h>
#define MAX 1080

typedef struct mt_matriz
{
    float mat1[MAX][MAX], mat2[MAX][MAX];
}Mcalc;
void* preenche1(void* arg1);
void* preenche2(void* arg2);

int main(void)
{
    clock_t t1, t2;
    float tempo;

    Mcalc *matriz;
    pthread_t *th1,*th2,t[8];
    
    srand(time(NULL));

    pthread_create(th1, NULL, preenche1, (void*) matriz);
    pthread_create(th2, NULL, preenche2, (void*) matriz);
}

void* preenche1(void* arg1)
{
    int i,j;
    Mcalc *matriz = (Mcalc*) arg1 ;

    for(i=0;i<MAX;i++)
        for(j=0;j<MAX;j++)
            matriz->mat1[i][j] = rand()%MAX;
    return NULL;
}








