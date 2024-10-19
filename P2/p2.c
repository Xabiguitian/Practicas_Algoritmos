
//P2
//para cada algoritmo va haber 3 tablas en el informe
//proporcionan lass funciones de semilla, aleatorio y ascendente, desas funciones hay que hacer la FUNCIÓN SEMILLA


//En esta práctica se van a implementar los algoritmos de inserción y de ordenación rápida con selección aleatoria del pivote.

//La práctica consiste en ordenar un vector de n numeros enteros





#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>


#define K 100000
#define UMBRAL 1

typedef enum cota{
    CONST, SOBR, SUBS

}cota;

typedef struct tCota{
    double resultado;
    char *string;

}tCota;


double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla() {
	srand(time(NULL));
}

void aleatorio(int v [], int n) {/* se generan números pseudoaleatorio entre -n y +n */
	int i, m=2*n+1;
	for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;
}

//CÓDIGOS PROPORCIONADOS EN LA PRÁCTICA
//CÓDIGO DE LOS ALGORITMOS DE INSERCIÓN Y DE ORDENACIÓN RÁPIDA

//FUNCIONES PROGRAMA
void ord_ins(int v[], int n){
	int i,x,j;

	for(i=1;i<n;i++){
		x=v[i];
		j=i-1;
		while(j>=0 && v[j]>x){
			v[j+1]=v[j];
			j--;

		}
		v[j+1]=x;
	}
}


void intercambiar(int *a, int *b) {
	int auxiliar;

	auxiliar=*a;
	*a=*b;
	*b=auxiliar;
}



void ord_rap_aux(int v[], int iz, int dr){
	int x,i,j, pivote;

	if(iz<dr){

		inicializar_semilla();
		x = (iz + rand() % (dr - iz +1));
		pivote=v[x];
		intercambiar(&v[iz],&v[x]); //mirar función intercambiar
		i=iz+1;
		j=dr;
		while(i<=j){
			while(i<=dr&&v[i]<pivote){
				i++;
			}

			while(v[j]>pivote){
				j--;
				
			}

			if(i<=j){
					intercambiar(&v[i],&v[j]);
					i++;
					j--;

			}
			
		
		}
		intercambiar(&v[iz], &v[j]);
		ord_rap_aux(v, iz, j-1);
		ord_rap_aux(v, i, dr);
		
	}
}


void ord_rap (int v [], int n) {
	ord_rap_aux(v, 0, n-1);
}



void ascendente(int v [], int n) {
	int i;
	for (i=0; i < n; i++)
		v[i] = i+1;
}

void descendente(int v[], int n){
	int i;
	for(i=0; i < n; i++){
		v[i] = n - i;

	}

}


void printVector(int v[], int n){
	int i;
	for(i=0;i<n;i++){
		printf("%4d",v[i]);
	}
	printf("\n");
}


bool ordenado(int v[], int n){
	int i;
	for(i=0;i<n-1;i++){
    	if(v[i]>v[i+1]){
      		return false;
        }
  	}

  	return true;
}


//FUNCIÓN VOID TEST

void test(void (*algoritmo)(int[], int), int tamV){
	int * desc, * asc, * aleat;

	//vectores vacíos
	desc=malloc(tamV * sizeof(int));
	asc=malloc(tamV * sizeof(int));
	aleat=malloc(tamV * sizeof(int));


	ascendente(asc, tamV);
	descendente(desc,tamV);
	aleatorio(aleat,tamV);

    printf("\nInicialización aleatoria.\n");
    printVector(aleat,tamV);
    printf("Ordenado? %d\nordenando...",ordenado(aleat,tamV));
    algoritmo(aleat,tamV);
    printVector(aleat,tamV);
    printf("ordenado? %d\n",ordenado(aleat,tamV));

	printf("\nInicialización ascendente.\n");
    printVector(asc,tamV);
	printf("Ordenado? %d\nordenando...",ordenado(asc,tamV));
    algoritmo(asc,tamV);
	printVector(asc,tamV);
	printf("ordenado? %d\n",ordenado(asc,tamV));

	printf("\nInicialización descendente.\n");
	printVector(desc,tamV);
	printf("Ordenado? %d\nordenando...",ordenado(desc,tamV));
	algoritmo(desc,tamV);
	printVector(asc,tamV);
	printf("ordenado? %d\n",ordenado(asc,tamV));

    free(desc);
    free(asc);
    free(aleat);

}





