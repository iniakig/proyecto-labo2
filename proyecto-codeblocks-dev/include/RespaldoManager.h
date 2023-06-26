#ifndef RESPALDOMANAGER_H
#define RESPALDOMANAGER_H

#include "MarcaManager.h"

class RespaldoManager
{
    private:
        MarcaManager _marcaManager;
        ProductoManager _productoManager;

    public:
        void mostrarCrearRespaldos();
        void mostrarRestaurarRespaldos();

};

#endif // RESPALDOMANAGER_H
