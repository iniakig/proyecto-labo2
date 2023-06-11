#ifndef CLIENTEMANAGER_H
#define CLIENTEMANAGER_H

#include "ClienteArchivo.h"

class ClienteManager
{
    private:
        ClienteArchivo _archivo;
        bool permisos[3];
        void listar(Cliente cliente, int tipoListado); // Hecho - Testear
        void listarPorNombreDeCliente(); // Pendiente
        void listarPorAlias(); // Pendiente
        void listarPorNroDeDocumento(); // Pendiente
        void listarPorBusquedaLibre(); // Pendiente

    public:
        void cargar(); // Hecho - Testear
        void listarClientes(); // En curso
        void modificar(); // Hecho - Testear
        void darDeBaja(); // Hecho - Testear
        void reactivar(); // Hecho - Testear
        void setPermisos(bool adm = false, bool sup = false, bool ven = false); // Hecho - Testear
};

#endif // CLIENTEMANAGER_H
