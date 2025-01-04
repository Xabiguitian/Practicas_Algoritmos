#include <stdio.h>
#include <math.h>
#include <sys/time.h>

// FUNCIONES FIBONACCI

int fib1(int n) {
    if (n < 2) return n;
    return fib1(n - 1) + fib1(n - 2);
}

int fib2(int n) {
    int i = 1, j = 0;
    for (int k = 1; k <= n; k++) {
        j = i + j;
        i = j - i;
    }
    return j;
}

int fib3(int n) {
    int i = 1, j = 0, k = 0, h = 1, t = 0;
    while (n > 0) {
        if (n % 2 != 0) {
            t = j * h;
            j = i * h + j * k + t;
            i = i * k + t;
        }
        t = h * h;
        h = 2 * k * h + t;
        k = k * k + t;
        n = n / 2;
    }
    return j;
}

// FUNCIONES AUXILIARES

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0) return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

double medir_tiempo(int (*fib)(int), int n) {
    double t1, t2, t, aux;
    int K = 1000;

    t1 = microsegundos();
    fib(n);
    t2 = microsegundos();
    t = t2 - t1;

    if (t < 500) {
        t1 = microsegundos();
        for (int i = 0; i < K; i++) fib(n);
        t2 = microsegundos();
        aux = t2 - t1;

        t1 = microsegundos();
        for (int i = 0; i < K; i++);
        t2 = microsegundos();
        t = (aux - (t2 - t1)) / K;
    }

    return t;
}

// VALIDACIÓN DE LOS ALGORITMOS
void validar_algoritmos() {
    printf("Validación de los algoritmos:\n");
    printf("  n\t  fib1\t  fib2\t  fib3\n");
    for (int n = 0; n <= 20; n++) {
        printf("%3d\t%6d\t%6d\t%6d\n", n, fib1(n), fib2(n), fib3(n));
    }
    printf("\n");
}

// MEDICIONES

void medicionesFib1() {
    printf("\t   n\t\t    t(n)\t\t       t(n)/1.1^n\t\t   t(n)/φ^n\t\t       t(n)/2^n\n");
    double phi = (1 + sqrt(5)) / 2;
    for (int n = 2; n <= 32; n *= 2) {
        double t = medir_tiempo(fib1, n);
        printf("%12d\t%16.6f\t%25.6f\t%19.6f\t%23.6f\n", n, t, t / pow(1.1, n), t / pow(phi, n), t / pow(2, n));
    }
    printf("\n");
}

void medicionesFib2() {
    printf("\t   n\t\t    t(n)\t\t       t(n)/n^0.8\t\t     t(n)/n\t\tt(n)/(n*log(n))\n");
    for (int n = 1000; n <= 10000000; n *= 10) {
        double t = medir_tiempo(fib2, n);
        printf("%12d\t%16.6f\t%25.6f\t%19.6f\t%23.6f\n", n, t, t / pow(n, 0.8), t / n, t / (n * log(n)));
    }
    printf("\n");
}

void medicionesFib3() {
    printf("\t   n\t\t    t(n)\t\tt(n)/sqrt(log(n))\t\tt(n)/log(n)\t\t     t(n)/n^0.5\n");
    for (int n = 1000; n <= 10000000; n *= 10) {
        double t = medir_tiempo(fib3, n);
        printf("%12d\t%16.6f\t%25.6f\t%19.6f\t%23.6f\n", n, t, t / sqrt(log(n)), t / log(n), t / pow(n, 0.5));
    }
    printf("\n");
}

// FUNCIÓN PRINCIPAL

int main() {
    validar_algoritmos();
    medicionesFib1();
    medicionesFib2();
    medicionesFib3();
    return 0;
}