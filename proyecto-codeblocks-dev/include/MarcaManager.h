#ifndef MARCAMANAGER_H
#define MARCAMANAGER_H
#include "MarcaArchivo.h"
#include "ProductoArchivo.h"

class MarcaManager
{
public:
    void cargar();
    int cargarDesdeProducto(std::string nombreMarca);

    void modificar();

    void eliminar();
    void reactivar();

    void listar(Marca marca);
    void listarXID();
    void listarXNombre();
    void listarTodos();

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
