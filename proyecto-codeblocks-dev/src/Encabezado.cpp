#include "Encabezado.h"
#include "../rlutil.h"


// Constructores
Encabezado::Encabezado(std::string titulo, int ancho) {
    setTitulo(titulo);
    setAncho(ancho);
}


// Interfaces
void Encabezado::imprimirEncabezado() {
    int anchoDelTitulo = getTitulo().length();
    int anchoDeAsteriscos = (getAncho() - anchoDelTitulo - 2) / 2;
    rlutil::locate(1, 1);
    std::cout << std::string(anchoDeAsteriscos, '*') << " " << getTitulo() << " " << std::string(anchoDeAsteriscos, '*') << std::endl;
}

// Setters
void Encabezado::setTitulo(std::string titulo) {
    _titulo = titulo;
}

void Encabezado::setAncho(int ancho) {
    _ancho = ancho;
}

// Getters

std::string Encabezado::getTitulo() {
    return _titulo;
}

int Encabezado::getAncho() {
    return _ancho;
}
