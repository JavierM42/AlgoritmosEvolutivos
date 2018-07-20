#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <assert.h>
#include <tgmath.h>
#include <string>
#include <unistd.h>
#include "variablesGlobales.cpp"
using namespace std;
#define INFINIT 10000


//Variables Globales
int dimension; // calculado
char* terrenos;
int* numeros;
char* puertos;
bool* construccionesOponentes;
int* construcciones;

bool** aristasOcupadas;
bool** caminos;

struct Reserva
{
	float arcilla;
	float trigo;
	float oveja;
	float piedra;
	float madera;
	float puntosDesarrollo;
};

struct Solucion
{
	int poblados;
	int ciudades;
	int puntos_desarrollo;
	int* solucion;
};

float probabilidad(int valor) {
	float prob;
	prob = 0;
	if (valor < 7) {
		prob = (valor-1);
	};
	if (valor > 7) {
		prob = 13 - valor;
	};
	prob = prob/36;
	return prob;
}

void split(string &txt, string* &palabras, char ch, int &tam)
{
	string str = txt;
	int largo = str.length();
	tam = 1;
	int j;
	for (j = 0; j < largo; j++){
		if (str[j] == ch) {
			tam++;
		};
	};
	palabras = new string[tam];
	int encontrados = 0;
	for (j = 0; j < largo; j++) {
		if (str[j] == ch){
			encontrados++;
		} else {
			palabras[encontrados] += str[j];
		};
	};
}

bool comprar(Reserva &tengo, int que_construyo) {
	Reserva quiero;
	switch (que_construyo) {
		case 1:					// camino
			quiero.arcilla = 1;
			quiero.trigo = 0;
			quiero.oveja = 0;
			quiero.piedra = 0;
			quiero.madera = 1;
			break;
		case 2:					// poblado
			quiero.arcilla = 1;
			quiero.trigo = 1;
			quiero.oveja = 1;
			quiero.piedra = 0;
			quiero.madera = 1;
			break;
		case 3:					// ciudad
			quiero.arcilla = 0;
			quiero.trigo = 2;
			quiero.oveja = 0;
			quiero.piedra = 3;
			quiero.madera = 0;
			break;
		case 4:					// carta_desarrollo
			quiero.arcilla = 0;
			quiero.trigo = 5;
			quiero.oveja = 5;
			quiero.piedra = 5;
			quiero.madera = 0;
			break;
	};
	int recursosQueNecesitoTradear = 0;

	//ver qué tengo y qué necesito tradear.
	bool alcanzaArcilla = tengo.arcilla >= quiero.arcilla;
	if(alcanzaArcilla) {
		tengo.arcilla -= quiero.arcilla; //resto y todo bien
	} else {
		recursosQueNecesitoTradear += quiero.arcilla - (int)tengo.arcilla;
		tengo.arcilla -= (int)tengo.arcilla;
	};

	bool alcanzaTrigo = tengo.trigo >= quiero.trigo;
	if(alcanzaTrigo) {
		tengo.trigo -= quiero.trigo; //resto y todo bien
	} else {
		recursosQueNecesitoTradear += quiero.trigo - (int)tengo.trigo;
		tengo.trigo -= (int)tengo.trigo;
	};

	bool alcanzaOveja = tengo.oveja >= quiero.oveja;
	if(alcanzaOveja) {
		tengo.oveja -= quiero.oveja; //resto y todo bien
	} else {
		recursosQueNecesitoTradear += quiero.oveja - (int)tengo.oveja;
		tengo.oveja -= (int)tengo.oveja;
	};

	bool alcanzaPiedra = tengo.piedra >= quiero.piedra;
	if(alcanzaPiedra) {
		tengo.piedra -= quiero.piedra; //resto y todo bien
	} else {
		recursosQueNecesitoTradear += quiero.piedra - (int)tengo.piedra;
		tengo.piedra -= (int)tengo.piedra;
	};

	bool (alcanzaMadera) = tengo.madera >= quiero.madera;
	if(alcanzaMadera) {
		tengo.madera -= quiero.madera; //resto y todo bien
	} else {
		recursosQueNecesitoTradear += quiero.madera - (int)tengo.madera;
		tengo.madera -= (int)tengo.madera;
	};
	//tradear:
	int cant_arcilla = tengo.arcilla / 4;
	recursosQueNecesitoTradear -= cant_arcilla;
	tengo.arcilla = tengo.arcilla - 4 * cant_arcilla;
	int cant_trigo = tengo.trigo / 4;
	recursosQueNecesitoTradear -= cant_trigo;
	tengo.trigo = tengo.trigo - 4 * cant_trigo;
	int cant_oveja = tengo.oveja / 4;
	recursosQueNecesitoTradear -= cant_oveja;
	tengo.oveja = tengo.oveja - 4 * cant_oveja;
	int cant_piedra = tengo.piedra / 4;
	recursosQueNecesitoTradear -= cant_piedra;
	tengo.piedra = tengo.piedra - 4 * cant_piedra;
	int cant_madera = tengo.madera / 4;
	recursosQueNecesitoTradear -= cant_madera;
	tengo.madera = tengo.madera - 4 * cant_madera;
	return (recursosQueNecesitoTradear <= 0);
}

