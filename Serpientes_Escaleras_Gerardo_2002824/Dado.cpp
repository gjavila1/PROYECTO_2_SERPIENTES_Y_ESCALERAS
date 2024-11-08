#include "Dado.h"

//Constructor 
Dado::Dado() :distribucion(1, 6) {
	//Inicializa el generador de números aleatorios con una semilla basada en el tiempo
	generador.seed(static_cast<unsigned>(time(nullptr))); 
}

int Dado::lanzarDado() {
	return distribucion(generador);
}