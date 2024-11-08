#include "Tablero.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define BLUE    "\033[34m"
#define BLINK "\x1b[5m"

using namespace std;        //revisar de nuevo la clase tablero

//Constructor
Tablero::Tablero(int numCasillas) : numCasillas(numCasillas) {
    generarTablero();
}
Tablero::Tablero(){}

//Metodo para generar el tablero
void Tablero::generarTablero() {
    casillas.resize(numCasillas, 0); //Inicializa todas las casillas como normales
    colocarEscalerasYSerpientes();   //Coloca escaleras y serpientes de manera aleatoria
}

//Metodo para colocar escaleras y serpientes de forma aleatoria
void Tablero::colocarEscalerasYSerpientes() {
    srand(static_cast<unsigned>(time(nullptr))); //Semilla para numeros aleatorios
    
    int maxEspeciales = numCasillas / 4; //25% del total de casillas
    int numEscaleras = maxEspeciales / 2; // 50% para escaleras y 50% para serpientes
    int numSerpientes = maxEspeciales - numEscaleras;

    //Colocar escaleras
    for (int i = 0; i < numEscaleras; ++i) {
        int inicio, fin;
        do {
            inicio = rand() % (numCasillas - 2);
            fin = inicio + 1 + (rand() % (numCasillas - inicio - 1));
        } while (inicio >= fin || fin >= numCasillas ||
            escaleras.count(inicio) || serpientes.count(inicio) ||
            escaleras.count(fin) || serpientes.count(fin));
        
        escaleras[inicio] = fin;//Marca la casilla de inicio y fin de la escalera
        casillas[inicio] = 1; //Marca la casilla como escalera
    }

    //Colocar serpientes
    for (int i = 0; i < numSerpientes; ++i) {
        int inicio, fin;
        do {
            inicio = rand() % (numCasillas - 1) + 1;
            fin = inicio - 1 - (rand() % inicio);
        } while (fin >= inicio  || inicio == 0 || fin == 0 ||escaleras.count(inicio) || serpientes.count(inicio) || escaleras.count(fin) || serpientes.count(fin));
        
        serpientes[inicio] = fin;
        casillas[inicio] = -1; //Marca la casilla como serpiente
    }
}

//Metodo para obtener el destino de una casilla especial (escalera o serpiente)
int Tablero::obtenerDestino(int posicion){
    if (escaleras.count(posicion)) {
        return escaleras.at(posicion);
    }
    else if (serpientes.count(posicion)) {
        return serpientes.at(posicion);
    }
    return posicion; //Si es casilla normal, retorna la misma posicion
}

//Metodo para verificar si una casilla tiene una escalera
bool Tablero::esEscalera(int posicion) {
    return escaleras.count(posicion) > 0;
}

//Metodo para verificar si una casilla tiene una serpiente
bool Tablero::esSerpiente(int posicion) {
    return serpientes.count(posicion) > 0;
}


//Metodo para mostrar el tablero
void Tablero::mostrarTablero(){
    cout << BOLD << BLUE << BLINK << "\n========== Tablero de Juego ==========\n"<<RESET;
    static const int columnas = 6;
    for (int i = 0; i < numCasillas; ++i) {
        if (casillas[i] == 1) {
            cout << CYAN << BLINK <<  "[E] " << RESET; //Escalera
        }
        else if (casillas[i] == -1) {
            cout << GREEN << BLINK << "[S] " << RESET; //Serpiente
        }
        else {
            cout << MAGENTA << "[ ] " << RESET; //Casilla normal
        }

        if ((i + 1) % columnas == 0) cout << endl; //Salto de línea cada 6 casillas
    }
    cout << endl;
}