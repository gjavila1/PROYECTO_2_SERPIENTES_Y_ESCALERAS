#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <regex>
#include "ColaHistorialGanadores.h"
#include "ListaJugadores.h"
#include "Tablero.h"
#include "Dado.h"
#define GREEN   "\033[1;32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define YELLOW  "\033[1;33m"
#define YELLOWS "\033[33m"
#define BLUE    "\033[34m"
#define BLINK "\x1b[5m"


using namespace std;

ListaJugadores lista; //Instancia global de ListaJugadores
Tablero tablero;
ColaHistorialGanadores colahistorialganadores;


bool ValidacionNombre(const string& simbolos) {
	//Expresion regular que permite solo letras mayusculas, minusculas y espacios
	regex pattern("^[a-zA-Z\\s]+$");

	//Compara la cadena 'simbolos' con el patron definido
	return regex_match(simbolos, pattern);
}

//Menu para los jugadores
void menuJugadores() {
	int opcion = 0;
	string nombre;

	do {
		cout << BOLD << BLUE << BLINK "\n===============================" << RESET << endl;
		cout << YELLOWS << "1." << RESET << " Agregar jugador" << endl;
		cout << YELLOWS << "2." << RESET << " Mostrar jugadores" << endl;
		cout << YELLOWS << "3." << RESET << " Volver al menu principal" << RESET << endl;
		cout << YELLOW << "Seleccione una opcion: " << RESET;
		while (!(cin >> opcion)) {
			cout << RED << BLINK << "\n-------------------------------\n" << RESET;
			cout << RED << BLINK << "Entrada invalida!" << RESET;
			cout << RED << BLINK << "\n-------------------------------\n" << RESET;
			cin.clear();  // Limpiar cualquier error de entrada
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar cualquier entrada no valida
			cout << YELLOW << "\nIngrese nuevamente la opcion que desea realizar: " << RESET;
		}
		switch (opcion) {
		case 1:
			//Agregar jugador
			int numJugadores;
			cout << BOLD << BLUE << BLINK << "\n===============================" << RESET;
			cout << YELLOW << "\nIngrese la cantidad de jugadores: " << RESET;
			while (!(cin >> numJugadores)) {
				cout << RED << BLINK << "\n-------------------------------\n" << RESET;
				cout << RED << BLINK << "Entrada invalida!" << RESET;
				cout << RED << BLINK << "\n-------------------------------\n" << RESET;
				cin.clear();  // Limpiar cualquier error de entrada
				cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar cualquier entrada no valida
				cout << YELLOW << "\nIngrese nuevamente la opcion que desea realizar: " << RESET;
			}
			//Verificar que la cantidad minima de jugadores sea 2
			if (numJugadores < 2) {
				cout << YELLOW << "\nLa cantidad minima de jugadores es de 2." << RESET << endl;
				return;
			}

			for (int i = 0; i < numJugadores; i++) {
				int id = 0;
				string nombre;
				string entrada;
				//Validacion de enteros
				cout << BOLD << BLINK << BLUE << "\n-------------------------------" << RESET;
				cout << YELLOW << "\nIngrese el ID del jugador: " << RESET;
				while (!(cin >> id)) {
					cout << RED << BLINK << "\n-------------------------------\n" << RESET;
					cout << RED << BLINK << "Entrada invalida!" << RESET;
					cout << RED << BLINK << "\n-------------------------------\n" << RESET;
					cin.clear();  // Limpiar cualquier error de entrada
					cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar cualquier entrada no válida
					cout << YELLOW << "\nIngrese nuevamente la opcion que desea realizar: " << RESET;
				}

				cout << YELLOW << "Ingrese el nombre del jugador: " << RESET;
				cin >> nombre;
				//Validacion para el nombre
				if (ValidacionNombre(nombre)) {
					cout << BOLD << BLUE << BLINK << "===============================" << RESET << endl;
					cout << YELLOW << "Jugador agregado exitosamente!" << RESET << endl;
					lista.agregarJugador(id, nombre);
				}
				else {
					cout << RED << BLINK << "\n-------------------------------" << RESET;
					cout << RED << BLINK << "\nNombre invalido!\nSolo se permiten letras y espacios.\n" << RESET;
					cout << RED << BLINK << "-------------------------------" << RESET << endl;
				}

			}
			break;

		case 2:
			//Mostrar jugadores
			lista.mostrarJugadores();
			break;

		case 3:
			//Volver al menu principal
			cout << GREEN << BLINK << "\n-------------------------------" << RESET << endl;
			cout << GREEN << BLINK << "Regresando al menu principal..." << RESET << endl;
			cout << GREEN << BLINK << "-------------------------------" << RESET << endl;
			break;

		default:
			cout << RED << BLINK << "\n-------------------------------" << RESET << endl;
			cout << RED << BLINK << "Opcion invalida. Intente nuevamente." << RESET << endl;
			cout << RED << BLINK << "-------------------------------" << RESET << endl;

		}
	} while (opcion != 3);
}

