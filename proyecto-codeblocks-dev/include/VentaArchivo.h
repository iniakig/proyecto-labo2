#ifndef VENTAARCHIVO_H_INCLUDED
#define VENTAARCHIVO_H_INCLUDED
#include "Venta.h"
class VentaArchivo
{
private:
    std::string _ruta;

public:
    VentaArchivo();
    VentaArchivo(std::string ruta);

    int getCantidadRegistros();

    bool guardar(Venta reg, int posRegAReemplazar);
    bool guardar(Venta reg);
    bool guardar(Venta *vec, int cantidadRegistrosAEscribir);

    int buscar(int ID);

    Venta leer(int nroRegistro);
    void leer(Producto *vec, int cantidadRegistrosALeer);

    void vaciar();
};

#endif // VENTAARCHIVO_H_INCLUDED
