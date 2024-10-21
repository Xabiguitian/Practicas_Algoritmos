#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define LONGITUD_CLAVE 30
#define LONGITUD_SINONIMOS 300
#define TAMV 38197


typedef struct entrada_ {
	int ocupada;
	char clave [LONGITUD_CLAVE];
	char sinonimos [LONGITUD_SINONIMOS];
} entrada;

typedef int pos;

typedef entrada *tabla_cerrada;

typedef struct {
	char clave [LONGITUD_CLAVE];
	char sinonimos [LONGITUD_SINONIMOS];
} item;

tabla_cerrada d = malloc (38197 * sizeof(entrada));


void inicializar_cerrada(tabla_cerrada *diccionario, int tam)
{
	int i;
	for (i=0; i < tam; i++){
		diccionario.ocupada= false;
	}
}

pos buscar_cerrada(char *clave, tabla_cerrada diccionario, int tam,
					int *colisiones, unsigned int (*dispersion)(char *, int),
					unsigned int (*resol_colisiones)(int pos_ini, int num_intento))
{
	
}

int insertar_cerrada(char *clave, char *sinonimos,
					tabla_cerrada *diccionario, int tam,
					unsigned int (*dispersion)(char *, int),
					unsigned int (*resol_colisiones)(int pos_ini, int num_intento))
{

}

void mostrar_cerrada(tabla_cerrada diccionario, int tam)
{

}



int ndispersion(char *clave, int tamTabla) {
	if (strcmp(clave, "ANA")==0) return 7;
	if (strcmp(clave, "JOSE")==0) return 7;
	if (strcmp(clave, "OLGA")==0) return 7;
	return 6;
}




int leer_sinonimos(item datos[]) {
	char c;
	int i, j;
	FILE *archivo;
	if ((archivo = fopen("sinonimos.txt", "r")) == NULL) {
		printf("Error al abrir ’sinonimos.txt’\n");
		return(EXIT_FAILURE);
	}
	for (i = 0; fscanf(archivo, "%s", datos[i].clave) != EOF; i++) {
		if ((c = fgetc(archivo)) != ’\t’) {
			printf("Error al leer el tabulador\n");
			return(EXIT_FAILURE);
		}
		for (j = 0; (c = fgetc(archivo)) != ’\n’; j++) {
			if (j < LONGITUD_SINONIMOS - 1)
			datos[i].sinonimos[j] = c;
		}
		datos[i].sinonimos[MIN(j, LONGITUD_SINONIMOS -1)] = ’\0’;
	}
	if (fclose(archivo) != 0) {
		printf("Error al cerrar el fichero\n");
		return(EXIT_FAILURE);
	}
	return(i);
}



unsigned int dispersionA(char *clave, int tamTabla) {
	int i, n = MIN(8, strlen(clave));
	unsigned int valor = clave[0];
	for (i = 1; i < n; i++)
	valor += clave[i];
	return valor % tamTabla;
}

unsigned int dispersionB(char *clave, int tamTabla) {
	int i, n = MIN(8, strlen(clave));
	unsigned int valor = clave[0];
	for (i = 1; i < n; i++)
	valor = (valor<<5) + clave[i]; /* el desplazamiento de 5 bits equivale a */
	return valor % tamTabla; /* multipicar por 32 */
}