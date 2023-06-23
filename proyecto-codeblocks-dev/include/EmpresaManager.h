#ifndef EMPRESAMANAGER_H
#define EMPRESAMANAGER_H

#include "EmpresaArchivo.h"

class EmpresaManager
{
    private:
        EmpresaArchivo _archivo;

    public:
        void cargar();
        void listar();
};

#endif // EMPRESAMANAGER_H
