#ifndef ENCABEZADO_H
#define ENCABEZADO_H

#include <iostream>
#include <string>

class Encabezado
{
private:
    std::string _titulo;
    int _ancho;

public:
    // Constructor
    Encabezado(std::string titulo, int ancho);

    // Interfaces
    void imprimirEncabezado();

    // Setters
    void setTitulo(std::string titulo);
    void setAncho(int ancho);

    // Getters
    std::string getTitulo();
    int getAncho();
};

#endif // ENCABEZADO_H
