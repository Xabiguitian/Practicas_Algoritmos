//DEFINICIÓN DE LIBRERÍAS
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>
#include "monticulo.h"

//DEFINICIÓN DE CONSTANTES

//#define TAM 256000
#define K 1000

void inicializar_semilla(){
    srand(time(NULL));
}

//FUNCIÓN MICROSEGUNDOS
double microsegundos(){
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0){
        return 0.0;
    }
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void printVector(int v[], int n){
    int i;
    for(i=0;i<n;i++){
        printf("%4d",v[i]);
    }
    printf("\n");
}

int kesimoMayor(int v[], int n, int k) {
    if (k <= n) {
        pmonticulo m = malloc(sizeof(struct monticulo));
        iniMonticulo(m);
        crearMonticulo(m, v, k);

        for (int i = k; i < n; i++) {
            if (v[i] > consultarMenor(m)) {
                quitarMenor(m);
                insertarMonticulo(m, v[i]);
            }
        }

        int result = consultarMenor(m);
        free(m);
        return result;
    }
    return -1; // Return an error value if k > n
}

void aleatorio(int v[], int n){
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;

}

void test() {
    pmonticulo m = malloc(sizeof(struct monticulo));
    int tam = 12, i;
    int v[tam];

    printf("K-ésimo mayor\n");
    aleatorio(v, tam);
    printf("Vector original: ");
    printVector(v, tam);
    printf("Elementos extraídos: ");
    for (i = 1; i <= tam; i++) {
        printf("%d ", kesimoMayor(v, tam, i));
    }
    printf("\n");

    free(m);
}



double tiempos(int tam, int k){
    double t1, t, t2, aux;
    int *v;
    int i;

    v= malloc(tam *sizeof(int));
    aleatorio(v, tam);

    t1=microsegundos();
    kesimoMayor(v,tam,k);
    t2=microsegundos();
    t=t2-t1;
    if(t<500){
        t1=microsegundos();
        for(i=0;i<K;i++){
            aleatorio(v, tam);
            kesimoMayor(v,tam, k);
        }
        t2=microsegundos();
        aux=t2-t1;
        t1=microsegundos();
        for(i=0;i<K;i++){
            aleatorio(v, tam);
        }
        t2=microsegundos();
        t=t2-t1;
        t=(aux-t)/K;
    }
    free (v);
    return t;
}


void tablaComplejidad_9(){
    double t;
    int i;
    printf("\nTABLA COMPLEJIDAD K=9");
    printf("\n\n\t  n\t\t t(n) \t t(n)/n^0.3*log(n)\tt(n)/n^0.5*log(n)"
                "\tt(n)/n^0.95\n");

    for (i = 125; i <=16000; i*=2) {

        t = tiempos(i, 9);
        if (t<500)
        {
            printf("(*)%8d%18.3f%21.6f%23.6f%18.6f\n",
            i, t, t /( pow( i,0.3)*log(i)), t /( pow( i,0.5)*log(i)), t / (pow( i,0.95)));
        }else{
            printf("%11d%18.3f%121.6f%23.6f%18.6f\n",
            i, t, t /( pow( i,0.3)*log(i)), t /( pow( i,0.5)*log(i)), t / (pow( i,0.95)));
        }
    }
}

void tablaComplejidad_05n(){
    double t;
    int i;
    printf("\nTABLA COMPLEJIDAD K=n/2");
    printf("\n\n\t  n\t\t t(n) \t\t t(n)/n\t    t(n)/n*log(n)"
                "\t t(n)/n^1.2\n");

    for (i = 125; i <=16000; i*=2) {

        t = tiempos(i, i/2);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
            i, t, t /(i), t /( i*log(i)), t / (pow( i,1.2)));
        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
            i, t, t /(i), t /( i*log(i)), t / (pow( i,1.2)));
        }
    }
}



int main() {
    inicializar_semilla();

    printf("Test\n");
    test();
    tablaComplejidad_9();
    tablaComplejidad_05n();
}