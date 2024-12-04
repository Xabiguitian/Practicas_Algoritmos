//DEFINICIÓN DE LIBRERÍAS
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>


//DEFINICIÓN DE CONSTANTES

#define TAM 256000
#define K 1000

//DEFINICIÓN DE STRUCTS Y TYPEDEFS
struct monticulo {
    int ultimo;
    int vector[TAM];
};
typedef struct monticulo * pmonticulo;


//DEFINICIÓN DE LAS FUNCIONES
void inicializar_semilla();
double microsegundos();
double tiempos(void (*algoritmo)(int[], int), void (*inicializa) (pmonticulo, int [], int), int tam, pmonticulo m);
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
void ascendente(int v[], int n);
void descendente(int v[], int n);
void aleatorio(int v[], int n);
void OrdenarPorMontículos();
void tablaComplejidadAleatorio();
void tablaComplejidadAscendente();
void tablaComplejidadDescendente();
void tablaComplejidadCrearMonticulo();
void tablaComplejidadInsertarMonticulo();
void printVector(int v[], int n);
void testOrdenarMonticulo(void (*algoritmo)(int[], int),int *vector, int tamV);

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
        intercambiar(&m->vector[i], &m->vector[j]);
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
    return m->vector[0];  
}


//FUNCIÓN PARA IMPRIMIR EL MONTÍCULO
void imprimirMonticulo(const pmonticulo m){
    int i;
    for(i=0;i<=m->ultimo;i++){
        printf("%d ", m->vector[i]);
    }
    printf("\n");
}

void crearVectorPrueba(int v[], int tam) {
    int i;

    v[0]=1;
    v[1]=2;
    v[2]=3;
    v[3]=25;
    v[4]=5;
    v[5]=6;
    v[6]=7;
    v[7]=8;
    v[8]=83;
    v[9]=17;
    v[10]=11;
    v[11]=12;

    for(i=0; i < tam; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

//FUNCION TEST PARA COMPROBAR QUE VAN TODAS LAS FUNCIONES DE LOS MONTICULOS

void testProbarFunciones(){
    int tam=12, rangoMin=1, rangoMax=100, x, v[tam], v2[tam], i;
    pmonticulo mont = (pmonticulo)malloc(sizeof(struct monticulo));
    iniMonticulo(mont);
    crearVectorPrueba(v, tam);
    crearMonticulo(mont, v, tam);
    imprimirMonticulo(mont);

    printf("El menor valor es: %d\n", consultarMenor(mont));
    for (int i = 0; i < tam; i++) {
        quitarMenor(mont);
    }
    imprimirMonticulo(mont);

    free(mont);
}


//FUNCION TEST PARA COMPROBAR QUE EL MONTICULO SE ORDENA CORRECTAMENTE CON LA FUNCIÓN IMPLEMENTADA.
void testOrdenarMonticulo(void (*algoritmo)(int[], int), int *vector, int tamV) {
    pmonticulo mont = (pmonticulo)malloc(sizeof(struct monticulo));
    iniMonticulo(mont);

    printf("Montículo inicial:\n");
    crearMonticulo(mont, vector, tamV);
    imprimirMonticulo(mont);

    algoritmo(vector, tamV);

    printf("Montículo ordenado:\n");
    imprimirMonticulo(mont);

    free(mont);
}


//ORDENACIÓN MONTICULOS

void ordenarPorMonticulos(pmonticulo m, int v[]){
    int i, j = m->ultimo;
    for(i=0; i <= j; i++){
        v[i]=consultarMenor(m);
        quitarMenor(m);

    }
}


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

double tiempos(void (*algoritmo)(int[], int), void (*inicializa) (pmonticulo, int [], int), int tam, pmonticulo m){

    double t1, t, t2, aux;
    int *v;
    int i;


    v= malloc(tam *sizeof(int));
    inicializa(m, v, tam);

    t1=microsegundos();
    algoritmo(v,tam);
    t2=microsegundos();
    t=t2-t1;
    if(t<500){
        t1=microsegundos();
        for(i=0;i<K;i++){
            inicializa(m, v, tam);
            algoritmo(v,tam);
        }
        t2=microsegundos();
        aux=t2-t1;
        t1=microsegundos();
        for(i=0;i<K;i++){
            inicializa(m, v, tam);
        }
        t2=microsegundos();
        t=t2-t1;
        t=(aux-t)/K;
    }


free (v);
return t;

}

//IMPRIMIR TABLAS DE COMPLEJIDAD

void tablaComplejidadInsertarMonticulo(){
    int n;
    double tiempo;

    printf("\n Inserción de Montículos\n");
    printf("\n\n\t  N\t\t t(n) \t    O(n*log(n)) \n");
    for (n = 500; n <= K; n = n * 2) {
        tiempo = tiempos(ascendente,insertarMonticulo,n,m);
        printf("%10d    \t|%14.3f\t|%14.8f\n",
                n, tiempo, tiempo/n);

    }
}


void tablaComplejidadCrearMonticulo(){
    int n;
    double tiempo;

    printf("\n Creacion de Monticulos\n");
    printf("\n\n\t  N\t\t t(n) \t    O(n) \n");
    for (n = 500; n <= K; n = n * 2) {
        tiempo = tiempos(ascendente,crearMonticulo,n,m);
        printf("%10d    \t|%14.3f\t|%14.8f\n",
                n, tiempo, tiempo/n);

    }
}

void tablaComplejidadAscendente(){
    double t;
    int i;

    printf("\n\n\t  n\t\t t(n) \t    t(n)/n^0.95\t           t(n)/n"
            "   t(n)/(n*log(n))\n");

    for (i = 125; i <=K; i*=2) {

        t = tiempos(ascendente,ordenarPorMonticulos,i,m);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i,1), t / (i * log(i)));
        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i,1), t / (i * log(i)));
        }
    }



}

