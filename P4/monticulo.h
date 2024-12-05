//
// Created by angela on 5/12/24.
//

#ifndef MONTICULO_H
#define MONTICULO_H

#define TAM 256000

//DEFINICIÓN DE STRUCTS Y TYPEDEFS
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

#endif //MONTICULO_H
