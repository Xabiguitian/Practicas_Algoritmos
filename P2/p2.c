
//P2
//para cada algoritmo va haber 3 tablas en el informe
//proporcionan lass funciones de semilla, aleatorio y ascendente, desas funciones hay que hacer la FUNCIÓN SEMILLA


//En esta práctica se van a implementar los algoritmos de inserción y de ordenación rápida con selección aleatoria del pivote.

//La práctica consiste en ordenar un vector de n numeros enteros





#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>





//CÓDIGOS PROPORCIONADOS EN LA PRÁCTICA
//CÓDIGO DE LOS ALGORITMOS DE INSERCIÓN Y DE ORDENACIÓN RÁPIDA

//FUNCIONES PROGRAMA
void ord_ins(int v[], int n){
	int i,x,j;

	for(i=1;i<n;i++){
		x=v[i];
		j=i-1;
		while(j>0 && v[j]>x){
			v[j+1]=v[j];
			j=j-1;

		}
		v[j+1]=x;
	}
}


void intercambiar(int a, int b) {
	int auxiliar;

	auxiliar=a;
	a=b;
	b=auxiliar;
}



void ord_rap_aux(int v[], int iz, int dr){
	int x,i,j, pivote;

	if(iz<dr){
		int m=2*dr+1;


		x = (rand() % m) - dr;;//CORREGIR
		pivote=v[x];
		intercambiar(v[iz],v[x]); //mirar función intercambiar
		i=iz+1;
		j=dr;
		while(i<=j){
			while(i<=dr&&v[i]<pivote){
				i+=1;
			}

			while(v[j]>pivote){
				j-=1;
				
			}

			if(i<=j){
					intercambiar(v[i],v[j]);
					i+=1;
					j-=1;

			}
			
			intercambiar(v[iz], v[j]);
			ord_rap_aux(v, iz, j-1);
			ord_rap_aux(v, j+1, dr)
		}
		

	}
}


void ord_rap (int v [], int n) {
	ord_rap_aux(v, 0, n-1);
}



void inicializar_semilla() {
	srand(time(NULL));
}

void aleatorio(int v [], int n) {/* se generan números pseudoaleatorio entre -n y +n */
	int i, m=2*n+1;
	for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;
}



void ascendente(int v [], int n) {
	int i;
	for (i=0; i < n; i++)
		v[i] = i;
}

void descendente(int v[], int n){
	int i,j=0;
	for(i=0; i < n; i++){
		v[i] = n - i;

	}

}


void printVector(int v[], int n){
	int i;
	for(i=0;i<n;i++){
		printf("%3d",v[i]);
	}
	printf("\n");
}


bool ordenado(int v[], int n){
	int i;
	for(i=0;i<n;i++){
    	if(v[i]>v[i+1]){
      		return false;
        }
  	}

  	return true;
}


//FUNCIÓN VOID TEST

void test(void (*algoritmo)(int[], int), int tamV){
	int * desc, * asc, * aleat;
    int aux;

	//vectores vacíos
	desc=malloc(tamV * sizeof(int));
	asc=malloc(tamV * sizeof(int));
	aleat=malloc(tamV * sizeof(int));


	ascendente(asc, tamV);
	descendente(desc,tamV);
	aleatorio(aleat,tamV);

    printf("Inicialización aleatoria.\n");
    printVector(aleat,tamV);
    printf("Ordenado? %d\nordenando...",ordenado(aleat,tamV));
    algoritmo(aleat,tamV);
    printVector(aleat,tamV);
    printf("ordenado? %d\n",ordenado(aleat,tamV));

	printf("Inicialización ascendente.\n");
    printVector(asc,tamV);
	printf("Ordenado? %d\nordenando...",ordenado(asc,tamV));
    algoritmo(asc,tamV);
	printVector(asc,tamV);
	printf("ordenado? %d\n",ordenado(asc,tamV));

	printf("Inicialización descendente.\n");
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






int main(){
	int tam = 10;

	inicializar_semilla();
	printf("Ordenacion por insercion\n");
    test(ord_ins, tam);
    printf("\n");

    printf("Ordenacion rápida\n");
    test(ord_rap,tam);
    printf("\n");
	


}