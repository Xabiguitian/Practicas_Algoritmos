
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



   



double tiempo(void (*algoritmo)(int[], int), void (*vec) (int [],int), int tam){

	double t1, t,t2,aux;
	int *v;
	int i;


	v= malloc(tam *sizeof(int));
	vec(v, tam);

	t1=microsegundos();
	algoritmo(v,tam);
	t2=microsegundos();
	t=t2-t1;
	if(t<500){
		t1=microsegundos();
		for(i=0;i<K;i++){
			vec(v,tam);
			algoritmo(v,tam);
		}
		t2=microsegundos();
		aux=t2-t1;
		t1=microsegundos();
		for(i=0;i<K;i++){
			vec(v,tam);
		}
		t2=microsegundos();
		t=t2-t1;
		t=(aux-t)/K;
	}


free (v);
return t;

}


void printTablasComplejidadIns(){
	int * desc, * asc, * aleat, i;
	


	printf("\n\nOrdenación por inserción con inicialización ascendente\n");
	printf("\tn\t\tt(n)\t\tt(n)/n^0.8\t\tt(n)/n\t\tt(n)/n^1.2\n(*)");
	
	for (i = 500; i <= 32000; i=i*2)
	{
		
		asc=malloc(i * sizeof(int));
		ascendente(asc, i);

		printf("%12d%16.2f%22.6f%22.6f%26.6f\n", i,tiempo(ord_ins,ascendente,i),
			tiempo(ord_ins,ascendente,i)/pow(i,0.8),tiempo(ord_ins,ascendente,i)/i,tiempo(ord_ins,ascendente,i)/pow(i,1.2));
	}

	printf("\n \nOrdenación por inserción con inicialización descendente\n");
	printf("\tn\t\tt(n)\t\tt(n)/n^1.8\t\tt(n)/n^2\t\tt(n)/n^2.2\n(*)");
	for (i = 500; i <= 32000; i=i*2)
	{
		
		desc=malloc(i * sizeof(int));
		descendente(desc, i);
		printf("%12d%16.2f%22.6f%22.6f%26.6f\n", i,tiempo(ord_ins,descendente,i),tiempo(ord_ins,descendente,i)/pow(i,1.8),tiempo(ord_ins,descendente,i)/pow(i,2),tiempo(ord_ins,descendente,i)/pow(i,2.2));
	}

	printf("\n\nOrdenación por inserción con inicialización desordenada\n");
	printf("\n\t\tt(n)\t\tt(n)/n^1.8\t\tt(n)/n^2\t\tt(n)/n^2.2\n(*)");
	for (i = 500; i <= 32000; i=i*2)
	{
		
		aleat=malloc(i * sizeof(int));
		aleatorio(aleat, i);
		printf("%12d%16.2f%22.6f%22.6f%26.6f\n", i,tiempo(ord_ins,aleatorio,i),tiempo(ord_ins,aleatorio,i)/pow(i,1.8),tiempo(ord_ins,aleatorio,i)/pow(i,2),tiempo(ord_ins,aleatorio,i)/pow(i,2.2));
	}
}

void printTablasComplejidadRap(){
	int * desc, * asc, * aleat, i;
	


	printf("\n\nnOrdenación Rápida con inicialización ascendente\n");
	printf("\tn\t\tt(n)\t\tt(n)/n^0.8\t\tt(n)/n\t\tt(n)/n^1.2\n(*)");
	for (i = 500; i <= 32000; i=i*2)
	{
		
		asc=malloc(i * sizeof(int));
		ascendente(asc, i);

		printf("%12d%16.2f%22.6f%22.6f%26.6f\n", i,tiempo(ord_rap,ascendente,i),tiempo(ord_rap,ascendente,i)/pow(i,0.8),
			tiempo(ord_rap,ascendente,i)/(pow(i,0.95)*log2(i)),tiempo(ord_rap,ascendente,i)/pow(i,1.2));
	}

	printf("\n\nOrdenación Rápida con inicialización descendente\n");
	printf("\tn\t\tt(n)\t\tt(n)/n^1.8\t\tt(n)/n^2\t\tt(n)/n^2.2\n(*)");
	for (i = 500; i <= 32000; i=i*2)
	{
		
		desc=malloc(i * sizeof(int));
		descendente(desc, i);
		printf("%12d%16.2f%22.6f%22.6f%26.6f\n", i,tiempo(ord_rap,descendente,i),tiempo(ord_rap,descendente,i)/i,
			tiempo(ord_rap,descendente,i)/pow(i,1.06),tiempo(ord_rap,descendente,i)/pow(i,1.3));
	}

	printf("\n\nOrdenación Rápida con inicialización desordenada\n");
	printf("\tn\t\tt(n)\t\tt(n)/n^1.8\t\tt(n)/n^2\t\tt(n)/n^2.2\n(*)");
	for (i = 500; i <= 32000; i=i*2)
	{
		
		aleat=malloc(i * sizeof(int));
		aleatorio(aleat, i);
		printf("%12d%16.2f%22.6f%22.6f%26.6f\n", i,tiempo(ord_rap,aleatorio,i),tiempo(ord_rap,aleatorio,i)/i,
			tiempo(ord_rap,aleatorio,i)/pow(i,1.1),tiempo(ord_rap,aleatorio,i)/pow(i,1.4));
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

    printTablasComplejidadIns();
    printTablasComplejidadRap();

}
