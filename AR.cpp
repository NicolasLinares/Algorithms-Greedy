#include <stdlib.h> 
#include <string.h>  
#include <iostream>  
using namespace std;

#define MAX_ALUMNOS 100

int amistad[MAX_ALUMNOS][MAX_ALUMNOS];
int trabajo[MAX_ALUMNOS][MAX_ALUMNOS]; 
int total, alumnos;

void leerEntrada(){
	cin >> alumnos;
	
	for (int i= 0; i<alumnos; i++) {
		for (int j= 0; j<(alumnos); j++) {
			if(i == j ) 
				amistad[i][j] = 0;
			else{
				cin >> amistad[i][j];
			}
		}
	} 

	for (int i= 0; i<alumnos; i++) {
		for (int j= 0; j<(alumnos); j++) {
			if(i == j ) trabajo[i][j] =0;
			else{
				cin >> trabajo[i][j];
			}
		}
	} 

}

bool solucion(int * s){
	int n = 0;
	for (int i=0; i < alumnos ; i++){ 
		if( s[i] == -2) n++;
	}
	return n <= 1; // n == 0 ó n == 1, significa que están todos seleccionados o que hay uno que se queda solo
				   // si  n > 1 todavía no es solución 
}

int seleccionar( int alumnoActual, bool * c){
	
	int mejorAlumno=-1;
	int compenetracion=-1;
	int aux=0;
	
	for(int candidato = 0; candidato < alumnos; candidato++){
		if(c[candidato]){
			aux = (amistad[alumnoActual][candidato] + amistad[candidato][alumnoActual]) * (trabajo[alumnoActual][candidato] + trabajo[candidato][alumnoActual]);
			if(aux > compenetracion){
				compenetracion = aux;
				mejorAlumno = candidato;
			}
		}
	}
	// Alumnos ya seleccionados, por lo que debemos descartarlos del conjunto de candidatos
	c[alumnoActual] = false;
	c[mejorAlumno] = false;
	
	total+= compenetracion;
	return mejorAlumno;
	
}

void mostrarParejas(int * s){
	
	cout << total <<endl;
	
	int solo = -1;
	for (int i=0; i < alumnos ; i++){ 
		if( s[i] >= 0)  cout << i << " " << s[i] << " ";
		if ( s[i] == -2) solo = i; 
	}
	
	if (solo != -1)  cout << solo;
	cout << endl;
}

void insertar(int alumnoActual, int pareja, int * s){
	s[alumnoActual] = pareja;
	s[pareja] = -1;
}

void avanceRapido(bool * c, int * s){
	
	//INICIALIZACIÓN: 
	for (int i=0; i < alumnos ; i++){ 	
		c[i] = true; // True porque no se han seleccionado.
		s[i] = -2;  // Solución vacía: -2 significa que no ha sido comprobado.
					//				  -1 significa que es pareja de alguien.
	}
	
	int alumnoActual=0; 
	
	//SOLUCIÓN: que todos los alumnos estén emparejados, pudiendo quedar uno solo.
	while(alumnoActual < alumnos && !solucion(s)) {
		//SELECCIONAR: seleccionamos el mejor candidato de la fila y columna alumnoActual.
		 int pareja = seleccionar(alumnoActual, c);
		 //FACTIBLE: siempre será verdadero.
		 //INSERTAR: inserta en el array solución.
		 insertar(alumnoActual, pareja, s);
		 
		 while(alumnoActual < alumnos && s[alumnoActual] != -2)
			alumnoActual++; //avanza hasta que encuentre un alumno que no ha sido escogido
	}
	
	if (!solucion(s))
		cout << " No se puede encontrar solución" << endl;
}

int main (void){
    int ncasos;
    cin >> ncasos;

    for (int i= 0; i<ncasos; i++) {
		total = 0;

		leerEntrada();
		int * solucion = new int[alumnos]();
		bool * candidatos =  new bool[alumnos]();
		avanceRapido(candidatos, solucion);  
		mostrarParejas(solucion);
		
		delete[] solucion;
		
	}
	
}