void cobrar_recursos_turno(Reserva &r) {

	for (int i = 2; i <= 12; i++) {
		float prob = probabilidad(i);
		for (int j = 0; j < 19; j++) {
			//obtengo los numeros de los vertices correspodientes al terreno j
			for (int k = 0; k < 6; k++) {
				int vertice = Global::terrenos_vertices[j][k];
				if ((numeros[j] == i) && construcciones[vertice]) {
					// cout << "num_terreno: " << j << ", num_dado: " << numeros[j] << ", terreno: " << terrenos[j] << ", vertice: " << vertice << ", el puto k es: "<< k << endl;
					switch (terrenos[j]) {
						case 'A':
							r.arcilla += (construcciones[vertice] * prob);
							break;
						case 'T': 
							r.trigo += (construcciones[vertice] * prob);
							break;
						case 'O': 
							r.oveja += (construcciones[vertice] * prob);
							break;
						case 'P': 
							r.piedra += (construcciones[vertice] * prob);
							break;
						case 'M': 
							r.madera += (construcciones[vertice] * prob);
							break;
					};
				};
			};
		};
	};
}


void dijkstra(int** cost, int startnode, int* &distance, int* &pred)
{
 	
	int visited[54], count, mindistance;
	int nextnode, i, j;
	
	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	
	//initialize pred[],distance[] and visited[]
	for (i = 0; i < 54; i++)
	{
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}
	
	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;
	
	while (count < (54-1))
	{
		mindistance = INFINIT;
		
		//nextnode gives the node at minimum distance
		for (i = 0; i < 54; i++) {
			if ((distance[i] < mindistance) && (!visited[i])) {
				mindistance = distance[i];
				nextnode = i;
			};
		};
			
		//check if a better path exists through nextnode            
		visited[nextnode]=1;
		for (i = 0; i < 54; i++) {
			if (!visited[i]) {
				if (mindistance+cost[nextnode][i] < distance[i]) {
					distance[i] = mindistance+cost[nextnode][i];
					pred[i] = nextnode;
				};
			};
		};
		count++;
	}
}


void minDistance(int startnode, int &min_distance, int &min_distance_node, int* &path) {
	
	int i, j;
	int columna, fila;

	//hacer grafo turrito, con int[54][54], con G[i][j] = 1 si hay camino y g[i][j] = INFINIT si no.
	int** costo = new int*[54];
	for (i = 0; i < 54; i++) {
		costo[i] = new int[54];
		for (j = 0; j < 54; j++){
			costo[i][j] = INFINIT;
		};
	};

	for (i = 0; i < 72; i++){
		fila = Global::aristas_validas[i][0];
		columna = Global::aristas_validas[i][1];
		costo[fila][columna] = 1;
		costo[columna][fila] = 1;
	};

	for (i = 0; i < 54; i++){			// saco las aristas ocupadas por los oponentes
		for (j = 0; j < 54; j++){
			if (aristasOcupadas[i][j]){
				costo[i][j] = INFINIT;
			}
		};
	};
	for (i = 0; i < 54; i++){			// saco las aristas adyacentes a los vertices con construcciones construccionesOponentes // TODO: pasarlo a AE
		if (construccionesOponentes[i]) {
			for (j = 0; j < 3; j++) {
				int vertice_adyacente = Global::vertices_adyacentes[i][j];
				if (vertice_adyacente >= 0) {
					costo[i][vertice_adyacente] = INFINIT;
					costo[vertice_adyacente][i] = INFINIT;
				};
			};
		};
	};
	int* distancia = new int[54];
	int* predecesor = new int[54];

	dijkstra(costo, startnode, distancia, predecesor);
	min_distance = INFINIT;
	for (i = 0; i < 54; i++) {
		for (j = 0; j < 54; j++) {
			if (caminos[i][j]){	
				if (distancia[i] < min_distance) {
					min_distance = distancia[i];
					min_distance_node = i;
				};
				if (distancia[i] < min_distance) {
					min_distance = distancia[j];
					min_distance_node = j;
				};
			};
		};
	};
	int nodo_aux = min_distance_node;
	path = new int[min_distance + 1];
	for (i = 0; i < min_distance; i++) {
		path[i] = nodo_aux;
		nodo_aux = predecesor[nodo_aux];
	};
	path[min_distance] = startnode;

	delete [] distancia;
	delete [] predecesor;
}