void tablaComplejidadDescendente(){
    double t;
    int i;

    printf("\n\n\t  n\t\t t(n) \t    t(n)/n^0.95\t           t(n)/n"
            "   t(n)/(n*log(n))\n");

    for (i = 125; i <=K; i*=2) {

        t = tiempos(descendente,ordenarPorMonticulos,i,m);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i,1), t / (i * log(i)));
        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i,1), t / (i * log(i)));
        }
    }

}

void tablaComplejidadAleatorio(){
    double t;
    int i;

    printf("\n\n\t  n\t\t t(n) \t    t(n)/n^0.95\t           t(n)/n"
            "   t(n)/(n*log(n))\n");

    for (i = 125; i <=K; i*=2) {

        t = tiempos(aleatorio,ordenarPorMonticulos,i,m);
        if (t<500)
        {
            printf("(*)%8d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i,1), t / (i * log(i)));
        }else{
            printf("%11d%18.3f%18.6f%18.6f%18.6f\n",
                i, t, t / pow(i, 0.95), t / pow(i,1), t / (i * log(i)));
        }
    }

}




int main() {
    int tamV = 100;
    int *asc, *desc, *aleat;

    inicializar_semilla();

    // Test de las funciones de montículos
    testProbarFunciones();

    // Crear tablas de complejidad
    tablaComplejidadCrearMonticulo();
    tablaComplejidadInsertarMonticulo();

    // Prueba con datos ascendentes
    printf("\nAscendente:\n");
    asc = malloc(tamV * sizeof(int));
    ascendente(asc, tamV);
    testOrdenarMonticulo(ascendente, asc, tamV);
    tablaComplejidadAscendente();
    free(asc);

    // Prueba con datos descendentes
    printf("\nDescendente:\n");
    desc = malloc(tamV * sizeof(int));
    descendente(desc, tamV);
    testOrdenarMonticulo(descendente, desc, tamV);
    tablaComplejidadDescendente();
    free(desc);

    // Prueba con datos aleatorios
    printf("\nAleatorio:\n");
    aleat = malloc(tamV * sizeof(int));
    aleatorio(aleat, tamV);
    testOrdenarMonticulo(aleatorio, aleat, tamV);
    tablaComplejidadAleatorio();
    free(aleat);

    return 0;


}