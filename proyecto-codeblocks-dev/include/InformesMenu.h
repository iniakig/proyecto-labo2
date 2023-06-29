#ifndef INFORMESMENU_H
#define INFORMESMENU_H

#include "ProductoManager.h"
#include "VentaManager.h"

class InformesMenu
{
    private:
        ProductoManager _productoManager;
        VentaManager _ventaManager;

    public:
        void mostrar();
};

#endif // INFORMESMENU_H
