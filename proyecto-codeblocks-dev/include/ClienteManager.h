#ifndef CLIENTEMANAGER_H
#define CLIENTEMANAGER_H

#include "ClienteArchivo.h"

class ClienteManager
{
    private:
        ClienteArchivo _archivo;
        bool permisos[3];

    public:
        void cargar(); // Hecho - Testear
        void listar(Cliente cliente, int tipoListado); // Hecho - Testear
        void modificar(); // En construccion
        void darDeBaja(); // Hecho - Testear
        void setPermisos(bool adm = false, bool sup = false, bool ven = false);
};

#endif // CLIENTEMANAGER_H
