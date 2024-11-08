#pragma once
#include <random>
using namespace std;
class Dado
{
private:
	//Atributos 
	mt19937 generador; //Este es el motor para generar numeros aleatorios
	uniform_int_distribution<int> distribucion; //Distribución uniforme para valores entre 1 y 6
public: 
	//Constructor
	Dado();

	//Metodos
	int lanzarDado();
};