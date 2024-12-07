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

//FUNCIÓN PARA IMPRIMIR EL MONTÍCULO
void imprimirMonticulo(const pmonticulo m){
    int i;
    for(i=0;i<=m->ultimo;i++){
        printf("%d ", m->vector[i]);
    }
    printf("\n");
}


void printVector(int v[], int n){
    int i;
    for(i=0;i<n;i++){
        printf("%4d",v[i]);
    }
    printf("\n");
}

//ORDENACIÓN MONTICULOS

void ordenarPorMonticulos(int v[], int n){
    int i;
    pmonticulo m = malloc(sizeof(struct monticulo));
    iniMonticulo(m);
    crearMonticulo(m, v, n);

    for(i = 0; i < n; i++) {
        v[i] = consultarMenor(m);
        quitarMenor(m);
    }

    free(m);
}

void test() {
    pmonticulo m = malloc(sizeof(struct monticulo));

    int tam = 12, menor=0;
    int v[tam];


    int nuevosValores[] = {13, 0, 15};
    //printf("hola");
    v[0]=8;
    v[1]=9;
    v[2]=12;
    v[3]=2;
    v[4]=10;
    v[5]=3;
    v[6]=7;
    v[7]=4;
    v[8]=1;
    v[9]=11;
    v[10]=5;
    v[11]=6;
    v[11]=6;

    iniMonticulo(m);

    printf("Test crearMonticulo \n");
    printVector(v, tam);
    printf("\n");
    crearMonticulo(m, v, tam);
    printf("Montículo creado\n");
    imprimirMonticulo(m);
    printf("\n");

    menor = consultarMenor(m);
    printf("El menor es %d\n", menor);
    quitarMenor(m);
    imprimirMonticulo(m);

    printf("Test insertarMonticulo\n");

    for (int i = 0; i < 3; i++) {
        printf("Insertando %d en el montículo...\n", nuevosValores[i]);
        insertarMonticulo(m, nuevosValores[i]);
        imprimirMonticulo(m);
        printf("\n");
    }

    printf("Ordenación\n");
    ordenarPorMonticulos(v, tam);
    printVector(v, tam);


    free(m);
}

//FUNCION ASCENDENTE, DESCENDENTE Y ALEATORIO

void ascendente(int v[], pmonticulo m,int  n){
    int i;
    iniMonticulo(m);
    for (i = 0; i < n; i++) {
        v[i] = i;

    }
    crearMonticulo(m,v,n);
}


void descendente(int v[], pmonticulo m,int  n){
    int i;
    iniMonticulo(m);
    for (i = n; i > 0; --i) {
        v[n - i] = i - 1;

    }
    crearMonticulo(m,v,n);
}



void aleatorio(int v[], pmonticulo m,int  n){
    int i, x = 2 * n + 1;
    iniMonticulo(m);
    for (i = 0; i < n; i++) {
        v[i] = rand() % x;
    }
        crearMonticulo(m,v,n);

}

//FUNCION DE TIEMPOS INSERCION

double tiemposInsertar(void (*algo)(pmonticulo, int),void (*inicializa)(int [],pmonticulo, int), int tam) {
    double t1, t, t2, aux;
    int *v;
    int i,j;



    v= malloc(tam *sizeof(int));
    pmonticulo m = malloc(sizeof(struct monticulo));
    inicializa(v,m, tam);
    crearMonticulo(m, v, tam);


    t1=microsegundos();
    for(i=0; i<=tam; i++){
        algo(m,v[i]);
    }

    t2=microsegundos();
    t=t2-t1;
    if(t<500){
        t1=microsegundos();
        for(i=0;i<K;i++){
            inicializa(v,m, tam);
            iniMonticulo(m);
            for(j=0; j<=tam; j++){
                algo(m,v[i]);
            }
        }
        t2=microsegundos();
        aux=t2-t1;
        t1=microsegundos();
        for(i=0;i<K;i++){
            inicializa(v,m, tam);
            iniMonticulo(m);
        }
        t2=microsegundos();
        t=t2-t1;
        t=(aux-t)/K;
    }
    free (v);
    free(m);

    return t;

}


//FUNCION DE TIEMPOS DE CREAR
double tiemposCrear(void (*algorit)(pmonticulo, int[], int),void (*inicializa)(int [],pmonticulo, int), int tam) {
    double t1, t, t2, aux;
    int *v;
    int i;
    pmonticulo m = malloc(sizeof(struct monticulo));
    v= malloc(tam *sizeof(int));
    inicializa(v,m, tam);


    t1=microsegundos();
    algorit(m,v,tam);
    t2=microsegundos();
    t=t2-t1;
    if(t<500){
        t1=microsegundos();
        for(i=0;i<K;i++){
            inicializa(v,m, tam);
            algorit(m,v,tam);
        }
        t2=microsegundos();
        aux=t2-t1;
        t1=microsegundos();
        for(i=0;i<K;i++){
            inicializa(v, m,tam);
        }
        t2=microsegundos();
        t=t2-t1;
        t=(aux-t)/K;
    }
    free (v);
    return t;


}

//FUNCION DE TIEMPOS DE ORDENACION

