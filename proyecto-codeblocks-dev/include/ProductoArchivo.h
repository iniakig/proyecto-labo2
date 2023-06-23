#ifndef PRODUCTOARCHIVO_H_INCLUDED
#define PRODUCTOARCHIVO_H_INCLUDED
#include "Producto.h"
#include <string>
#include <cstdio>


class ProductoArchivo
{
public:
    //CONSTRUCTORES
    ProductoArchivo();
    ProductoArchivo(std::string ruta);

    //GETTERS
    int getCantidadDeRegistros();
    int getCantidadRegistrosActivos();

    //INTERFACES
    bool guardar(Producto reg);
    bool guardar(Producto reg, int posicionAReemplazar);
    bool guardar(Producto *vec, int cantidadRegistrosAEscribir);

    int buscar(int ID);

    Producto leer(int posicion);
    void leer(Producto *vec, int cantidadRegistrosALeer);

    void vaciar();

private:
    std::string _ruta;
};
#endif // PRODUCTOARCHIVO_H_INCLUDED
