#ifndef MARCAMANAGER_H
#define MARCAMANAGER_H
#include "MarcaArchivo.h"
#include "ProductoArchivo.h"
#include "ProductoManager.h"

#include <iostream>
#include <string>
#include <iomanip>

class MarcaManager
{
public:
    void cargar();
    int cargarDesdeProducto(std::string nombreMarca);

    void modificar();

    void eliminar();
    void reactivar();

    void listar(Marca marca, int tipoListado);
    void listarXID();
    void listarXNombre();
    void listarActivas();
    void listarInactivas();

    void hacerCopiaSeguridad();
    void restaurarCopiaSeguridad();

private:
    MarcaArchivo _archivo;
    MarcaArchivo _archivoBkp = MarcaArchivo("marcas.bkp");
    int generarID();
    void modificarXID();
    void modificarXNombre();
};

#endif // MARCAMANAGER_H
