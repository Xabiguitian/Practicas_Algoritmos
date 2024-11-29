#include<stdio.h>

#define TAM 256000

struct monticulo {
    int ultimo;
    int vector[TAM];
};
typedef struct monticulo * pmonticulo;

void iniMonticulo(pmonticulo m);
void insertarMonticulo(pmonticulo m, int x);
void quitarMenor(pmonticulo m);
int consultarMenor(const pmonticulo m);
void crearMonticulo(pmonticulo m, int v [], int n);
void flotar(pmonticulo m, int i);
void intercambiar(pmonticulo *m1, pmonticulo *m2);
void insertar (int x, pmonticulo m);
void hundir(pmonticulo m, int i);
int eliminarMax (pmonticulo m);


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

void flotar(pmonticulo m, int i){
    while (i>1 && m->vector[i/2] < m->vector[i])
    {
        intercambiar(m->vector[i/2], m->vector[i]);
        i = i/2;
    }
    
}

void intercambiar(pmonticulo *m1, pmonticulo *m2){
    pmonticulo aux = m1;
    m1 = m2;
    m2 = aux;
}

void insertar (int x, pmonticulo m){
    if(m->ultimo >= TAM){
        printf("Error: Montículo lleno");
    }else{
        m->ultimo++;
        m->vector[m->ultimo] = x;
        flotar(m, m->ultimo);
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

int eliminarMax (pmonticulo m){
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
}