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
void generarVectorAleat(pmonticulo m, int tam, int rangoMin, int rangoMax);
void imprimirMonticulo(const pmonticulo m);
void testProbarFunciones();

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
    for (i =0; i < n; ++i){
        m->vector[i] = v[i];
    }

    m->ultimo = n - 1;

    for (i = n; i >= 0; --i)
    {
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
    if (m->ultimo == -1) {  
        printf("Error: Montículo vacío\n");
        return -1;  
    }
    return m->vector[1];  
}


//FUNCIÓN PARA GENERAR EL VECTOR ALEATORIO
void generarVectorAleat(pmonticulo m, int tam, int rangoMin, int rangoMax){
int i;

for(i=0;i<tam;i++){
    m->vector[i]=rand()%(rangoMax-rangoMin +1) + rangoMin;
}
m->ultimo=tam-1;
}


//FUNCIÓN PARA IMPRIMIR EL MONTÍCULO
void imprimirMonticulo(const pmonticulo m){
    int i;
    for(i=0;i<m->ultimo;i++){
        printf("%d ", m->vector[i]);
    }
}

//FUNCION TEST PARA COMPROBAR QUE VAN TODAS LAS FUNCIONES DE LOS MONTICULOS

void testProbarFunciones(){
    int tam=10, rangoMin=1, rangoMax=100, x;
    pmonticulo mont = (pmonticulo)malloc(sizeof(struct monticulo));
    iniMonticulo(mont);

    generarVectorAleat(mont, tam, rangoMin, rangoMax);
    imprimirMonticulo(mont);

    insertarMonticulo(mont, 50);
    imprimirMonticulo(mont);

    int menor = consultarMenor(mont);
    printf("El menor valor es: %d\n", menor);

    x = quitarMenor(mont);
    printf("Cuando quitamos el valor %d y nos queda:\n", x);
    imprimirMonticulo(mont);

    free(mont);
}

//FUNCION TEST PARA COMPROBAR QUE VAN TODAS LAS FUNCIONES DE LOS MONTICULOS
/*void test1(){
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
}*/


//FUNCION ASCENDENTE, DESCENDENTE Y ALEATORIO

//FUNCION DE TIEMPOS

//IMPRIMIR TABLAS DE COMPLEJIDAD


//ORDENACIÓN MONTICULOS

/*void ordenarPorMonticulos(){
    int i;
    crearMonticulo(m,v,n);
    for(i=0; i<n; i++){
        v[i]=consultarMenor(m);
        quitarMenor(m);

    }
}*/


int main(){

inicializar_semilla();
testProbarFunciones();

}
