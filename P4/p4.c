//DEFINICIÓN DE LIBRERÍAS
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>


//DEFINICIÓN DE CONSTANTES

#define TAM 256000

//DEFINICIÓN DE STRUCTS Y TYPEDEFS
struct monticulo {
    int ultimo;
    int vector[TAM];
};
typedef struct monticulo * pmonticulo;

void inicializar_semilla();
double microsegundos();
void iniMonticulo(pmonticulo m);
void crearMonticulo(pmonticulo m, int v [], int n);
void intercambiar(int *a, int *b);
void flotar(pmonticulo M, int i);
void insertarMonticulo(pmonticulo m, int x);
void hundir(pmonticulo m, int i);
int quitarMenor(pmonticulo m);
int consultarMenor(const pmonticulo m);
void imprimirMonticulo(const pmonticulo m);
void crearVectorPrueba(int v[], int tam);
void testProbarFunciones();
void testOrdenarMonticulo();
void ascendente(int v[], int n);
void descendente(int v[], int n);
void aleatorio(int v[], int n);
void OrdenarPorMontículos();
void tablaComplejidadAleatorio();
void tablaComplejidadAscendente();
void tablaComplejidadDescendente();
void tablaComplejidadCrearMonticulo();
void tablaComplejidadInsertarMonticulo();

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
    int i;
    for (i = 0; i <= n; ++i){
        m->vector[i] = v[i];
    }

    m->ultimo = n-1;

    for (i = n; i >= 0; --i){
        hundir(m, i);
    }
}

//FUNCIÓN AUXILIAR PARA FLOTAR

void intercambiar(int *a, int *b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void flotar(pmonticulo M, int i) {

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
    do{
        hijoizq = 2*i+1;
        hijoder = 2*i+2;
        j = i;
        if (hijoder <= m ->ultimo && m->vector[hijoder] > m->vector[i]){
            i = hijoder;
        }
        if (hijoizq <= m ->ultimo && m->vector[hijoizq] > m->vector[i]){
            i = hijoizq;
        }
        intercambiar(&m->vector[j], &m->vector[i]);
    }while(j!=i);
} 


int quitarMenor(pmonticulo m){
    int x;
    if (m->ultimo == -1) {
        printf("Error: Montículo vacío\n");
        return -1;  
    } else {
        x = m->vector[0]; 
        m->vector[0] = m->vector[m->ultimo];  
        m->ultimo--;  
        if (m->ultimo > 0) {
            hundir(m, 1);  
        }
        return x;  
    }
}

int consultarMenor(const pmonticulo m) {
    if (m->ultimo == -1) {  
        printf("Error: Montículo vacío\n");
        return -1;  
    }
    int i, menor = m->vector[m->ultimo/2];
    for (i = m->ultimo/2; i <= m->ultimo; i++){
        if (m->vector[i] < menor) menor = m->vector[i];
    }
    return menor;  
}


//FUNCIÓN PARA IMPRIMIR EL MONTÍCULO
void imprimirMonticulo(const pmonticulo m){
    int i;
    for(i=0;i<=m->ultimo;i++){
        printf("%d ", m->vector[i]);
    }
    printf("\n");
}

void crearVectorPrueba(int v[], int tam){
    int i;

    v[0]=1;
    v[1]=2;
    v[2]=3;
    v[3]=4;
    v[4]=14;
    v[5]=6;
    v[6]=7;
    v[7]=8;
    v[8]=9;
    v[9]=10;
    v[10]=11;
    v[11]=12;
    v[12]=13;
    v[13]=5;

    for(i=0; i < tam; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

//FUNCION TEST PARA COMPROBAR QUE VAN TODAS LAS FUNCIONES DE LOS MONTICULOS

void testProbarFunciones(){
    int tam=14, rangoMin=1, rangoMax=100, x, v[tam], v2[tam], i;
    pmonticulo mont = (pmonticulo)malloc(sizeof(struct monticulo));
    iniMonticulo(mont);


    crearVectorPrueba(v,tam);
    crearMonticulo(mont,v,tam);
    imprimirMonticulo(mont);

    //insertarMonticulo(mont, 50);
    //imprimirMonticulo(mont);

    int menor = consultarMenor(mont);
    printf("El menor valor es: %d\n", menor);

    for (i = 0; i < tam; i++)
    {
        x = quitarMenor(mont);
        v2[i] = x;
    }
    imprimirMonticulo(v2);

    free(mont);
}


//ORDENACIÓN MONTICULOS

/*void ordenarPorMonticulos(){
    int i;
    crearMonticulo(m,v,n);
    for(i=0; i<n; i++){
        v[i]=consultarMenor(m);
        quitarMenor(m);

    }
}*/


//FUNCION ASCENDENTE, DESCENDENTE Y ALEATORIO

void ascendente(int v[], int n){
 int i;
    for (i = 0; i < n; i++) {
        v[i] = i;
    }
}


void descendente(int v[], int n){
  int i;
    for (i = n; i > 0; --i) {
        v[n - i] = i - 1;
    }

}



void aleatorio(int v[], int n){
 int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;

}

//FUNCION DE TIEMPOS

/*double tiempos(void (*algoritmo)(int[], int), void (*inicializa) (int [],int), int tam){

    double t1, t,t2,aux;
    int *v;
    int i;


    v= malloc(tam *sizeof(int));
    inicializa(v, tam);

    t1=microsegundos();
    algoritmo(v,tam);
    t2=microsegundos();
    t=t2-t1;
    if(t<500){
        t1=microsegundos();
        for(i=0;i<K;i++){
            inicializa(v,tam);
            algoritmo(v,tam);
        }
        t2=microsegundos();
        aux=t2-t1;
        t1=microsegundos();
        for(i=0;i<K;i++){
            inicializa(v,tam);
        }
        t2=microsegundos();
        t=t2-t1;
        t=(aux-t)/K;
    }


free (v);
return t;

}*/

//IMPRIMIR TABLAS DE COMPLEJIDAD

void tablaComplejidadInsertarMonticulo(){

    printf("\n\nn \t t(n) \t\t t(n)/(n*log(n)) \t t(n)/(n*log(n))\t t(n)/(n*log(n))\n");
}


void tablaComplejidadCrearMonticulo(){

    printf("\n\nn \t t(n) \t\t  t(n)/n \t t(n)/n \t  t(n)/n\n");
}

void tablaComplejidadAscendente(){

}

void tablaComplejidadDescendente(){

}

void tablaComplejidadAleatorio(){

}



int main(){

inicializar_semilla();
testProbarFunciones();

}
