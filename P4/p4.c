//DEFINICIÓN DE LIBRERÍAS
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include "monticulos.h"
#include <math.h>


//DEFINICIÓN DE CONSTANTES

#define TAM 256000

//DEFINICIÓN DE STRUCTS Y TYPEDEFS
struct monticulo {
    int ultimo;
    int vector[TAM];
};
typedef struct monticulo * pmonticulo;

//FUNCIÓN INICIALIZAR SEMILLA

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


//FUNCIONES PARA EL MONTICULO


void iniMonticulo(pmonticulo m){
    m->ultimo=0;
}

void crearMonticulo(pmonticulo m, int v [], int n){
    iniMonticulo(m);
    return m;
}

//FUNCIÓN AUXILIAR PARA FLOTAR

void intercambiar(pmonticulo *m1, pmonticulo *m2){
    pmonticulo aux = m1;
    m1 = m2;
    m2 = aux;
}

void flotar(monticulo *M, int i) {

    while (i > 1 && M->vector[i / 2] < M->vector[i]) {

        intercambiar(&M->vector[i/2], &M->vector[i]);
        i = i / 2;
    }
}


void insertarMonticulo(pmonticulo m, int x){
    if (m->ultimo >= TAM)
    {
        perror("Montículo lleno");
    }else{
        m->ultimo += 1;
        m->vector[m->ultimo] = x;
        flotar(m,m->ultimo);
    }
    
}

  


void hundir(pmonticulo m, int i){
    int j = -1, hijoizq, hijoder;
    while(j=!i){
        hijoizq = 2*i;
        hijoder = 2*i+1;
        j = i;
        if (hijoder <= m ->ultimo && m->vector[hijoder] > m->vector[i]){
            i = hijoder;
        }
        if (hijoizq <= m ->ultimo && m->vector[hijoizq] > m->vector[i]){
            i = hijoizq;
        }
        intercambiar(m->vector[j], m->vector[i]);
    }
} 





void quitarMenor(pmonticulo m){
 int x;
    if (m->ultimo == 0) {
        printf("Error: Montículo vacío\n");
        return -1;  
    } else {
        x = m->vector[1]; 
        m->vector[1] = m->vector[m->ultimo];  
        m->ultimo--;  
        if (m->ultimo > 0) {
            hundir(m, 1);  
        }
        return x;  
    }
}
int consultarMenor(const pmonticulo m) {
    if (m->ultimo == 0) {  
        printf("Error: Montículo vacío\n");
        return -1;  
    }
    return m->vector[1];  
}


//FUNCION AUX
void print_heap(monticulo *M){
    int i;
    printf("[");
    for(i=0;i<=M->ultimo;i++)
        printf(" %d ",M->vector[i]);
    printf("]\n");
}


//FUNCION TEST PARA COMPROBAR QUE VAN TODAS LAS FUNCIONES DE LOS MONTICULOS
void test1(){
    printf("----------------------------------------------------------------");
    printf("\n");
    int v[25],i;
    pmonticulo m;
    printf("[");
    for(i=0;i<25;i++){
        v[i]=i-12;
        printf(" %d ",v[i]);
    }
    printf("]\n");
    niMonticulo(&m);
    crearMonticulo(v,25,&m);
    print_heap(&m);
    eliminar_mayor(&m);
    print_heap(&m);
    printf("----------------------------------------------------------------");
    printf("\n");
}


//FUNCION ASCENDENTE, DESCENDENTE Y ALEATORIO

//FUNCION DE TIEMPOS

//IMPRIMIR TABLAS DE COMPLEJIDAD


//ORDENACIÓN MONTICULOS

void ordenarPorMonticulos(){
    int i;
    crearMonticulo(m,v,n);
    for(i=0; i<n; i++){
        v[i]=consultarMenor(m);
        quitarMenor(m);

    }
}


int main(){


inicializar_semilla();



}
