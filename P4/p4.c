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


//DEFINICIÓN DE FUNCIONES
void iniMonticulo(pmonticulo m);
void insertarMonticulo(pmonticulo m, int x);
void quitarMenor(pmonticulo m);
int consultarMenor(const pmonticulo m);
void crearMonticulo(pmonticulo m, int v [], int n);
void flotar(pmonticulo m, int i);



void iniMonticulo(pmonticulo m){
    m->ultimo=0;
}

void crearMonticulo(pmonticulo m, int v [], int n){
    iniMonticulo(m);
    return m;
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
    


/*void hundir(pmonticulo m, int i){
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
}*/  



/*int eliminarMax (pmonticulo m){
    int x;
    if (m->ultimo == 0){
        printf("Error: Montículo vacío");
    }else{
        x = m->vector[1];
        m->vector[1] = m->vector[m->ultimo];
        m->ultimo--;
        if (m->ultimo > 0){
            hundir(m, 1);
        }
        return x;
    }
}*/ 

void quitarMenor(pmonticulo m){

}
int consultarMenor(const pmonticulo m){

}



int main(){


inicializar_semilla();



}
