
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
void ordenaciónInsercion(char v[]){
	int i,n,x,j;

	for(i=2;i<n;i++){
		x=v[i];
		j=i-1;
		while(j>0 && v[j]>x){
			v[j+1]=v[j];
			j=j-1;

		}
		v[j+1]=x;
	}
}

/*void ord_ins (int v [], int n) {
	int i, j,x;


	for(i=2;i<=n;i++){
		x = v[i];
		j = j-1;
		while (j>0 && v[j]>x){
			v[j+1] = v[j];
			j=j-1;;
		}
		v[j+1]=x;
	}
}*/



void ordenaciónAuxiliar(char v[]){
	int iz=0, dr,x,i,j, pivote;

	for (dr = 0; v[i]!=NULL; dr++);

	if(iz<dr){
		x=8;//CORREGIR
		pivote=v[x];
		intercambiar(v[iz],v[x]); //mirar función intercambiar
		i=iz+1;
		j=dr;
		while(i<=j){
			while(i<=dr&&v[i]<pivote){
				i=i+1;
			}

			while(v[j]>pivote){
				j=j-1;
				if(i<=j){
					intercambiar(v[1],v[j]);
					i=i+1;
					j=j-1;

			}
				}
				intercambiar(v[iz], v[j]);
				ordenaciónAuxiliar(v[iz,j-1]);
				ordenaciónAuxiliar(v[j+1,dr])
		}
		

	}
}

void ord_rap_aux (int v [], int iz, int dr) {
/* ... */
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
	for(i=0;i<n;i--){
		v[i-1]=j;

	}

}


void printVector(int v[], int n){
	int i;
	printf("[");
	for(i=0;i<n;i++){
		printf("%2d",v[i]);
	}
	printf("]\n");
}



//FUNCIÓN VOID TEST

void test(){

	printf(" n\t\t fib1\t\t fib2\t\t fib3\n");
	for(int  n=0;n<=20;n++){
		printf("%2d\t\t%5d\t\t%5d\t\t%5d\n",n,fib1(n),fib2(n),fib3(n));
	}
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

	inicializar_semilla();
	test();
	


}
