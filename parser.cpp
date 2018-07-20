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


struct Reserva //user defined datatype
{
	int arcilla;
	int trigo;
	int oveja;
	int piedra;
	int madera;
	int puntosDesarrollo;
};


void split(string &txt, string* &palabras, char ch, int &tam)
{
	// recorrer y encontrar cuantos espacios hay
	//crear array de tamaño n+1
	//volver a recorrer y agregar al array
	string str = txt;
	int largo = str.length();
	tam = 1;
	int j;
	for (j = 0; j < largo; j++){
		if (str[j] == ch) {
			tam++;
		};
	};
	// delete [] palabras;
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
		for (i = 0; i < 54; i++)
			if ((distance[i] < mindistance) && (!visited[i])) {
				mindistance = distance[i];
				nextnode = i;
			}
			
			//check if a better path exists through nextnode            
			visited[nextnode]=1;
			for (i = 0; i < 54; i++)
				if (!visited[i])
					if (mindistance+cost[nextnode][i] < distance[i])
					{
						distance[i] = mindistance+cost[nextnode][i];
						pred[i] = nextnode;
					}
		count++;
	}
 
	//print the path and distance of each node
	// for (i=0; i<n; i++)
	//     if (i != startnode)
	//     {
	//         printf("\nDistance of node%d=%d",i,distance[i]);
	//         printf("\nPath=%d",i);
			
	//         j=i;
	//         do
	//         {
	//             j=pred[j];
	//             printf("<-%d",j);
	//         }while(j!=startnode);
	// }

}


void minDistance(bool** aristasOcupadas, bool** caminos, int startnode, int &min_distnace, int &min_distnace_node, int* &path) {
	
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

	for (i = 0; i < 54; i++){
		for (j = 0; j < 54; j++){
			if (aristasOcupadas[i][j]){
				costo[i][j] = INFINIT;
			}
		};
	};
	int* distancia = new int[54];
	int* predecesor = new int[54];
	dijkstra(costo, startnode, distancia, predecesor);
	
	min_distnace = INFINIT;
	for (i = 0; i < 54; i++) {
		for (j = 0; j < i; j++) {
			if (caminos[i][j]){
				if (distancia[i] < min_distnace) {
					min_distnace = distancia[i];
					min_distnace_node = i;
				};
				if (distancia[i] < min_distnace) {
					min_distnace = distancia[j];
					min_distnace_node = j;
				};
			};
		};
	};
	int nodo_aux = min_distnace_node;
	path = new int[min_distnace + 1];
	for (i = 0; i < min_distnace; i++) {
		path[i] = nodo_aux;
		nodo_aux = predecesor[nodo_aux];
	};
	path[min_distnace] = startnode;


	delete [] distancia;
	delete [] predecesor;
}


