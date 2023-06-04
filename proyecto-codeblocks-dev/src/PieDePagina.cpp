#include <iostream>
#include <string>

#include "PieDePagina.h"
#include "../rlutil.h"

// Constructores
PieDePagina::PieDePagina(std::string titulo, int ancho) {
    setTitulo(titulo);
    setAncho(ancho);
}

// Interfaces
void PieDePagina::imprimirPieDePagina() {
    int anchoDelTitulo = getTitulo().length();
    int anchoDeAsteriscos = (getAncho() - anchoDelTitulo - 2) / 2;
    rlutil::locate(1, rlutil::trows());
    std::cout << std::string(anchoDeAsteriscos, '*') << " " << getTitulo() << " " << std::string(anchoDeAsteriscos, '*');
}

// Setters
void PieDePagina::setTitulo(std::string titulo) {
    _titulo = titulo;
}

void PieDePagina::setAncho(int ancho) {
    _ancho = ancho;
}

// Getters
std::string PieDePagina::getTitulo() {
    return _titulo;
}

int PieDePagina::getAncho() {
    return _ancho;
}
