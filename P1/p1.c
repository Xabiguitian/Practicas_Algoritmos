#include <stdio.h>
#include <math.h>
#include <sys/time.h>


 //FUNCION FIBONACCI 1
int fib1(int n){

	if(n<2){
		return n;
	}else 
		return (fib1(n-1)+fib1(n-2));
}



//FUNCIÓN FIBONACCI 2

int fib2(int n){
	int i =1, j=0;
	for(int k=1;k<=n;k++){
		j=i+j;
		i=j-i;
	}

	return j;
}


//FUNCIÓN FIBONACCI 3


int fib3(int n){
	int i=1, j=0,k=0,h=1,t=0;
	while(n>0){
		if(n%2!=0){
			t=j*h;
			j=i*h+j*k+t;
			i=i*k+t;
		}
		t =h*h ;
		h = 2*k*h + t ;
		k =k*k+t ;
		n =n/2;
		
	}
	return j;

}


//FUNCIÓN VOID TEST
 

void test(){
	printf("Validacion de los algoritmos:\n");
	printf(" n\t\t fib1\t\t fib2\t\t fib3\n");
	for(int  n=0;n<=20;n++){
		printf("%2d\t\t%5d\t\t%5d\t\t%5d\n",n,fib1(n),fib2(n),fib3(n));
	}
	printf("\n\n");
}


//FUNCIÓN MICROSEGUNDOS

double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}


void medicionesFib1(){
	double t1=0, t2=0, t, x, y, z;
	printf("fib1\n    \t   n\t\t   t\t  t/pow(1.1,n)\t  t/pow((1+sqrt(5))/2,n)\tt/pow(2, n)\titeraciones\n");
	for(int n=2;n<=32;n=n*2){
		int i=0;
		
		t1 = microsegundos();
		while(t2 - t1 < 500){
			
			fib1(n);
			t2 = microsegundos();
			i++;
		}
		t=(t2-t1)/i;

		x = t / pow(1.1, n);
		y = t / pow((1+sqrt(5))/2, n);
		z = t / pow(2, n);
		printf("%12d%16.3f%18.6f%26.6f%19.6f%16d\n", n, t, x, y, z, i);
	}
}



void medicionesFib2(){
	double t1, t2, t, x, y, z;
	printf("\nfib2\n    \t   n\t\t   t\t  t/pow(n,0.8)\t\t\t     t/n       t/(n*log(n))\titeraciones\n");
	for(int n=1000;n<=10000000;n=n*10){
		
		int i=0;
		
		t1 = microsegundos();
		while(t2 - t1 < 500){
			
			fib2(n);
			t2 = microsegundos();
			i++;
		}
		t=(t2-t1)/i;

		x = t / pow(n, 0.8);
		y = t / n;
		z = t / (n*log(n));
		printf("%12d%16.3f%18.6f%26.6f%19.6f%16d\n", n, t, x, y, z,i);
	}
}


void medicionesFib3(){
	double t1, t2, t, x, y, z;

	printf("\nfib3\n    \t   n\t\t   t\tt/sqrt(log(n))\t\t\tt/log(n)      t/pow(n, 0.5)\titeraciones\n");
	for(int n=1000;n<=10000000;n=n*10){
		
		int i=0;
		
		t1 = microsegundos();
		while(t2 - t1 < 500){
			
			fib3(n);
			t2 = microsegundos();
			i++;
		}
		t=(t2-t1)/i;

		x = t / sqrt(log(n));
		y = t / log(n);
		z = t / pow(n, 0.5);
		printf("%12d%16.3f%18.6f%26.6f%19.6f%16d\n", n, t, x, y, z, i);
	}
}




int main() {
	test();
	medicionesFib1();
	medicionesFib2();
	medicionesFib3();
	
}
