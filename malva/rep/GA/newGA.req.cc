#ifndef INC_REQ_newGA
#define INC_REQ_newGA
#include "newGA.hh"
#include <math.h>
#include <string>
#include <unistd.h>
#include "variablesGlobales.cpp"
using namespace std;
#define INFINIT 10000
#define CANTIDADSIMULACIONES 10
#define MAXLARGOSIMULACION 1000


// Separar por un caracter para el parser
void split(string &txt, string* &palabras, char ch, int &tam)
{
	// recorrer y encontrar cuantos espacios hay
	//crear array de tamaño n+1
	//volver a recorrer y agregar al array
	string str = txt;
	int largo = str.length();
	if (largo > 0) {
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
	} else {
		tam = 0;
	}
}

// Algoritmo de djkstra
void dijkstra(int** cost, int startnode, int* &distance, int* &pred)
{
 
	int visited[54], count, mindistance;
	int nextnode, i, j;
	nextnode = -1;
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
		if (nextnode == -1) {
			for (i = 0; i < 54; i++) {
				pred[i] == -1;
			};
			return;
		}
		for (i = 0; i < 54; i++) {
			if (!visited[i]) {
				if (mindistance + cost[nextnode][i] < distance[i]) {
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				};
			};
		};
		count++;
	}
}