double tiempos(void (*algoritmo)(int[], int), void (*inicializa)(int [], pmonticulo,int), int tam){

    double t1, t, t2, aux;
    int *v;
    int i;


    v= malloc(tam *sizeof(int));
    pmonticulo m = malloc(sizeof(struct monticulo));
    inicializa(v, m,tam);


    t1=microsegundos();
    algoritmo(v,tam);
    t2=microsegundos();
    t=t2-t1;
    if(t<500){
        t1=microsegundos();
        for(i=0;i<K;i++){
            inicializa(v,m, tam);
            algoritmo(v,tam);
        }
        t2=microsegundos();
        aux=t2-t1;
        t1=microsegundos();
        for(i=0;i<K;i++){
            inicializa(v,m, tam);
        }
        t2=microsegundos();
        t=t2-t1;
        t=(aux-t)/K;
    }
    free (v);
    free(m);
    return t;
}

void tablaComplejidadCrearMonticulo() {
    double t;
    int i, *asc;


    printf("TABLA COMPLEJIDAD CREAR MONTÍCULO");
    printf("\n\n\t  n\t\t t(n) \t    t(n)/n^0.95\t       t(n)/n"
              "  t(n)/n^1.2\n");

    for (i = 125; i <=16000; i*=2) {
        asc = malloc(i*sizeof(int));
        pmonticulo m= malloc(sizeof(struct monticulo));
        ascendente(asc,m, i);


        t = tiemposCrear(crearMonticulo,ascendente,i);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
            i, t, t /( pow(i,0.95)), t /( i), t / (pow( i,1.2)));

        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
            i, t, t /( pow(i,0.95)), t /( i), t / (pow( i,1.2)));
        }
        free(asc);
        free(m);


    }



}
void tablaComplejidadInsertarMonticulo() {
    double t;
    int i, *asc;

    printf("TABLA COMPLEJIDAD INSERTAR MONTÍCULO\n");
    printf("\n\n\t  n\t\t t(n) \t    t(n)/n\t       t(n)/n*log(n)"
        "  t(n)/n^2\n");
    for (i = 125; i <=16000; i*=2) {
        asc = malloc(i*sizeof(int));
        pmonticulo m = malloc(sizeof(struct monticulo));
        ascendente(asc,m, i);




        t = tiemposInsertar(insertarMonticulo,ascendente,i);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
            i, t, t /(i), t /( i*log(i)), t / (pow( i,2)));

        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
            i, t, t /(i), t /( i*log(i)), t / (pow( i,2)));
        }
        free(asc);
        free(m);

    }


}



void tablaComplejidadAscendente(){
    double t;
    int i;
    int  *asc;

    printf("\nTABLA COMPLEJIDAD ASCENDENTE\n");
    printf("\n\n\t  n\t\t t(n) \t    t(n)/n\t       t(n)/n*log(n)"
                "  t(n)/n^2\n");

    for (i = 125; i <=16000; i*=2) {
        asc = malloc(i*sizeof(int));
        pmonticulo m = malloc(sizeof(struct monticulo));
        ascendente(asc,m, i);



        t = tiempos(ordenarPorMonticulos,ascendente,i);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
            i, t, t /(i), t /( i*log(i)), t / (pow( i,2)));

        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
            i, t, t /(i), t /( i*log(i)), t / (pow( i,2)));
        }
        free(asc);
        free(m);
    }



}

void tablaComplejidadDescendente(){
    double t;
    int i, *desc;

    printf("\nTABLA COMPLEJIDAD DESCENDENTE");
    printf("\n\n\t  n\t\t t(n) \t    t(n)/n\t       t(n)/n*log(n)"
            "  t(n)/n^2\n");

    for (i = 125; i <=16000; i*=2) {
        desc = malloc(i*sizeof(int));
        pmonticulo m = malloc(sizeof(struct monticulo));
        descendente(desc,m, i);



        t = tiempos(ordenarPorMonticulos,descendente,i);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
            i, t, t /(i), t /( i*log(i)), t / (pow( i,2)));
        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
            i, t, t /(i), t /( i*log(i)), t / (pow( i,2)));
        }
        free(desc);
        free(m);

    }

}

void tablaComplejidadAleatorio(){
    double t;
    int i;
    int *aleat;

    printf("\nTABLA COMPLEJIDAD ALEATORIA");
    printf("\n\n\t  n\t\t t(n) \t    t(n)/n\t       t(n)/n*log(n)"
                "  t(n)/n^2\n");

    for (i = 125; i <=16000; i*=2) {
        aleat = malloc(i*sizeof(int));
        pmonticulo m = malloc(sizeof(struct monticulo));
        aleatorio(aleat,m,i);



        t = tiempos(ordenarPorMonticulos,aleatorio,i);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
            i, t, t /(i), t /( i*log(i)), t / (pow( i,2)));
        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
            i, t, t /(i), t /( i*log(i)), t / (pow( i,2)));
        }
        free(aleat);
        free(m);
    }

}







int main() {
    inicializar_semilla();

    printf("Test\n");
    test();

    printf("Tiempos insertar\n");

    tablaComplejidadInsertarMonticulo();

    printf("Tiempos crear\n");

    tablaComplejidadCrearMonticulo();

    printf("Tiempos ordenación\n");


    tablaComplejidadAleatorio();
    tablaComplejidadDescendente();
    tablaComplejidadAscendente();

}