//FUNCIONES PARA LAS MEDICIONES (para cada algoritmo va haber 3 tablas en el informe)

/*inicializar(vector);
leer_tiempo (ta); alg(vector); leer_tiempo (tb);
t:=tb-ta;
si (t < 500) entonces { % ‘‘umbral de confianza’’
leer_tiempo (ta);
repetir K veces: {
inicializar(vector); alg(vector)
};
leer_tiempo (tb);
t1:=tb-ta; % deber´ıa estar por encima de 500!
leer_tiempo (ta);
repetir K veces: % debe ser la misma constante K
inicializar(vector);
leer_tiempo (tb);
t2:=tb-ta;
t:=(t1-t2)/K
}*/

double tiempo(void (*algoritmo)(int[], int), int vector [], int tam){

    double t1, t=0,t2,aux;
    int i;

    t1=microsegundos();
    algoritmo(vector,tam);
    t2=microsegundos();
    t=t2-t1;
    if(t<500){
        t1=microsegundos();
        for(i=0;i<K;i++){
            algoritmo(vector,tam);
        }
        t2=microsegundos();
        t=t2-t1;
        t=t/K;
    }

return t;

}


void printTablasTiemposInsercion(){
	int * desc, * asc, * aleat;

	desc=malloc(500 * sizeof(int));
	asc=malloc(500 * sizeof(int));
	aleat=malloc(500 * sizeof(int));
	descendente(desc, 500);
	ascendente(asc, 500);
	aleatorio(aleat, 500);


	int i;
	printf("\nTest ordenación por inserción");
	printf("\n\t   n\t\tascendente\t\tdescendente\t\tdesordenado\n(*)");
	printf("%9d%22.2f%25.6f%24.6f\n", 500,tiempo(ord_ins,asc,500),tiempo(ord_ins,desc,500),tiempo(ord_ins,aleat,500));
	for (i = 1000; i <= 32000; i=i*2)
	{
		desc=malloc(i * sizeof(int));
		asc=malloc(i * sizeof(int));
		aleat=malloc(i * sizeof(int));
		descendente(desc, i);
		ascendente(asc, i);
		aleatorio(aleat, i);

		printf("%12d%22.2f%25.6f%24.6f\n", i,tiempo(ord_ins,asc,i),tiempo(ord_ins,desc,i),tiempo(ord_ins,aleat,i));
	}
}

void printTablasTiemposOrdRap(){
	int * desc, * asc, * aleat;

	desc=malloc(500 * sizeof(int));
	asc=malloc(500 * sizeof(int));
	aleat=malloc(500 * sizeof(int));
	descendente(desc, 500);
	ascendente(asc, 500);
	aleatorio(aleat, 500);


	int i;
	printf("\nTest ordenación rápida");
	printf("\n\t   n\t\tascendente\t\tdescendente\t\tdesordenado\n(*)");
	printf("%9d%22.2f%25.6f%24.6f\n", 500,tiempo(ord_rap,asc,500),tiempo(ord_rap,desc,500),tiempo(ord_rap,aleat,500));
	for (i = 1000; i <= 32000; i=i*2)
	{
		desc=malloc(i * sizeof(int));
		asc=malloc(i * sizeof(int));
		aleat=malloc(i * sizeof(int));
		descendente(desc, i);
		ascendente(asc, i);
		aleatorio(aleat, i);

		printf("%12d%22.2f%25.6f%24.6f\n", i,tiempo(ord_rap,asc,i),tiempo(ord_rap,desc,i),tiempo(ord_rap,aleat,i));
	}
}