void minDistance(const newGA::Problem& pbm, bool** caminos, int construccion0, int construccion1, int startnode, int &min_distance, int &min_distance_node, int* &path) {
	
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
			if (pbm.aristasOcupadas(i,j)){
				costo[i][j] = INFINIT;
			}
		};
	};
	for (i = 0; i < 54; i++){			// saco las aristas adyacentes a los vertices con construcciones construccionesOponentes
		if (pbm.construccionesOponentes(i)) {
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

	if (predecesor[0] == -1) {
		min_distance = INFINIT;
		return;
	}
	
	min_distance = INFINIT;
	for (i = 0; i < 54; i++) {
		for (j = 0; j < 54; j++) {
			if (caminos[i][j]){
				if (distancia[i] < min_distance) {
					min_distance = distancia[i];
					min_distance_node = i;
				};
				if (distancia[j] < min_distance) {
					min_distance = distancia[j];
					min_distance_node = j;
				};
			} else {
				if ((distancia[i] < min_distance) && (i == construccion0 || i == construccion1)) {
					min_distance = distancia[i];
					min_distance_node = i;
				};
			};
		};
	};

	// TODO: min distance a las construcciones

	int nodo_aux = min_distance_node;
	path = new int[min_distance + 1];
	for (i = 0; i < min_distance; i++) {
		path[i] = nodo_aux;
		nodo_aux = predecesor[nodo_aux];
	};
	path[min_distance] = startnode;

	for (i = 0; i < 54; i++) {
		delete [] costo[i];
	};
	delete [] costo;
	delete [] distancia;
	delete [] predecesor;
}


skeleton newGA
{

	// Problem ---------------------------------------------------------------

	Problem::Problem ():_dimension(0)
	{}

	ostream& operator<< (ostream& os, const Problem& pbm)
	{
		os << endl << endl << "Number of Variables " << pbm._dimension
		   << endl;
		return os;
	}

	istream& operator>> (istream& is, Problem& pbm)
	{
		char buffer[MAX_BUFFER];
		int i;

		string s;
		string asterisco = "*";

		// Inicializar variables del problema
		pbm._terrenos = new char[19];
		pbm._numeros = new int[19];
		pbm._puertos = new char[9];
		pbm._construccionesOponentes = new bool[54];
		pbm._construcciones = new int[54];

		pbm._aristasOcupadas = new bool*[54]; 	// estructura magica de dijkstra // ingresarlas al array
		pbm._caminos = new bool*[54]; 			// estructura magica de dijkstra


		pbm._verticesValidos = new bool[54];


		for (int i = 0; i < 54; i++) {
			pbm._aristasOcupadas[i] = new bool[54];
			pbm._caminos[i] = new bool[54];
			pbm._verticesValidos[i] = true;
			for (int j = 0; j < 54; j++){
				pbm._aristasOcupadas[i][j] = false;
				pbm._caminos[i][j] = false;
			}
		};

		int size;
		int size2;
		Global g;


		//Parsear Matriz
		string* v;
		string* v2;
		string arista;
		int j;
		int fila, columna;

		s = "basura";
		while (s != asterisco){
			is.getline(buffer,MAX_BUFFER,'\n');
			s = buffer;
			split(s, v, ' ', size);
			if (v[0] == "terrenos:") {
				if ((size-1) != 19) {
					cout << "Los cantidad de terrenos no es correcta, debe haber 19 y hay: " << (size-1) << endl;
				};
				for (i = 0; i < 19; i++) {
					pbm._terrenos[i] = v[i+1][0];
				};
			};
			if (v[0] == "numeros:") {
				if ((size-1) != 19) {
					cout << "Los cantidad de numeros no es correcta, debe haber 19 y hay: " << (size-1) << endl;
				};
				for (i = 0; i < 19; i++) {
					// cout << v[i+1];
					if (v[i+1] == "-1") {
						pbm._numeros[i] = -1;
					} else {
						pbm._numeros[i] = stoi(v[i+1]);
					};
				};
			};
			if (v[0] == "puertos:") {
				if ((size-1)  != 9) {
					cout << "Los cantidad de puertos no es correcta, debe haber 9 y hay: " << (size-1) << endl;
				};
				for (i = 0; i < 9; i++) {
					pbm._puertos[i] = v[i+1][0];
				};
			};
			if (v[0] == "construccionesOponentes:") {
				if ((size-1) != 54) {
					cout << "Los cantidad de construcciones oponentes no es correcta, debe haber 54 y hay: " << (size-1) << endl;
				};
				for (i = 0; i < 54; i++) {
					pbm._construccionesOponentes[i] = stoi(v[i+1]);
					if(pbm._construccionesOponentes[i] > 0) {
						pbm._verticesValidos[i] = false;
						for(int j=0; j<3; j++) {
							int posAdyacente = g.vertices_adyacentes[i][j];
							if(posAdyacente != -1) {
								pbm._verticesValidos[posAdyacente] = false;
							}
						}
					}
				};
			};
			if (v[0] == "aristasOcupadas:") {
				for (i = 1; i < size; i++) {
					arista = v[i];			//sacarle los parentesis
					split(arista, v2, ',', size2);
					fila = stoi(v2[0]);
					columna = stoi(v2[1]);
					pbm._aristasOcupadas[fila][columna] = true;
					pbm._aristasOcupadas[columna][fila] = true;
					delete [] v2;
				};
			};
			if (v[0] == "construcciones:") {
				if ((size-1)  != 54) {
					cout << "Los cantidad de construcciones no es correcta, debe haber 54 y hay: " << (size-1) << endl;
				};
				for (i = 0; i < 54; i++) {
					pbm._construcciones[i] = stoi(v[i+1]);
					if(pbm._construcciones[i] > 0) {
						for(int j=0; j<3; j++) {
							int posAdyacente = g.vertices_adyacentes[i][j];
							if(posAdyacente != -1) {
								pbm._verticesValidos[posAdyacente] = false;
							}
						}
					}
				}
			}
			if (v[0] == "caminos:") {
				for (i = 1; i < size; i++) {
					arista = v[i];			//sacarle los parentesis
					split(arista, v2, ',', size2);
					fila = stoi(v2[0]);
					columna = stoi(v2[1]);
					pbm._caminos[fila][columna] = true;
					pbm._caminos[columna][fila] = true;
					//agregar a la matriz o a la estructura magica de dijkstra
					delete [] v2;
				};

			};
			if (v[0] == "reserva:") {
				for (i = 1; i < size; i++) {
					string coso = v[i];			//sacarle los parentesis
					split(coso, v2, ':', size2);
					if (v2[0] == "T") {
						pbm._reserva.trigo = stoi(v2[1]);
					};
					if (v2[0] == "A") {
						pbm._reserva.arcilla = stoi(v2[1]);
					};
					if (v2[0] == "M") {
						pbm._reserva.madera = stoi(v2[1]);
					};
					if (v2[0] == "O") {
						pbm._reserva.oveja = stoi(v2[1]);
					};
					if (v2[0] == "P") {
						pbm._reserva.piedra = stoi(v2[1]);
					};
					if (v2[0] == "puntos") {
						pbm._reserva.puntosDesarrollo = stoi(v2[1]);
					};
					delete [] v2;
				};
			};
			delete [] v;
		};

		int puntosObtenidos = pbm.reserva().puntosDesarrollo;
		for(int i=0; i<54; i++) {
			puntosObtenidos += pbm.construcciones(i);
		};
		pbm._dimension = 10 - puntosObtenidos;

		pbm._dados = new int*[CANTIDADSIMULACIONES];
		for (int i = 0; i < CANTIDADSIMULACIONES; i++) {
			pbm._dados[i] = new int[MAXLARGOSIMULACION];
			for (int j = 0; j < MAXLARGOSIMULACION; j++) {
				pbm._dados[i][j] = rand_int(1,6) + rand_int(1,6);
			};
		};

		int dist; int nodo;
		int* path;

		if (pbm._dimension <= 8){
			for(int i = 0; i < 54; i++ ){
				minDistance(pbm, pbm._caminos, -1, -1, i, dist, nodo, path);
				if(dist == INFINIT) {
					pbm._verticesValidos[i] = false;
				};
			};
		};


		return is;
	}

	bool Problem::operator== (const Problem& pbm) const
	{
		if (_dimension!=pbm.dimension()) return false;
		return true;
	}

	bool Problem::operator!= (const Problem& pbm) const
	{
		return !(*this == pbm);
	}

	Direction Problem::direction() const
	{
		return maximize;
		//return minimize;
	}

	int Problem::dimension() const
	{
		return _dimension;
	}

	char Problem::terrenos(int i) const {
		return _terrenos[i];
	}

	int Problem::numeros(int i) const {
		return _numeros[i];
	}

	char Problem::puertos(int i) const{
		return _puertos[i];
	}

	bool Problem::construccionesOponentes(int i) const{
		return _construccionesOponentes[i];
	}

	bool Problem::aristasOcupadas(int i, int j) const{
		return _aristasOcupadas[i][j];
	}

	int Problem::construcciones(int i) const{
		return _construcciones[i];
	}

	bool Problem::caminos(int i, int j) const{
		return _caminos[i][j];
	}

	Reserva Problem::reserva() const{
		return _reserva;
	}

	int Problem::dados(int i, int j) const{
		return _dados[i][j];
	}

	bool Problem::verticesValidos(int i) const{
		return _verticesValidos[i];
	}


	Problem::~Problem()
	{
		if(this->_terrenos != NULL) {
			delete [] this->_terrenos;
		}
		if(this->_numeros != NULL) {
			delete [] this->_numeros;
		}
		if(this->_puertos != NULL) {
			delete [] this->_puertos;
		}
		if(this->_construccionesOponentes != NULL) {
			delete [] this->_construccionesOponentes;
		}
		if(this->_construcciones != NULL) {
			delete [] this->_construcciones;
		}
		if(this->_aristasOcupadas != NULL) {
			for (int i = 0; i<54; i++) {
				delete [] this->_aristasOcupadas[i];
			}
			delete [] this->_aristasOcupadas;
		}
		if(this->_caminos != NULL) {
			for (int i = 0; i<54; i++) {
				delete [] this->_caminos[i];
			}
			delete [] this->_caminos;
		}
		if(this->_verticesValidos != NULL) {
			delete [] this->_verticesValidos;
		}
		if(this->_dados != NULL) {
			for (int i = 0; i<CANTIDADSIMULACIONES; i++) {
				delete [] this->_dados[i];
			}
			delete [] this->_dados;
		}
	}

	// Solution --------------------------------------------------------------

	Solution::Solution (const Problem& pbm):_pbm(pbm),_var(pbm.dimension())
	{}

	const Problem& Solution::pbm() const
	{
		return _pbm;
	}

	Solution::Solution(const Solution& sol):_pbm(sol.pbm())
	{
		*this=sol;
	}

	istream& operator>> (istream& is, Solution& sol)
	{
		for (int i=0;i<sol.pbm().dimension();i++)
			is >> sol._var[i];
		return is;
	}

	ostream& operator<< (ostream& os, const Solution& sol)
	{
		for (int i=0;i<sol.pbm().dimension();i++)
			os << " " << sol._var[i];
		return os;
	}

	NetStream& operator << (NetStream& ns, const Solution& sol)
	{
		for (int i=0;i<sol._var.size();i++)
			ns << sol._var[i];
		return ns;
	}

	NetStream& operator >> (NetStream& ns, Solution& sol)
	{
		for (int i=0;i<sol._var.size();i++)
			ns >> sol._var[i];
		return ns;
	}

 	Solution& Solution::operator= (const Solution &sol)
	{
		_var=sol._var;
		return *this;
	}

	bool Solution::operator== (const Solution& sol) const
	{
		if (sol.pbm() != _pbm) return false;
		for(int i = 0; i < _var.size(); i++)
			if(_var[i] != sol._var[i]) return false;
		return true;
	}

	bool Solution::operator!= (const Solution& sol) const
	{
		return !(*this == sol);
	}

	void Solution::corregirSolucion() {
		bool rota = false;
		bool* posicionesRotas = new bool[_pbm.dimension()];
		for (int i = 0; i < _pbm.dimension(); i++) {
			posicionesRotas[i] = false;
		}

		int cantidadCiudades = 0;
		////mide cantidad de ciudades y de construcciones iniciales
		int* cantidadConstrucciones = new int[54];
		for (int i = 0; i < 54; i++) {
			cantidadConstrucciones[i] = _pbm.construcciones(i);
			if (cantidadConstrucciones[i] == 2) {
				cantidadCiudades++;
			};
		}

		//instanciar en true todas las posiciones ocupadas
		int* construcciones = new int[54];
		for (int i=0; i<54; i++) {
			construcciones[i] = _pbm.construccionesOponentes(i);
			if (_pbm.construcciones(i)!=0) {
				construcciones[i]=true;
			}
		}

		Global g;
		int cantidadDesarrollo = _pbm.reserva().puntosDesarrollo;
		

		for(int i=0;i<_var.size(); i++) {
			if(_var[i]==-1){
				cantidadDesarrollo++;
				if(cantidadDesarrollo>5) {
					rota = true;
					posicionesRotas[i] = true;
				}
			} else {
				construcciones[_var[i]] = true;
				cantidadConstrucciones[_var[i]]++;
				if (cantidadConstrucciones[_var[i]] == 2) {
					cantidadCiudades++;
					if(cantidadCiudades > 4) {
						rota = true;
						posicionesRotas[i] = true;
					}
				}
				if(cantidadConstrucciones[_var[i]] > 2) {
					rota = true;
					posicionesRotas[i] = true;
				}
				for(int j=0; j<3; j++) {
					int posAdyacente = g.vertices_adyacentes[_var[i]][j];
					if(posAdyacente != -1 && construcciones[posAdyacente]) {
						rota = true;
						posicionesRotas[i] = true;
					}
				}
			}
		}
		delete [] cantidadConstrucciones;
		delete [] construcciones;

		if(rota) {
			// this->initialize();
			for(int i=0; i<_pbm.dimension(); i++) {
				if(posicionesRotas[i]) {
					_var[i]=rand_int(-1,53);
					while(!_pbm.verticesValidos(_var[i])) {
						_var[i]=rand_int(-1,53);
					}
				}
			}
			corregirSolucion();
		}
		delete [] posicionesRotas;
	}

	void Solution::initialize()
	{
		int dimension = _pbm.dimension();
		int start = 0;

		if (dimension > 8) {
			start = dimension - 8;
			int calidad;
			int valor;
			int numero_terreno;
			int mejor_vertice = -1;
			int mejor_calidad = INFINIT;
			_var[0] = -1;
			_var[1] = -1;

			for (int k = 0; k < (dimension - 8); k++) {		// Uno o dos poblados
				mejor_vertice = -1;
				mejor_calidad = INFINIT;
				for (int i = 0; i < 54; i++) {				// Para cada vértice
					if (_var[0] != i) {
						calidad = 0;
						for (int j = 0; j < 3; j++) {
							numero_terreno = Global::vertices_terrenos[i][j];
							if ((numero_terreno >= 0) && (_pbm.construccionesOponentes(numero_terreno) == 0) && (_pbm.construcciones(numero_terreno) == 0)) {
								valor = _pbm.numeros(numero_terreno);
								if (valor == 7) {
									calidad += 7;
								} else {
									calidad += abs((valor - 7));		// se le puede multiplicar por un valor hipotetico del tipo de terreno que hay ahí
								};
							} else {
								calidad += 7;
							};
							calidad += (rand_int(1,7));			//<<-----   TODO: VER PORQUE SE ROMPE SI DESCOMENTO ESTA LINEA
						};
						if (calidad < mejor_calidad) {
							mejor_calidad = calidad;
							mejor_vertice = i;
						};
					};
				};
				_var[k] = mejor_vertice;
			};
		};
		// Inicializo random lo que queda
		for (int i = start; i < dimension; i++) {
			_var[i]=rand_int(-1,53);
			while (!_pbm.verticesValidos(_var[i])) {
				_var[i]=rand_int(-1,53);
			};
		};
		corregirSolucion();		
	}

	//void Solution::initializeGreedy()

	void Solution::mapearRecursos(Reserva* &mapeo) {
		//copiar caminos
		bool** caminos = new bool*[54]; 
		for (int i = 0; i < 54; i++) {
			caminos[i] = new bool[54];
			for (int j = 0; j < 54; j++){
				caminos[i][j] = _pbm.caminos(i,j);
			};
		};
		//para cada gen de la solución
		int start = 0;
		int caminos_gratis = 0;
		int construccion0 = -1;
		int construccion1 = -1;
		if (_var.size() > 8) {
			start = _var.size() - 8;
			caminos_gratis = start;
			construccion0 = _var[0];
			if (_var.size() == 10) {
				construccion1 = _var[1];
			};
		};
		for(int i = start; i < _var.size(); i++) {
			if(_var[i] == -1) {
				//es desarrollo
				mapeo[i].arcilla = 0;
				mapeo[i].trigo = 5;
				mapeo[i].oveja = 5;
				mapeo[i].piedra = 5;
				mapeo[i].madera = 0;
				mapeo[i].puntosDesarrollo = 0;
			} else {
				if(_pbm.construcciones(_var[i])==1) {
					//es ciudad
					mapeo[i].arcilla = 0;
					mapeo[i].trigo = 2;
					mapeo[i].oveja = 0;
					mapeo[i].piedra = 3;
					mapeo[i].madera = 0;
					mapeo[i].puntosDesarrollo = 0;
				} else {
					//es poblado.
					mapeo[i].arcilla = 1;
					mapeo[i].trigo = 1;
					mapeo[i].oveja = 1;
					mapeo[i].piedra = 0;
					mapeo[i].madera = 1;
					mapeo[i].puntosDesarrollo = 0;
					//contar caminos!
					int min_distance;
					int min_distance_node;
					int* path;

					minDistance(_pbm, caminos, construccion0, construccion1, _var[i], min_distance, min_distance_node, path);
					if(min_distance > 0){
						for(int j = 1; j <= min_distance; j++){
							caminos[path[j]][path[j-1]] = true;
							caminos[path[j-1]][path[j]] = true;
						}
						if (caminos_gratis > 0) {
							min_distance--;
							caminos_gratis--;
						};
						mapeo[i].arcilla += min_distance;
						mapeo[i].madera += min_distance;

					};
					delete [] path;
				}
			}
		}
		for (int i = 0; i < 54; i++) {
			delete [] caminos[i];
		}
		delete [] caminos;
	}

	void Solution::cobrarRecursos(int dadoActual, Reserva &recursos, int* construcciones) {
		if(dadoActual != 7) {
			for (int i = 0; i < 19; i++) {
				if(_pbm.numeros(i) == dadoActual) {
					char recursoQueProduce = _pbm.terrenos(i);
					for(int j=0; j < 6; j++) {
						int vertice = Global::terrenos_vertices[i][j];
						int cantRecursosASumar = construcciones[vertice];
						switch (recursoQueProduce) {
					        case 'A': 
						        recursos.arcilla += cantRecursosASumar;
						        break;
						    case 'T': 
						        recursos.trigo += cantRecursosASumar;
						        break;
					        case 'O': 
						        recursos.oveja += cantRecursosASumar;
						        break;
					        case 'P': 
						        recursos.piedra += cantRecursosASumar;
						        break;
					        case 'M': 
						        recursos.madera += cantRecursosASumar;
						        break;
						}
					}
				}
			}
		};
	}

	bool Solution::alcanzanRecursos(Reserva &tengo, Reserva quiero, DivisoresTrade divisores) {
		Reserva r = tengo;
		int recursosQueNecesitoTradear = 0;

		//ver qué tengo y qué necesito tradear.
		bool alcanzaArcilla = tengo.arcilla >= quiero.arcilla;
		if(alcanzaArcilla)
		{
			r.arcilla -= quiero.arcilla; //resto y todo bien
		}
		else
		{
			recursosQueNecesitoTradear += quiero.arcilla - tengo.arcilla;
			r.arcilla = 0;
		}

		bool alcanzaTrigo = tengo.trigo >= quiero.trigo;
		if(alcanzaTrigo)
		{
			r.trigo -= quiero.trigo; //resto y todo bien
		}
		else
		{
			recursosQueNecesitoTradear += quiero.trigo - tengo.trigo;
			r.trigo = 0;
		}

		bool alcanzaOveja = tengo.oveja >= quiero.oveja;
		if(alcanzaOveja)
		{
			r.oveja -= quiero.oveja; //resto y todo bien
		}
		else
		{
			recursosQueNecesitoTradear += quiero.oveja - tengo.oveja;
			r.oveja = 0;
		}

		bool alcanzaPiedra = tengo.piedra >= quiero.piedra;
		if(alcanzaPiedra)
		{
			r.piedra -= quiero.piedra; //resto y todo bien
		}
		else
		{
			recursosQueNecesitoTradear += quiero.piedra - tengo.piedra;
			r.piedra = 0;
		}

		bool (alcanzaMadera) = tengo.madera >= quiero.madera;
		if(alcanzaMadera)
		{
			r.madera -= quiero.madera; //resto y todo bien
		}
		else
		{
			recursosQueNecesitoTradear += quiero.madera - tengo.madera;
			r.madera = 0;
		}

		//tradear:
		recursosQueNecesitoTradear -= r.arcilla / divisores.arcilla;
		r.arcilla = r.arcilla % divisores.arcilla;
		recursosQueNecesitoTradear -= r.trigo / divisores.trigo;
		r.trigo = r.trigo % divisores.trigo;
		recursosQueNecesitoTradear -= r.oveja / divisores.oveja;
		r.oveja = r.oveja % divisores.oveja;
		recursosQueNecesitoTradear -= r.piedra / divisores.piedra;
		r.piedra = r.piedra % divisores.piedra;
		recursosQueNecesitoTradear -= r.madera / divisores.madera;
		r.madera = r.madera % divisores.madera;

		if (recursosQueNecesitoTradear <= 0) {
			tengo = r;
			return true;
		} else {
			return false;
		}
	}

	int Solution::correrSimulacion(int idxSimulacion, Reserva* mapeo) {
		int turnos = 0;
		
		int* construcciones = new int[54];
		for (int i = 0; i < 54; i++) {
			construcciones[i] = _pbm.construcciones(i);
		};
		// Las primeras dos construcciones en caso que el problema sea > 8
		if (_pbm.dimension() > 8) {
			for (int i = 0; i < (_pbm.dimension() - 8); i++) {
				construcciones[_var[i]] = 1;
			}
		};

		Reserva recursos = _pbm.reserva();

		//divisores de trade. inician en 4.
		DivisoresTrade divisores;
		divisores.arcilla = 4;
		divisores.trigo = 4;
		divisores.oveja = 4;
		divisores.piedra = 4;
		divisores.madera = 4;

		Global g;
		//inicializar divisores con datos de problema.
		for (int i=0; i< 54; i++) {
			if(construcciones[i]!=0) {
				if(g.vertices_puertos[i] != -1) {
					switch (_pbm.puertos(g.vertices_puertos[i])) {
				        case 'A': 
					        divisores.arcilla = 2;
					        break;
				        case 'T': 
					        divisores.trigo = 2;
					        break;
				        case 'O': 
					        divisores.oveja = 2;
					        break;
				        case 'P': 
					        divisores.piedra = 2;
					        break;
				        case 'M': 
					        divisores.madera = 2;
					        break;
				        case '3': 
				        	if (divisores.arcilla == 4) {
				        		divisores.arcilla = 3;
				        	}
				        	if (divisores.trigo == 4) {
				        		divisores.trigo = 3;
				        	}
				        	if (divisores.oveja == 4) {
				        		divisores.oveja = 3;
				        	}
				        	if (divisores.piedra == 4) {
				        		divisores.piedra = 3;
				        	}
				        	if (divisores.madera == 4) {
				        		divisores.madera = 3;
				        	}
					        break;
					}
				}
			}
		}

		//para cada gen
		int start = 0;
		if (_pbm.dimension() > 8) {
			start = _pbm.dimension() - 8;
		};

		for(int i = start; i < _pbm.dimension(); i++) {
			while (!alcanzanRecursos(recursos, mapeo[i], divisores)) {
				int dadoActual = _pbm.dados(idxSimulacion, (turnos % MAXLARGOSIMULACION));
				turnos++;
				if (turnos > 1000) {
					return INFINIT;
				};
				cobrarRecursos(dadoActual, recursos, construcciones);
			}
			//si alcanzaron los recursos, me lo resta alcanzanRecursos (pasa por referencia).
			if(_var[i] != -1) {
				construcciones[_var[i]]++;
				//actualizar divisores.
				if(g.vertices_puertos[_var[i]] != -1) {
					switch (_pbm.puertos(g.vertices_puertos[i])) {
				        case 'A': 
					        divisores.arcilla = 2;
					        break;
				        case 'T': 
					        divisores.trigo = 2;
					        break;
				        case 'O': 
					        divisores.oveja = 2;
					        break;
				        case 'P': 
					        divisores.piedra = 2;
					        break;
				        case 'M': 
					        divisores.madera = 2;
					        break;
				        case '3': 
				        	if (divisores.arcilla == 4) {
				        		divisores.arcilla = 3;
				        	}
				        	if (divisores.trigo == 4) {
				        		divisores.trigo = 3;
				        	}
				        	if (divisores.oveja == 4) {
				        		divisores.oveja = 3;
				        	}
				        	if (divisores.piedra == 4) {
				        		divisores.piedra = 3;
				        	}
				        	if (divisores.madera == 4) {
				        		divisores.madera = 3;
				        	}
					        break;
					}
				}
			}
		}
		delete [] construcciones;
		return turnos;
	}

	double Solution::fitness ()
	{
        double fitness = 0.0;


		Reserva* mapeoRecursos = new Reserva[_pbm.dimension()];
        mapearRecursos(mapeoRecursos);

        for(int i = 0; i < CANTIDADSIMULACIONES; i++) {
        	fitness += correrSimulacion(i, mapeoRecursos);
        }

        fitness /= CANTIDADSIMULACIONES;
        fitness *= -1;
        delete [] mapeoRecursos;
		return fitness;
	}

	char *Solution::to_String() const
	{
		return (char *)_var.get_first();
	}

	void Solution::to_Solution(char *_string_)
	{
		int *ptr=(int *)_string_;
		for (int i=0;i<_pbm.dimension();i++)
		{
			_var[i]=*ptr;
			ptr++;
		}
	}

	unsigned int Solution::size() const
	{
		return (_pbm.dimension() * sizeof(int));
	}


	int& Solution::var(const int index)
	{
		return _var[index];
	}


	Rarray<int>& Solution::array_var()
	{
		return _var;
	}

	Solution::~Solution()
	{}

	// UserStatistics -------------------------------------------------------

	UserStatistics::UserStatistics ()
	{}

	ostream& operator<< (ostream& os, const UserStatistics& userstat)
	{
		os << "\n---------------------------------------------------------------" << endl;
		os << "                   STATISTICS OF TRIALS                   	 " << endl;
		os << "------------------------------------------------------------------" << endl;

		for (int i=0;i< userstat.result_trials.size();i++)
		{
			os << endl
			   << userstat.result_trials[i].trial
			   << "\t" << userstat.result_trials[i].best_cost_trial
			   << "\t\t" << userstat.result_trials[i].worst_cost_trial
			   << "\t\t\t" << userstat.result_trials[i].nb_evaluation_best_found_trial
			   << "\t\t\t" << userstat.result_trials[i].nb_iteration_best_found_trial
			   << "\t\t\t" << userstat.result_trials[i].time_best_found_trial
			   << "\t\t" << userstat.result_trials[i].time_spent_trial;
		}
		os << endl << "------------------------------------------------------------------" << endl;
		return os;
	}

	UserStatistics& UserStatistics::operator= (const UserStatistics& userstats)
	{
		result_trials=userstats.result_trials;
		return (*this);
	}

	void UserStatistics::update(const Solver& solver)
	{
		if( (solver.pid()!=0) || (solver.end_trial()!=true)
		  || ((solver.current_iteration()!=solver.setup().nb_evolution_steps())
		       && !terminateQ(solver.pbm(),solver,solver.setup())))
			return;

		struct user_stat *new_stat;

		if ((new_stat=(struct user_stat *)malloc(sizeof(struct user_stat)))==NULL)
			show_message(7);
		new_stat->trial         		 		 = solver.current_trial();
		new_stat->nb_evaluation_best_found_trial = solver.evaluations_best_found_in_trial();
		new_stat->nb_iteration_best_found_trial  = solver.iteration_best_found_in_trial();
		new_stat->worst_cost_trial     		 	 = solver.worst_cost_trial();
		new_stat->best_cost_trial     		 	 = solver.best_cost_trial();
		new_stat->time_best_found_trial		 	 = solver.time_best_found_trial();
		new_stat->time_spent_trial 		 		 = solver.time_spent_trial();

		result_trials.append(*new_stat);
	}

	void UserStatistics::clear()
	{
		result_trials.remove();
	}

	UserStatistics::~UserStatistics()
	{
		result_trials.remove();
	}

// Intra_operator  --------------------------------------------------------------

	Intra_Operator::Intra_Operator(const unsigned int _number_op):_number_operator(_number_op),probability(NULL)
	{}

	unsigned int Intra_Operator::number_operator() const
	{
		return _number_operator;
	}

	Intra_Operator *Intra_Operator::create(const unsigned int _number_op)
	{
		switch (_number_op)
		{
			case 0: return new Crossover;break;
			case 1: return new Mutation();break;
		}
	}

	ostream& operator<< (ostream& os, const Intra_Operator& intra)
	{
		switch (intra.number_operator())
		{
			case 0: os << (Crossover&)intra;break;
			case 1: os << (Mutation&)intra;break;
		}
		return os;
	}

	Intra_Operator::~Intra_Operator()
	{}

//  Crossover:Intra_operator -------------------------------------------------------------

	Crossover::Crossover():Intra_Operator(0)
	{
		probability = new float[1];
	}

	void Crossover::cross(Solution& sol1,Solution& sol2) const // dadas dos soluciones de la poblacion, las cruza
	{
		int i=0;
		Rarray<int> aux(sol1.pbm().dimension());
		aux=sol2.array_var();

		int start = 0;
		if (sol1.pbm().dimension() >= 9) {
			start = sol1.pbm().dimension() -8;
		};

		int limit=rand_int((sol1.pbm().dimension()/2)+1,sol1.pbm().dimension()-1);
		int limit2=rand_int(start,limit-1);

		for (i=0;i<limit2;i++)
			sol2.var(i)=sol1.var(i);
		for (i=0;i<limit2;i++)
			sol1.var(i)=aux[i];
		for (i=limit;i<sol1.pbm().dimension();i++)
			sol2.var(i)=sol1.var(i);
		for (i=limit;i<sol1.pbm().dimension();i++)
			sol1.var(i)=aux[i];
		sol1.corregirSolucion();
		sol2.corregirSolucion();
	}

	void Crossover::execute(Rarray<Solution*>& sols) const
	{
		for (int i=0;i+1<sols.size();i=i+2)
		 	if (rand01()<=probability[0]) cross(*sols[i],*sols[i+1]);
	}

	ostream& operator<< (ostream& os, const Crossover&  cross)
	{
		 os << "Crossover." << " Probability: "
                    << cross.probability[0]
		    << endl;
		 return os;
	}

	void Crossover::RefreshState(const StateCenter& _sc) const
	{
		_sc.set_contents_state_variable("_crossover_probability",(char *)probability,1,sizeof(float));
	}

	void Crossover::UpdateFromState(const StateCenter& _sc)
	{
		 unsigned long nbytes,length;
		 _sc.get_contents_state_variable("_crossover_probability",(char *)probability,nbytes,length);
	}

	void Crossover::setup(char line[MAX_BUFFER])
	{
		int op;
		sscanf(line," %d %f ",&op,&probability[0]);
		assert(probability[0]>=0);
	}

	Crossover::~Crossover()
	{
		delete [] probability;
	}

	//  Mutation: Sub_operator -------------------------------------------------------------

	Mutation::Mutation():Intra_Operator(1)
	{
		probability = new float[2];
	}

	void Mutation::mutate(Solution& sol) const
	{
		bool mute = false;
		for (int i=0;i<sol.pbm().dimension();i++)
		{
			if (rand01()<=probability[1])
			{
				sol.var(i)=rand_int(-1,53);
				while(!sol.pbm().verticesValidos(sol.var(i))) {
					sol.var(i)=rand_int(-1,53);
				}
				mute = true;
			}
		}
		if (mute) {
			sol.corregirSolucion();
		}
	}

	void Mutation::execute(Rarray<Solution*>& sols) const
	{
		for (int i=0;i<sols.size();i++)
			if(rand01() <= probability[0])	mutate(*sols[i]);
	}

	ostream& operator<< (ostream& os, const Mutation&  mutation)
	{
		os << "Mutation." << " Probability: " << mutation.probability[0]
		   << " Probability1: " << mutation.probability[1]
		   << endl;
		return os;
	}

	void Mutation::setup(char line[MAX_BUFFER])
	{
		int op;
		sscanf(line," %d %f %f ",&op,&probability[0],&probability[1]);
		assert(probability[0]>=0);
		assert(probability[1]>=0);
	}

	void Mutation::RefreshState(const StateCenter& _sc) const
	{
		_sc.set_contents_state_variable("_mutation_probability",(char *)probability,2,sizeof(probability));
	}

	void Mutation::UpdateFromState(const StateCenter& _sc)
	{
		unsigned long nbytes,length;
		_sc.get_contents_state_variable("_mutation_probability",(char *)probability,nbytes,length);
	}

	Mutation::~Mutation()
	{
		delete [] probability;
	}

// StopCondition_1 -------------------------------------------------------------------------------------

	StopCondition_1::StopCondition_1():StopCondition()
	{}

	bool StopCondition_1::EvaluateCondition(const Problem& pbm,const Solver& solver,const SetUpParams& setup)
	{
		return ((int)solver.best_cost_trial() > pbm.dimension()*53);
	}

	StopCondition_1::~StopCondition_1()
	{}

	//------------------------------------------------------------------------
	// Specific methods ------------------------------------------------------
	//------------------------------------------------------------------------

	bool terminateQ (const Problem& pbm, const Solver& solver,
			 const SetUpParams& setup)
	{
		StopCondition_1 stop;
		return stop.EvaluateCondition(pbm,solver,setup);
	}
}
#endif




