#ifndef MARCAMANAGER_H
#define MARCAMANAGER_H
#include "MarcaArchivo.h"

class MarcaManager
{
public:
    void cargar();
    Marca cargarDesdeProducto(std::string nombreMarca);

    void modificar();

    void listar(Marca marca);
    void listarXID();
    void listarXNombre();
    void listarTodos();

private:
    MarcaArchivo _archivo;
    MarcaArchivo _archivoBkp = MarcaArchivo("marca.bkp");
    int generarID();
    void modificarXID();
    void modificaarXNombre();
};

#endif // MARCAMANAGER_H
