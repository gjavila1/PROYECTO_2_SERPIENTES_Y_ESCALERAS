#pragma once
#include <string>
using namespace std;

struct NodoJugador {
	int jugadorID;        // ID del jugador (numero unico)
	string nombre;        // Nombre del jugador
	int posicion = 0;     // Posicion actual en el tablero
	NodoJugador* next;    // Puntero al siguiente jugador

	// Constructor
	NodoJugador(int _jugadorID, string& _nombre);
};

class ListaJugadores {
public:
	NodoJugador* header; // Puntero a la cabeza de la lista de jugadores

public:
	// Constructor y destructor
	ListaJugadores();
	~ListaJugadores();

	// Métodos
	void agregarJugador(int jugadorID, string& nombre);
	void mostrarJugadores();
	void eliminarJugador(int jugadorID);
	void moverJugador(int jugadorID, int nuevaPosicion);
	//NodoJugador* obtenerJugador(int jugadorID); // Opcional, para obtener un jugador por su ID
	void limpiarLista();
};