void printTablasComplejidadIns(){
	int * desc, * asc, * aleat, i;
	double k=0 , j=0;

	desc=malloc(500 * sizeof(int));
	asc=malloc(500 * sizeof(int));
	aleat=malloc(500 * sizeof(int));
	descendente(desc, 500);
	ascendente(asc, 500);
	aleatorio(aleat, 500);

	printf("\n\nOrdenación por inserción con inicialización ascendente\n");
	printf("\t   n\t\tt(n)\t\tt(n)/n^0.8\t\tt(n)/n\t\tt(n)/n^1.2\n(*)");
	printf("%9d%16.2f%22.6f%22.6f%26.6f\n", 500,tiempo(ord_ins,asc,500),tiempo(ord_ins,asc,500)/pow(500,0.8),tiempo(ord_ins,asc,500)/500,tiempo(ord_ins,asc,500)/pow(500,1.2));

	for (i = 1000; i <= 32000; i=i*2)
	{
		free(asc);
		asc=malloc(i * sizeof(int));
		ascendente(asc, i);

		printf("%12d%16.2f%22.6f%22.6f%26.6f\n", i,tiempo(ord_ins,asc,i),tiempo(ord_ins,asc,i)/pow(i,0.8),tiempo(ord_ins,asc,i)/i,tiempo(ord_ins,asc,i)/pow(i,1.2));
	}

	printf("\n\nOrdenación por inserción con inicialización descendente\n");
	printf("\t   n\t\tt(n)\t\tt(n)/n^1.8\t\tt(n)/n^2\t\tt(n)/n^2.2\n(*)");
	printf("%9d%16.2f%22.6f%22.6f%26.6f\n", 500,j,tiempo(ord_ins,desc,500),tiempo(ord_ins,desc,500)/pow(500,1.8),tiempo(ord_ins,desc,500)/pow(500,2),tiempo(ord_ins,desc,500)/pow(500,2.2));
	for (i = 1000; i <= 32000; i=i*2)
	{
		free(desc);
		desc=malloc(i * sizeof(int));
		ascendente(desc, i);
		printf("%12d%16.2f%22.6f%22.6f%26.6f\n", i,tiempo(ord_ins,desc,i),tiempo(ord_ins,desc,i)/pow(i,1.8),tiempo(ord_ins,desc,i)/pow(i,2),tiempo(ord_ins,desc,i)/pow(i,2.2));
	}

	printf("\n\nOrdenación por inserción con inicialización desordenada\n");
	printf("\t   n\t\tt(n)\t\tt(n)/n^1.8\t\tt(n)/n^2\t\tt(n)/n^2.2\n(*)");
	printf("%9d%16.2f%22.6f%22.6f%26.6f\n", 500,j,tiempo(ord_ins,aleat,500),tiempo(ord_ins,aleat,500)/pow(500,1.8),tiempo(ord_ins,aleat,500)/pow(500,2),tiempo(ord_ins,aleat,500)/pow(500,2.2));
	for (i = 1000; i <= 32000; i=i*2)
	{
		free(aleat);
		aleat=malloc(i * sizeof(int));
		ascendente(aleat, i);
		printf("%12d%16.2f%22.6f%22.6f%26.6f\n", i,tiempo(ord_ins,aleat,i),tiempo(ord_ins,aleat,i)/pow(i,1.8),tiempo(ord_ins,aleat,i)/pow(i,2),tiempo(ord_ins,aleat,i)/pow(i,2.2));
	}
}






int main(){
	int tam = 10;

	inicializar_semilla();
	printf("Ordenacion por insercion\n");
    test(ord_ins, tam);
    printf("\n");

    printf("Ordenacion rápida\n");
    test(ord_rap,tam);
    printf("\n");

	printTablasTiemposInsercion();
	//printTablasTiemposOrdRap();
    printTablasComplejidadIns();

}
