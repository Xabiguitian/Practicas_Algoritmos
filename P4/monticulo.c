//
// Created by angela on 5/12/24.
//

#include <stdio.h>
#include "monticulo.h"

void iniMonticulo(pmonticulo m) {
    m->ultimo=-1;
}

//FUNCIÓN AUXILIAR PARA FLOTAR

void flotar(pmonticulo m, int i) {
    int aux;
   while (i > 0 && m->vector[i / 2] > m->vector[i]) {
        aux = m->vector[i / 2];
        m->vector[i / 2] = m->vector[i];
        m->vector[i] = aux;

        i = i / 2;
    }
}

void hundir(pmonticulo m, int i){
    int j, hijoizq, hijoder, aux;
    do{
        hijoizq = 2*i+1;
        hijoder = 2*i+2;
        j = i;
        if (hijoder -1<= m ->ultimo && m->vector[hijoder] < m->vector[i]){
            i = hijoder;
        }
        if (hijoizq-1 <= m ->ultimo && m->vector[hijoizq] < m->vector[i]){
            i = hijoizq;
        }

        aux = m->vector[i];
        m->vector[i] = m->vector[j];
        m->vector[j] = aux;
    }while(j!=i);
}

void insertarMonticulo(pmonticulo m, int x) {
    if (m->ultimo >= TAM)
    {
        perror("Montículo lleno");
    }else{
        m->ultimo += 1;
        m->vector[m->ultimo] = x;
        flotar(m,m->ultimo);
    }
}

void quitarMenor(pmonticulo m) {
    if (m->ultimo == -1) {
        printf("Error: Montículo vacío\n");
    } else {
        m->vector[0] = m->vector[m->ultimo];
        m->ultimo--;
        if (m->ultimo >= 0) {
            hundir(m, 0);
        }
    }
}

int consultarMenor(const pmonticulo m) {
    if (m->ultimo == -1) {
        printf("Error: Montículo vacío\n");
        return -1;
    }
    return m->vector[0];
}

void crearMonticulo(pmonticulo m, int v [], int n) {
    int i;
    for (i = 0; i < n; i++){
        m->vector[i] = v[i];
    }

    m->ultimo = n-1;

    for (i = n/2; i >= 0; i--){
        hundir(m, i);
    }
}



