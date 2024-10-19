
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


#define K 10000
#define UMBRAL 1

typedef enum cota{
	CONST, SOBR, SUBS

}cota;

typedef struct tCota{
	double resultado;
	char *string;

}tCota;



void inicializar_semilla() {
	srand(time(NULL));
}


//conseguimos la hora actual del sistema en microsegundos--
double microsegundos() {
struct timeval t;
if (gettimeofday(&t, NULL) < 0 )
return 0.0;
return (t.tv_usec + t.tv_sec * 1000000.0);
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


//FUNCIONES DE MEDIR EL TIEMPO

//FUNCIONES PARA IMPRIMIR LAS TABLAS DE TIEMPOS

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



double tiempo(void (*algoritmo)(int[], int), void (*vec)(int [], int tam), int tam){

	double t1, t=0,t2,aux;
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


int AscDescAleat(int v[], int n){
int i;
for(i=0; i<n;i++){

	if(v[i] == i+1){ //es ascendente
		return 1;
	}else if(v[i] == n - i){ //es descendente
		return 2;
	}
	}
	return 3;
}



tCota CalcularCotaRap(int n , enum cota tipo,int AscDescAleat){
	tCota c;
	c.resultado=0;

	if(AscDescAleat == 1){

		if(tipo==SUBS){
			c.resultado= pow (n,0.8);
			c.string= (UMBRAL==1)? "____[t(n)/n^0.8]____" : "[t(n)/n^2.2]____";



		}else if(tipo=CONST){
			c.resultado= (UMBRAL==1)? pow(n,0.95)*log2(n) :
			 (UMBRAL==10)? pow(n,0.99)*log2(n) : pow(n,1.06)*log2(n);
			c.string= (UMBRAL==1)? "[t(n)/n^0.95 * log2 n]____" : 
			(UMBRAL==10)? "[t(n)/n^0.99 * log2 n]____" : "[t(n)/n^2.2 * log2 n]____";
			

		}else if(tipo=SOBR){
			c.resultado= (UMBRAL==1 || UMBRAL ==10) ? pow(n,1.2) :pow(n,1.3);
			c.string= (UMBRAL==1 || UMBRAL ==10) ? "[t(n)/n^1.2]____" : "[t(n)/n^1.3]____";
			
		}



	}else if(AscDescAleat == 2){

		if(tipo==SUBS){
			c.resultado=n ;
			c.string= "____[t(n)/n]____";

		}else if(tipo=CONST){
			c.resultado= (UMBRAL==1) ? pow(n,1.06) : pow(n,1.1);
			c.string= (UMBRAL==1) ? "[t(n)/n^1.06____]" : "[t(n)/n^1.1]____";;

		}else if(tipo=SOBR){
			c.resultado=pow(n,1.3) ;
			c.string= "[t(n)/n^1.3]____";
		}



	}else{

		if(tipo==SUBS){
			c.resultado=n ;
			c.string="____[t(n)/n]____]" ;

		}else if(tipo=CONST){
			c.resultado=(UMBRAL==1) ? pow(n, 1.01) : (UMBRAL==10) ? pow(n,1.14): pow(n,1.1);
			c.string=(UMBRAL==1)? "[t(n)/n^1.01]____" :(UMBRAL==10)? "[t(n)/n^1.14]____" : "[t(n)/n^1.1]____";

		}else if(tipo=SOBR){
			c.resultado= pow(n,1.4);
			c.string="[t(n)/n^1.4]____" ;
		}



	}
	return c;

}

tCota CalcularCotaInser(int n, enum cota tipo ,int AscDescAleat ){
	tCota c;
	c.resultado=0;

	if(AscDescAleat == 1){
		if(tipo==SUBS){
			c.resultado=pow(n,0.8) ;
			c.string="____[t(n)/n^0.8]____" ;

		}else if(tipo=CONST){
			c.resultado= n;
			c.string= "[t(n)/n]____";

		}else if(tipo=SOBR){
			c.resultado=pow(n,1.2) ;
			c.string= "[t(n)/n^1.2]____";

		}


	}else if(AscDescAleat == 2){

		if(tipo==SUBS){
			c.resultado=pow(n,1.8) ;
			c.string="____[t(n)/n^1.8]____" ;

		}else if(tipo=CONST){
			c.resultado= n*n;
			c.string="[t(n)/n^2]____" ;

		}else if(tipo=SOBR){
			c.resultado=pow(n,2.2) ;
			c.string="[t(n)/n^2.2]____" ;
		}

	}else{

		if(tipo==SUBS){
			c.resultado=pow(n,1.8);
			c.string="___[t(n)/n^1.8]___";

		}else if(tipo=CONST){
			c.resultado= n*n ;
			c.string= "[t(n)/n^2____";

		}else if(tipo=SOBR){
			c.resultado= pow(n,2.2);
			c.string= "t(n)/n^2.2____";
			
			
		}

		

	}
	return c;


}
void printTablasTiempos(){
	int i;
	float j=247.03, k=0.003425;
	printf("\n\t   n\t\tascendente\t\tdescendente\t\tdesordenado\n(*)");
	printf("%9d%22.2f%25.6f%24.6f\n", 500,j,k,k);
	for (i = 1000; i <= 32000; i=i*2)
	{
		printf("%12d%22.2f%25.6f%24.6f\n", i,j,k,k);
	}
}


void printTablasComplejidad(){
	int i;
	float j=247.03, k=0.003425;

	printf("\n\nOrdenación por inserción con inicialización ascendente\n");
	printf("\t   n\t\tt(n)\t\tt(n)/n^1.8\t\tt(n)/n^2\t\tt(n)/n^2.2\n(*)");
	printf("%9d%16.2f%22.6f%22.6f%26.6f\n", 500,j,k,k,k);

	for (i = 1000; i <= 32000; i=i*2)
	{
		printf("%12d%16.2f%22.6f%22.6f%26.6f\n", i,j,k,k,k);
	}

	printf("\n\nOrdenación por inserción con inicialización descendente\n");
	printf("\t   n\t\tt(n)\t\tt(n)/n^1.8\t\tt(n)/n^2\t\tt(n)/n^2.2\n(*)");
	printf("%9d%16.2f%22.6f%22.6f%26.6f\n", 500,j,k,k,k);
	for (i = 1000; i <= 32000; i=i*2)
	{
		printf("%12d%16.2f%22.6f%22.6f%26.6f\n", i,j,k,k,k);
	}

	printf("\n\nOrdenación por inserción con inicialización desordenada\n");
	printf("\t   n\t\tt(n)\t\tt(n)/n^1.8\t\tt(n)/n^2\t\tt(n)/n^2.2\n(*)");
	printf("%9d%16.2f%22.6f%22.6f%26.6f\n", 500,j,k,k,k);
	for (i = 1000; i <= 32000; i=i*2)
	{
		printf("%12d%16.2f%22.6f%22.6f%26.6f\n", i,j,k,k,k);
	}
}






int main(){
	int tam = 10;


    //Ejecución del test
	inicializar_semilla();
	printf("Ordenacion por insercion\n");
    test(ord_ins, tam);
    printf("\n");

    printf("Ordenacion rápida\n");
    test(ord_rap,tam);
    printf("\n");

    //Ejecucion  de los tiempos
    printTablasTiempos();
    printTablasComplejidad();


	


}
