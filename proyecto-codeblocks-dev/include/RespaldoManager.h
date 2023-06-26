#ifndef RESPALDOMANAGER_H
#define RESPALDOMANAGER_H

#include "MarcaManager.h"
#include "UsuarioManager.h"
#include "ProductoManager.h"

class RespaldoManager
{
    private:
        UsuarioManager _usuarioManager;
        MarcaManager _marcaManager;
        ProductoManager _productoManager;

    public:
        void mostrarCrearRespaldos();
        void mostrarRestaurarRespaldos();

};

#endif // RESPALDOMANAGER_H
