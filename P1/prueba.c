#include <stdio.h>
#include <sys/time.h>


 //FUNCION FIBONACCI 1
int fib1(int n){

	if(n<2){
		return n;
	}else 
		return (fib1(n-1)+fib1(n-2));
}

//FUNCIÓN MICROSEGUNDOS

double microsegundos() {
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

int main() {
	double t1, t2, t;
	t1 = microsegundos();
	fib1(32);
	t2 = microsegundos();
	t=(t2-t1);
	printf("%f\n", t);
	
}