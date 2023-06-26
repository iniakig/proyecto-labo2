#ifndef RESPALDOMANAGER_H
#define RESPALDOMANAGER_H

#include "MarcaManager.h"
#include "UsuarioManager.h"
#include "ProductoManager.h"
#include "ClienteManager.h"

class RespaldoManager
{
    private:
        UsuarioManager _usuarioManager;
        ClienteManager _clienteManager;
        MarcaManager _marcaManager;
        ProductoManager _productoManager;

    public:
        void mostrarCrearRespaldos();
        void mostrarRestaurarRespaldos();
};

#endif // RESPALDOMANAGER_H
