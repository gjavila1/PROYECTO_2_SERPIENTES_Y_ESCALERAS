#include "ColaHistorialGanadores.h"
#include <iostream>
#define BLINK "\x1b[5m"

using namespace std;

//Constructor
ColaHistorialGanadores::ColaHistorialGanadores() : frente(nullptr), final(nullptr) {}

//Destructor para liberar memoria
ColaHistorialGanadores::~ColaHistorialGanadores() {
    while (frente) {
        NodoGanador* temp = frente;
        frente = frente->siguiente;
        delete temp;
    }
}

//Metodo para agregar un ganador a la cola
void ColaHistorialGanadores::agregarGanador(const string& nombre, int id) {
    NodoGanador* nuevoGanador = new NodoGanador(nombre,id);
    if (!frente) {
        frente = final = nuevoGanador;
    }
    else {
        final->siguiente = nuevoGanador;
        final = nuevoGanador;
    }
}

//Metodo para mostrar los ganadores
void ColaHistorialGanadores::mostrarGanadores(){
    if (!frente) {
        cout << RED << BLINK << "\n-------------------------------" << RESET << endl;
        cout << RED << BLINK << "No hay ganadores registrados aun." << RESET << endl;
        cout << RED << BLINK << "-------------------------------" << RESET << endl;
        return;
    }
    cout << BOLD << BLUE << BLINK << "\n========== Historial de Ganadores ==========\n" << RESET;
    NodoGanador* actual = frente;
    while (actual) {
        cout << YELLOWS << "ID: " << RESET << actual->id << YELLOWS << " | Nombre: "<< RESET << actual->nombre << endl;
        actual = actual->siguiente;
    }
}
