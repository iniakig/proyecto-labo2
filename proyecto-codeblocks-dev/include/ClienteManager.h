#ifndef CLIENTEMANAGER_H
#define CLIENTEMANAGER_H

#include "ClienteArchivo.h"

class ClienteManager
{
    private:
        ClienteArchivo _archivo;
        bool permisos[3];

        int generarId(); // Hecho
        void listarPorNroDeDocumento(); // Pendiente
        void listarActivos();
        void listarInactivos();
        void listarPorBusquedaLibre(); // Pendiente
        void ordenarPorNombre(Cliente *listaDeClientes, int cantidadDeRegistros); // Hecho - Testear

    public:
        void cargar(); // Hecho - Testear
        bool cargar(std::string nroDocumento);
        void listar(Cliente cliente, int tipoListado); // Hecho - Testear
        void listarClientes(); // En curso
        void modificar(); // En curso
        void darDeBaja(); // Hecho - Testear
        void reactivar(); // Hecho - Testear
        bool reactivar(std::string nroDocumento);
        void setPermisos(bool adm = false, bool sup = false, bool ven = false); // Hecho - Testear
};

#endif // CLIENTEMANAGER_H
