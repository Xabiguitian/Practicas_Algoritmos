
//DEFINICIÓN DE LIBRERÍAS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//DEFINICIÓN DE CONSTANTES
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define LONGITUD_CLAVE 30
#define LONGITUD_SINONIMOS 300




//DEFINICIÓN DE TYPEDEFS

//struct de la entrada al diccionario
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


//UNSIGNED INTS
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



//FUNCIONES DISPERSIÓN CERRADA

//RESOL COLISIONES
unsigned int resol_lineal(int pos_ini, int num_intento) {
	return (unsigned int)(num_intento);
}

unsigned int resol_cuadratica(int pos_ini, int num_intento) {
	return (unsigned int) pow(num_intento,2);
}

unsigned int resol_doble(int pos_ini, int num_intento) {
	return (unsigned int) (num_intento*(10007 - (pos_ini % 10007)));
}




void inicializar_cerrada(tabla_cerrada *diccionario, int tam)
{
	int i;
	for (i=0;i<tam;i++){
		(*diccionario)[i].ocupada=0;
	}
}

pos buscar_cerrada(char *clave, tabla_cerrada diccionario, int tam,
					int *colisiones, unsigned int (*dispersion)(char *, int),
					unsigned int (*resol_colisiones)(int pos_ini, int num_intento))
{
	int i =0;
	int x= dispersion(clave, tam);
	pos posActual=x;

	while(diccionario[posActual].ocupada!=0 && strcmp(diccionario[posActual].clave, clave)!=0){
		i+=1;
		posActual=(x+ resol_colisiones(x, i))%tam;
	}

	*colisiones=i;
	return posActual;
	
}



int insertar_cerrada(char *clave, char *sinonimos, tabla_cerrada *diccionario, int tam,unsigned int (*dispersion)(char *, int),unsigned int (*resol_colisiones)(int pos_ini, int num_intento))
{
	int colisiones=0;
	pos posicion=buscar_cerrada(clave,*diccionario,tam,&colisiones,dispersion,resol_colisiones);
	
	if((*diccionario)[posicion].ocupada!=1){
		strcpy((*diccionario)[posicion].clave,clave);
		strcpy((*diccionario)[posicion].sinonimos,sinonimos);
		(*diccionario)[posicion].ocupada=1;
		
	}
	return colisiones;
}

void mostrar_cerrada(tabla_cerrada diccionario, int tam) {
	int i;
	printf("{\n");
    for (i = 0; i < tam; i++) {
        if (diccionario[i].ocupada==1) {
            printf("%d- (%s )\n", i, diccionario[i].clave);
        } else if(diccionario[i].ocupada==0){
            printf("%d-\n", i);
        }
    }
    printf("}\n");
}


//función  con el ejemplo visto en clase
int ndispersion(char *clave, int tamTabla) {
	if (strcmp(clave, "ANA")==0) return 7;
	if (strcmp(clave, "JOSE")==0) return 7;
	if (strcmp(clave, "OLGA")==0) return 7;
	return 6;
}

unsigned int dispersion(char *clave, int tamTabla) {
	return (unsigned int)ndispersion(clave, tamTabla);
}




//TABLA DE DISPERSIÓN CERRADA CON EXPLORACIÓN LINEAL


//TABLA DE DISPERSIÓN CERRADA CON EXPLORACIÓN CUADRÁTICA
//TABLA DE DISPERSIÓN CERRADA CON EXPLORACIÓN DOBLE


int leer_sinonimos(item datos[]) {
	char c;
	int i, j;
	FILE *archivo;
	if ((archivo = fopen("sinonimos.txt", "r")) == NULL) {
		printf("Error al abrir ’sinonimos.txt’\n");
		return(EXIT_FAILURE);
	}
	for (i = 0; fscanf(archivo, "%s", datos[i].clave) != EOF; i++) {
		if ((c = fgetc(archivo)) != '\t') {
			printf("Error al leer el tabulador\n");
			return(EXIT_FAILURE);
		}
		for (j = 0; (c = fgetc(archivo)) != '\n'; j++) {
			if (j < LONGITUD_SINONIMOS - 1)
			datos[i].sinonimos[j] = c;
		}
		datos[i].sinonimos[MIN(j, LONGITUD_SINONIMOS -1)] = '\0';
	}
	if (fclose(archivo) != 0) {
		printf("Error al cerrar el fichero\n");
		return(EXIT_FAILURE);
	}
	return(i);
}


//CÁLCULO DEL TIEMPO DE EJECUCIÓN
//CÁLCULO DE LAS COMPLEJIDADES