void buscar_lugar_poblado(int &posicion, int &distance, int* &path) {
	int min_distance_aux;
	int min_distance_node_aux;
	int* path_aux;
	distance = INFINIT;

	for (int i = 0; i < 54; i++) {			// Para cada uno de los vertices del tablero
		bool construcciones_vecinas = false;
		for (int j = 0; j < 3; j++) {
			int vertice_adyacente = Global::vertices_adyacentes[i][j];
			if ((vertice_adyacente >= 0) && ((construcciones[vertice_adyacente]) || (construccionesOponentes[vertice_adyacente]))) {
				construcciones_vecinas = true;
			};
		};
		if (!construcciones[i] && !construccionesOponentes[i] && !construcciones_vecinas) {			//Si no hay construcciones de uno o de los demás
			minDistance(i, min_distance_aux, min_distance_node_aux, path_aux);
			
			if (min_distance_aux < distance) {
				posicion = min_distance_node_aux;
				distance = min_distance_aux;
				posicion = i;
				delete [] path;
				path = path_aux;
			} else {
				delete [] path_aux;
			};
		};
	};

}




int main(int argc, char* argv[])	//	MAIN	-	MAIN	-	MAIN	-	MAIN	-	MAIN	-	MAIN	-	MAIN	-	MAIN
{
	//	INICIALIZAR LAS VARIABLES DEL PROBLEMA
	string s;
	ifstream infile;
	string asterisco = "*";

	//Variables del problema
	Reserva reserva;
	terrenos = new char[19];
	numeros = new int[19];
	puertos = new char[9];
	construccionesOponentes = new bool[54];
	construcciones = new int[54];
	aristasOcupadas = new bool*[54];
	caminos = new bool*[54]; 			// Los caminos son míos

	for (int i = 0; i < 54; i++) {
		aristasOcupadas[i] = new bool[54];
		caminos[i] = new bool[54];
		for (int j = 0; j < 54; j++){
			aristasOcupadas[i][j] = false;
			caminos[i][j] = false;
		}
	};

	infile.open("codificacion_turrita.txt");

	//	LEER DATOS DE ENTRADA	-	LEER DATOS DE ENTRADA	-	LEER DATOS DE ENTRADA	-	LEER DATOS DE ENTRADA	-	LEER DATOS DE ENTRADA
	string* v;
	string* v2;
	string arista;
	int i, j;
	int fila, columna;
	int size, size2;
	Solucion sol;
	sol.poblados = 0;
	sol.ciudades = 0;
	sol.puntos_desarrollo = 0;

	s = "basura";
	while (s != asterisco){
		getline(infile, s);
		split(s, v, ' ', size);
		if (v[0] == "terrenos:") {
			if ((size-1) != 19) {
				cout << "Los cantidad de terrenos no es correcta, debe haber 19 y hay: " << size << endl;
				return 0;
			};
			for (i = 0; i < 19; i++) {
				terrenos[i] = v[i+1][0];
			};
		};
		if (v[0] == "numeros:") {
			if ((size-1) != 19) {
				cout << "Los cantidad de numeros no es correcta, debe haber 19 y hay: " << size << endl;
				return 0;
			};
			for (i = 0; i < 19; i++) {
				if (v[i+1] == "-1") {
					numeros[i] = -1;
				} else {
					numeros[i] = stoi(v[i+1]);
				}
			};
		};
		if (v[0] == "puertos:") {
			if ((size-1) != 9) {
				cout << "Los cantidad de puertos no es correcta, debe haber 9 y hay: " << size << endl;
				return 0;
			};
			for (i = 0; i < 9; i++) {
				puertos[i] = v[i+1][0];
			};
		};
		if (v[0] == "construccionesOponentes:") {
			if ((size-1) != 54) {
				cout << "Los cantidad de construcciones oponentes no es correcta, debe haber 54 y hay: " << size << endl;
				return 0;
			};
			for (i = 0; i < 54; i++) {
				construccionesOponentes[i] = (v[i+1] == "1");
			};
		};
		if (v[0] == "aristasOcupadas:") {
			for (i = 1; i < size; i++) {
				arista = v[i];			//sacarle los parentesis
				split(arista, v2, ',', size2);
				fila = stoi(v2[0]);
				columna = stoi(v2[1]);
				aristasOcupadas[fila][columna] = true;
				aristasOcupadas[columna][fila] = true;
			};
		};
		if (v[0] == "construcciones:") {
			if ((size-1) != 54) {
				cout << "Los cantidad de construcciones no es correcta, debe haber 54 y hay: " << size << endl;
				return 0;
			};
			for (i = 0; i < 54; i++) {
				construcciones[i] = stoi(v[i+1]);
				if (construcciones[i] == 1) {
					sol.poblados++;
				};
				if (construcciones[i] == 2) {
					sol.ciudades++;
				};
			};
		};
		if (v[0] == "caminos:") {
			for (i = 1; i < size; i++) {
				arista = v[i];			//sacarle los parentesis
				split(arista, v2, ',', size2);
				fila = stoi(v2[0]);
				columna = stoi(v2[1]);
				// cout << fila << "," << columna << "   ";
				caminos[fila][columna] = true;
				caminos[columna][fila] = true;
				//agregar a la amtriz o a la estructura magica de dijkstra
			};
		};
		if (v[0] == "reserva:") {
			// cout << "reserva: " << endl;
			for (i = 1; i < size; i++) {
				string coso = v[i];			//sacarle los parentesis
				split(coso, v2, ':', size2);
				if (v2[0] == "T") {
					reserva.trigo = stoi(v2[1]);
					// cout << "    trigo: " << reserva.trigo;
				};
				if (v2[0] == "A") {
					reserva.arcilla = stoi(v2[1]);
					// cout << "    arcilla: " << reserva.arcilla;
				};
				if (v2[0] == "M") {
					reserva.madera = stoi(v2[1]);
					// cout << "    trigo: " << reserva.trigo;
				};
				if (v2[0] == "O") {
					reserva.oveja = stoi(v2[1]);
					// cout << "    madera: " << reserva.madera;
				};
				if (v2[0] == "P") {
					reserva.piedra = stoi(v2[1]);
					// cout << "    piedra: " << reserva.piedra;
				};
				if (v2[0] == "puntos") {
					reserva.puntosDesarrollo = stoi(v2[1]);
					// cout << "    puntosDesarrollo: " << reserva.puntosDesarrollo;
					sol.puntos_desarrollo = reserva.puntosDesarrollo;
				};
			};
			// cout << endl;
		};
		// if (v != NULL){
		// 	delete [] v;
		// };
		// if (v2 != NULL){
		// 	delete [] v2;
		// };
	};

	infile.close();

	int puntosObtenidos = sol.puntos_desarrollo;
	for(int i=0; i<54; i++) {
		puntosObtenidos += construcciones[i];
	};
	dimension = 10 - puntosObtenidos;
	int puntos_victoria = 0;
	sol.solucion = new int[dimension];

	//	GREEDY	-	GREEDY	-	GREEDY	-	GREEDY	-	GREEDY	-	GREEDY	-	GREEDY	-	GREEDY	-	GREEDY	-	GREEDY	-	GREEDY
	int turnos = 0;
	bool puedo;
	int lugar;
	int posicion;
	int distance;
	int* path;
	Reserva r2 = reserva;
	while (puntos_victoria < dimension) {
		turnos++;
		// cout << turnos << endl;
		cobrar_recursos_turno(reserva);					// Cobra los recursos del turno
		r2 = reserva;
		if (comprar(r2, 2)) {							// Si puedo construir un poblado
			// cout << "puedo comprar un poblado" << endl;
			comprar(reserva, 2);
			buscar_lugar_poblado(posicion, distance, path);
			r2 = reserva;
			for (i = 0; i < distance; i++){
				while (!comprar(r2, 1)) {			// Mientras no pueda construir el camino
					turnos++;
					cobrar_recursos_turno(reserva);
					r2 = reserva;
				};
				comprar(reserva, 1);
				caminos[path[i]][path[i+1]] = true;
				caminos[path[i+1]][path[i]] = true;
				r2 = reserva;
			};
			sol.solucion[puntos_victoria] = posicion;
			construcciones[posicion]++;
			puntos_victoria++;
			sol.poblados++;
		};
		r2 = reserva;
		if (comprar(r2, 3) && (sol.poblados > sol.ciudades) && (sol.ciudades <= 4)) {		// Veo si puedo construir una ciudad
			// cout << "puedo comprar una ciudad" << endl;
			comprar(reserva, 3);															// Construyo ciudad
			//seleccionar que ciudad polentear
			for (int i = 0; i < 54; i++) {
				if (construcciones[i] == 1) {
					lugar = i;
				};
			};
			sol.solucion[puntos_victoria] = lugar;
			construcciones[lugar]++;
			puntos_victoria++;
			sol.ciudades++;
		};
		r2 = reserva;
		if (comprar(r2, 4) && (sol.puntos_desarrollo <= 4)) {		// Veo si puedo comprar una carta_desarrollo y que tengo menos de 5
			// cout << "puedo comprar una carta_desarrollo" << endl;
			comprar(reserva, 4);									// Compro carta_desarrollo
			sol.solucion[puntos_victoria] = -1;
			puntos_victoria++;
			sol.puntos_desarrollo++;
			r2 = reserva;
		};
	};
	cout << "La solución es:  ";
	for (int i = 0; i < dimension; i++) {
		cout << sol.solucion[i] << " ";
	};
	cout << endl;
	cout << "El fitness es:   " << turnos << endl;


	return 0;
}