//Funcion para iniciar el juego
void iniciarJuego(int numCasillas) {
	Tablero tablero(numCasillas);
	Dado dado;
	bool juegoTerminado = false;
	NodoJugador* jugadorActual = lista.header;

	//Mostrar el tablero inicial
	tablero.mostrarTablero();

	//Verificar si hay jugadores
	if (!jugadorActual) {
		cout << YELLOW << "No hay jugadores registrados. Agregue jugadores antes de comenzar." << RESET << endl;
		return;
	}

	//Juego
	while (!juegoTerminado) {
		cout << BOLD << BLUE << BLINK << "===============================" << RESET;
		cout << YELLOW << "\nTurno de " << RESET << jugadorActual->nombre << YELLOWS << "(ID: " << RESET << jugadorActual->jugadorID << YELLOWS << ")" << RESET << endl;

		//Esperar a que el usuario presione Enter para lanzar el dado
		cout << jugadorActual->nombre << YELLOW << ", presiona Enter para lanzar el dado..." << RESET;
		cin.ignore();
		cin.get();  //Lee la tecla Enter para continuar

		int lanzamiento = dado.lanzarDado();
		cout << jugadorActual->nombre << YELLOW << " lanza el dado y obtiene: " << RESET << lanzamiento << endl;

		//Calcular nueva posicion
		int nuevaPosicion = jugadorActual->posicion + lanzamiento;


		//Comprobar si llega a la ultima casilla o la supera
		if (nuevaPosicion >= numCasillas - 1) {
			cout << jugadorActual->nombre << YELLOW << " ha ganado el juego al llegar a la ultima casilla!" << RESET << endl;
			colahistorialganadores.agregarGanador(jugadorActual->nombre, jugadorActual->jugadorID);
			juegoTerminado = true;
			break;
		}

		//Revisar si la nueva posicion tiene una escalera o serpiente
		int destino = tablero.obtenerDestino(nuevaPosicion);
		if (destino != nuevaPosicion) {
			if (destino > nuevaPosicion) {
				cout << jugadorActual->nombre << YELLOW << " sube por una escalera a la casilla " << RESET << destino << "!" << endl;
			}
			else {
				cout << jugadorActual->nombre << YELLOW << " baja por una serpiente a la casilla " << RESET << destino << YELLOW << "!" << RESET << endl;
			}
			nuevaPosicion = destino;
		}

		//Actualizar posicion del jugador
		jugadorActual->posicion = nuevaPosicion;
		cout << BOLD << BLUE << BLINK "-------------------------------\n" << RESET;
		cout << jugadorActual->nombre << YELLOW << " se mueve a la casilla " << RESET << nuevaPosicion << endl;
		//Pasar al siguiente jugador
		jugadorActual = jugadorActual->next ? jugadorActual->next : lista.header;
	}
}

//Menu de bienvenida y opciones principales
void menuInicio() {
	int opciont;
	int numCasillas = 0;

	do {
		cout << BOLD << BLUE << BLINK << "\n========== Serpientes y Escaleras ==========" << RESET << endl;
		cout << YELLOWS << "1." << RESET << " Crear Tablero" << endl;
		cout << YELLOWS << "2." << RESET << " Jugadores" << endl;
		cout << YELLOWS << "3." << RESET << " Iniciar Juego" << endl;
		cout << YELLOWS << "4." << RESET << " Hisotrial de Victorias" << endl;
		cout << YELLOWS << "5." << RESET << " Salir" << endl;
		cout << YELLOW << "Seleccione una opcion: " << RESET;
		while (!(cin >> opciont)) {
			cout << RED << BLINK << "\n-------------------------------\n" << RESET;
			cout << RED << BLINK << "Entrada invalida!" << RESET;
			cout << RED << BLINK << "\n-------------------------------\n" << RESET;
			cin.clear();  // Limpiar cualquier error de entrada
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar cualquier entrada no valida
			cout << YELLOW << "\nIngrese nuevamente la opcion que desea realizar: " << RESET;
		}

		switch (opciont) {
		case 1:
			//Crear el tablero
			cout << BOLD << BLINK << BLUE << "\n===============================" << RESET;
			cout << YELLOW << "\nIngrese el numero de casillas (minimo 30 y multiplo de 5): " << RESET;
			while (!(cin >> numCasillas)) {
				cout << RED << BLINK << "\n-------------------------------\n" << RESET;
				cout << RED << BLINK << "Entrada invalida!" << RESET;
				cout << RED << BLINK << "\n-------------------------------\n" << RESET;
				cin.clear();  // Limpiar cualquier error de entrada
				cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar cualquier entrada no valida
				cout << YELLOW << "\nIngrese nuevamente la opcion que desea realizar: " << RESET;
			}
			if (numCasillas >= 30 && numCasillas % 5 == 0) {
				cout << BOLD << BLINK << BLUE << "-------------------------------" << RESET << endl;
				cout << YELLOW << "Su tablero de " << RESET << numCasillas << YELLOW << " casillas fue creado exitosamente!" << RESET << endl;
			}
			else {
				cout << YELLOW << "Numero de casillas invalido!" << RESET << endl;
			}

			break;

		case 2:
			//Menu de jugadores
			menuJugadores();
			break;

		case 3:
			//Iniciar el juego si el tablero ya fue creado

			if (numCasillas >= 30 && numCasillas % 5 == 0) {
				iniciarJuego(numCasillas);
			}
			else {
				cout << YELLOW << "Debe crear un tablero valido antes de iniciar el juego." << RESET << endl;
			}
			break;
		case 4:
			colahistorialganadores.mostrarGanadores();
			break;
		case 5:
			cout << BLUE << BLINK << "\n-------------------------------" << RESET << endl;
			cout << BLUE << BLINK << "Saliendo del programa..." << RESET;
			cout << BLUE << BLINK << "\n-------------------------------" << RESET << endl;
			break;
		default:
			cout << RED << BLINK << "\n-------------------------------" << RESET << endl;
			cout << RED << BLINK << "Opcion invalida. Intente nuevamente." << RESET << endl;
			cout << RED << BLINK << "-------------------------------" << RESET << endl;
		}
	} while (opciont != 5);
}

int main() {
	cout << YELLOWS << BLINK << "Bienvenido a Serpientes y Escaleras!!" << RESET << endl;
	menuInicio();
	return 0;
}