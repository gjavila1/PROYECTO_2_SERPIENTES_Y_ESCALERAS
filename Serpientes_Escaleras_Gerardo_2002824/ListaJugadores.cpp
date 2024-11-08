#include "ListaJugadores.h"
#include <iostream>
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define BLUE    "\033[34m"
#define BLINK "\x1b[5m"


using namespace std;

// Constructor de NodoJugador
NodoJugador::NodoJugador(int _jugadorID, string& _nombre)
    : jugadorID(_jugadorID), nombre(_nombre), next(nullptr) {}

//Constructor de ListaJugadores
ListaJugadores::ListaJugadores() : header(nullptr) {}

//Destructor para limpiar la lista
ListaJugadores::~ListaJugadores() {
    limpiarLista();
}

//Metodo para agregar un jugador al juego
void ListaJugadores::agregarJugador(int jugadorID,string& nombre) {
    NodoJugador* nuevo = new NodoJugador(jugadorID, nombre);

    if (!header) {
        header = nuevo; //Si la lista esta vacia, el nuevo nodo es el primero
    }
    else {
        NodoJugador* temp = header;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = nuevo;
    }
}

//Metodo para mostrar todos los jugadores
void ListaJugadores::mostrarJugadores() {
    if (!header) {
        cout << RED << BLINK << "\n-------------------------------" << RESET << endl;
        cout << RED << BLINK << "No hay jugadores en la lista." << RESET << endl;
        cout << RED << BLINK << "-------------------------------" << RESET << endl;
        return;
    }
    NodoJugador* temp = header;
    cout << BOLD << BLUE << "\n========= Lista de Jugadores =========" << RESET<< endl;
    while (temp) {
        cout << YELLOW << "ID: " << RESET << temp->jugadorID << YELLOW << " | Nombre: " << RESET << temp->nombre << YELLOW << " | Posicion: " << RESET << temp->posicion << endl;
        temp = temp->next;
    }
}

//Metodo para liberar la memoria de toda la lista
void ListaJugadores::limpiarLista() {
    NodoJugador* actual = header;
    while (actual != nullptr) {
        NodoJugador* siguiente = actual->next;
        delete actual;
        actual = siguiente;
    }
    header = nullptr;
}