int main(int argc, char* argv[])
{
	string s;
	ifstream infile;
	string asterisco = "*";

	//Variables del problema
	int dimension; // calculado
	char* terrenos = new char[19];
	int* numeros = new int[19];
	char* puertos = new char[9];
	bool* construccionesOponentes = new bool[54];
	int* construcciones = new int[54];

	bool** aristasOcupadas = new bool*[54];
	bool** caminos = new bool*[54]; 			// Los caminos son míos

	for (int i = 0; i < 54; i++) {
		aristasOcupadas[i] = new bool[54];
		caminos[i] = new bool[54];
		for (int j = 0; j < 54; j++){
			aristasOcupadas[i][j] = false;
			caminos[i][j] = false;
		}
	};

	Reserva reserva;


	infile.open("codificacion_turrita.txt");

	int size;
	int size2;


	//Parsear Matriz
	string* v;
	string* v2;
	string arista;
	int i;
	int j;
	int fila, columna;

	s = "basura";
	while (s != asterisco){
		getline(infile, s);
		split(s, v, ' ', size);
		if (v[0] == "terrenos:") {
			if (size  != 20) {
				cout << "Los cantidad de terrenos no es correcta, debe haber 19 y hay: " << size << endl;
				return 0;
			};
			// cout << "terrenos: " << endl;
			for (i = 0; i < 19; i++) {
				terrenos[i] = v[i+1][0];
				// cout << terrenos[i] << " ";
			};
			// cout << endl;
		};
		if (v[0] == "numeros:") {
			if (size  != 20) {
				cout << "Los cantidad de numeros no es correcta, debe haber 19 y hay: " << size << endl;
				return 0;
			};
			// cout << "numeros: " << endl;
			for (i = 0; i < 19; i++) {
				// cout << v[i+1];
				if (v[i+1] == "-1") {
					numeros[i] = -1;
				} else {
					numeros[i] = stoi(v[i+1]);
				}
				// cout << numeros[i] << " ";
			};
			// cout << endl;
		};
		if (v[0] == "puertos:") {
			if (size  != 10) {
				cout << "Los cantidad de puertos no es correcta, debe haber 9 y hay: " << size << endl;
				return 0;
			};
			// cout << "puertos: " << endl;
			for (i = 0; i < 9; i++) {
				puertos[i] = v[i+1][0];
				// cout << puertos[i] << " ";
			};
			// cout << endl;
		};
		if (v[0] == "construccionesOponentes:") {
			if (size  != 55) {
				cout << "Los cantidad de construcciones oponentes no es correcta, debe haber 54 y hay: " << size << endl;
				return 0;
			};
			// cout << "construccionesOponentes: " << endl;
			for (i = 0; i < 54; i++) {
				construccionesOponentes[i] = (v[i+1] == "1");
				// cout << construccionesOponentes[i] << " ";
			};
			// cout << endl;
		};
		if (v[0] == "aristasOcupadas:") {
			// cout << "aristasOcupadas: " << endl;
			// cout << "aristasOcupadas:" << endl;
			for (i = 1; i < size; i++) {
				arista = v[i];			//sacarle los parentesis
				split(arista, v2, ',', size2);
				fila = stoi(v2[0]);
				columna = stoi(v2[1]);
				aristasOcupadas[fila][columna] = true;
				aristasOcupadas[columna][fila] = true;
				// cout << fila << "," << columna << "   ";
				//agregar a la matriz o a la estructura magica de dijkstra
			};
			// cout << endl;
			for (i = 0; i<54; i++) {
				for (j = 0; j<i; j++) {
					// cout << aristasOcupadas[i][j] << " ";
				};
				// cout << endl;
			};
		};
		if (v[0] == "construcciones:") {
			if (size  != 55) {
				cout << "Los cantidad de construcciones no es correcta, debe haber 54 y hay: " << size << endl;
				return 0;
			};
			// cout << "construcciones: " << endl;
			for (i = 0; i < 54; i++) {
				construcciones[i] = (v[i+1] == "1");
				// cout << construcciones[i] << " ";
			};
			// cout << endl;
		};
		if (v[0] == "caminos:") {
			// cout << "caminos: " << endl;
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
			// cout << endl;
			for (i = 0; i<54; i++) {
				for (j = 0; j<i; j++) {
					// cout << caminos[i][j] << " ";
				};
				// cout << endl;
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

	int nodo_inicial = 5;
	int* path;
	int min_distnace;
	int min_distnace_node;

	minDistance(aristasOcupadas, caminos, nodo_inicial, min_distnace, min_distnace_node, path);

	cout << "La distancia minima desde el nodo inicial (" << nodo_inicial << ") a una pos mía es: " << min_distnace << endl;
	cout << "esa posición mía es: " << min_distnace_node << endl; 
	cout << "el path es: " << endl;
	for (i = 0; i < (min_distnace + 1); i++){
		cout << path[i] << " ";
	}
	cout << endl;

	return 0;
}













//chequear fitness


int calcular_fitness(int* simulacion_dados, int* jugadas_partida, estado_juego (tablero, reserva cartas, etc))
	int fitness
	bool termino = false;
	Reserva necesito;
	int numero_tirada = 0;
	while (!termino) {
		for (int i = 0; i < dimension; i++) {
			int proximo_punto = partida[i];
			if (proximo_punto == -1) {
				necesito = ...; //cosas para una carta desarrollo
			} else {
				if (!construccion_mia[proximo_punto]) {
					necesito = ...;
					minDistance(cosas, proximo_punto, min_distnace, path)
					if (tengo que hacer caminos) {
						necesito2 = ...; //cosas para hacer un camino
						necesito2 = necesito2 * min_distnace;
						necesito += necesito2;
					}
				} else {
				//si es ciudad
					necesito = ...; //cosas para una ciudad
				}
			}
			
			tengo_suficiente = tengoSuficiente(reserva, necesito);
			while (!tengo_suficiente) {
				// tiro dados 
				obtener_recursos(estado_juego, simulacion_dados[numero_tirada], reservaJugador);
				tengo_suficiente = tengoSuficiente(reserva, necesito);
			}
			construir(estado_juego, {poblado, ciudad, carta_desarrollo}, reservaJugador, jugada)
		}
	}
	return numero_tirada;



















