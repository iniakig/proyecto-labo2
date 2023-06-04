#ifndef MARCAARCHIVO_H
#define MARCAARCHIVO_H
#include "Marca.h"

#include <string>
#include <cstdio>

class MarcaArchivo
{
public:
    //CONSTRUCTORES
    MarcaArchivo();
    MarcaArchivo(std::string ruta);

    //GETTERS
    int getCantidadDeRegistros();

    //INTERFACES
    bool guardar(Marca reg);
    bool guardar(Marca reg, int posicionAReemplazar);
    bool guardar(Marca *vec, int cantidadRegistrosAEscribir);

    int buscar(std::string nombreMarca);
    int buscar(int ID);

    Marca leer(int posicion);
    void leer(Marca *vec, int cantidadRegistrosALeer);

    void vaciar();

private:
    std::string _ruta;
};

#endif // MARCAARCHIVO_H
