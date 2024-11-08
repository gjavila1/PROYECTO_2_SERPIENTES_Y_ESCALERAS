#pragma once
#include <iostream>
#include <string>
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define BLUE    "\033[34m"
#define YELLOWS "\033[33m"
#define BLINK "\x1b[5m"
using namespace std;

struct NodoGanador {
    string nombre;
    int id = 0;
    NodoGanador* siguiente;

    NodoGanador(const string& nombre, int id) : nombre(nombre), id(id), siguiente(nullptr) {}
};

class ColaHistorialGanadores {
private:
    NodoGanador* frente;
    NodoGanador* final;

public:
    ColaHistorialGanadores();
    ~ColaHistorialGanadores();

    void agregarGanador(const string& nombre, int id);  // Agrega un ganador a la cola
    void mostrarGanadores();              // Muestra todos los ganadores
};
