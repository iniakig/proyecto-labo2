#ifndef MARCAMANAGER_H
#define MARCAMANAGER_H
#include "MarcaArchivo.h"

class MarcaManager
{
    public:
    void cargar();

    private:
        MarcaArchivo _archivo;
        MarcaArchivo _archivoBkp = MarcaArchivo("marca.bkp");
        int generarID();
};

#endif // MARCAMANAGER_H