void test(tabla_cerrada *d,unsigned int (*resol_colisiones)(int pos_ini, int intentos), int tamTabla){
	int i;
	pos posicion;
    inicializar_cerrada(d, tamTabla);
	char* claves[] = {"ANA", "LUIS", "JOSE", "OLGA", "ROSA", "IVAN","CARLOS"};
	int colisionesTot=0, colisiones ,colisiones_busqueda;

    for (i=0;i<6; i++) {
    	colisiones=insertar_cerrada(claves[i], "nombre propio", d, tamTabla, dispersion,resol_colisiones);
    	colisionesTot+=colisiones;

    }


    mostrar_cerrada(*d, tamTabla);

	printf("Numero total de colisiones al insertar los elementos: %d\n\n", colisionesTot);

    for (i = 0; i < 7; i++) {
    	colisiones_busqueda=0;
       
        posicion = buscar_cerrada(claves[i], *d, tamTabla, &colisiones_busqueda, dispersion, resol_colisiones);
        if (strcmp((*d)[posicion].clave, claves[i])==0) {
            printf("Al buscar: %s, encuentro: %s, colisiones: %d\n", claves[i], (*d)[posicion].clave, colisiones_busqueda);
        } else {
            printf("No encuentro: %s, colisiones: %d\n\n", claves[i], colisiones_busqueda);
        }
    }
    
}

/*void testS(tabla_cerrada *d,unsigned int (*resol_colisiones)(int pos_ini, int intentos), unsigned int (*disp)()){
	int i;
	pos posicion;
    inicializar_cerrada(d, tamTabla);
	int colisionesTot=0, colisiones ,colisiones_busqueda;


    for (i=0;i<6; i++) {
    	leer_sinonimos(datos[i]);
    	colisiones=insertar_cerrada(datos[i], "nombre propio", d, tamTabla, dispersion,resol_colisiones);
    	colisionesTot+=colisiones;

    }

	printf("Numero total de colisiones al insertar los elementos: %d\n", colisionesTot);

    for (i = 0; i < 7; i++) {
    	colisiones_busqueda=0;
       
        posicion = buscar_cerrada(claves[i], *d, tamTabla, &colisiones_busqueda, dispersion, resol_colisiones);

}*/

void testS(tabla_cerrada *d, unsigned int (*resol_colisiones)(int pos_ini, int intentos), unsigned int (*disp)(char *clave, int tamTabla),  int tamS,item datos[], int numDatos) {
	int i;

	

	inicializar_cerrada(d, tamS);
	

	int colisionesTot=0, colisiones;


    for (i=0;i<numDatos; i++) {
    	colisiones=insertar_cerrada(datos[i].clave, datos[i].sinonimos, d, tamS, disp,resol_colisiones);
    	colisionesTot+=colisiones;

    }

    printf("Insertando %d elementos... Numero total de colisiones: %d\n", tamS, colisionesTot);

}



int main(){
	tabla_cerrada d;
	int tamS =38197;
	item datos[19062];
	int numDatos = leer_sinonimos(datos);
	
 	 
	//tabla_cerrada diccionario;
	int tamTabla =11;
	//int colisiones;
	//int pos;
	

	//int colisiones;
	d = malloc(38197 * sizeof(entrada));
	inicializar_cerrada(&d, tamTabla);
	//CERRADA LINEAL
	printf("***TABLA CERRADA LINEAL\n");
	test(&d,resol_lineal,tamTabla);


	//CERRADA CUADRÁTICA
	printf("***TABLA CERRADA CUADRÁTICA\n");
	test(&d,resol_cuadratica,tamTabla);

	//CERRADA LINEAL
	printf("***TABLA CERRADA DOBLE\n");
	test(&d,resol_doble,tamTabla);


	//SINÓNIMOS
	printf("***Dispersión cerrada lineal con dispersión A\n");
	testS(&d, resol_lineal, dispersionA, tamS,datos,numDatos);


	printf("***Dispersión cerrada lineal con dispersión B\n");
	testS(&d, resol_lineal, dispersionB,  tamS,datos,numDatos);



	printf("***Dispersión cerrada cuadratica con dispersión A\n");
	testS(&d, resol_cuadratica, dispersionA, tamS,datos,numDatos);


	printf("***Dispersión cerrada cuadratica con dispersión B\n");
	testS(&d, resol_cuadratica, dispersionB, tamS,datos,numDatos);


	printf("***Dispersión cerrada doble con dispersión A\n");
	testS(&d, resol_doble, dispersionA,  tamS,datos,numDatos);


	printf("***Dispersión cerrada doble con dispersión B\n");
	testS(&d, resol_doble, dispersionB, tamS,datos,numDatos);




	free(d);
	return 0;

	}
 
