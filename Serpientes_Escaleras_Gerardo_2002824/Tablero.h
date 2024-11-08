#pragma once
#include <vector>
#include <map>
using namespace std;

class Tablero {
public:
    //Atributos 
    int numCasillas = 0;
    vector<int> casillas;
    //Se declaran map, ya que cada casilla tiene su valor unico
    map<int, int> escaleras;
    map<int, int> serpientes;

public:
    //Constructor
    Tablero(int numCasillas);
    Tablero();

    //Metodos para configurar el tablero
    void generarTablero();                //Genera casillas normales, escaleras y serpientes
    int obtenerDestino(int posicion); //Devuelve la casilla de destino si es escalera/serpiente
    void mostrarTablero();          //Muestra el tablero en consola
    bool esEscalera(int posicion);  //Metodo para verificar si es escalera
    bool esSerpiente(int posicion); //Metodo para verificar si es serpiente

private:
    //Metodo para usar dentro de la clase tablero 
    void colocarEscalerasYSerpientes();//Coloca escaleras y serpientes aleatoriamente
};