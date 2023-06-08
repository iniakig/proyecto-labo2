#ifndef CLIENTEMANAGER_H
#define CLIENTEMANAGER_H

#include "ClienteArchivo.h"

class ClienteManager
{
    private:
        ClienteArchivo _archivo;
        bool permisos[3];

    public:
        void cargar();
        void listar(Cliente cliente);
        void modificar();
        void darDeBaja();
        void setPermisos(bool adm = false, bool sup = false, bool ven = false);
};

#endif // CLIENTEMANAGER_H
