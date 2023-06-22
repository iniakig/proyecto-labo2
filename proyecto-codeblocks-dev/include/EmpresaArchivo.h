#ifndef EMPRESAARCHIVO_H
#define EMPRESAARCHIVO_H

#include <string>
#include "Empresa.h"

class EmpresaArchivo
{
    private:
        std::string _nombre;

    public:
        EmpresaArchivo();
        EmpresaArchivo(std::string nombre);

        bool crear(Empresa empresa);
        Empresa leer();
        bool modificar(Empresa empresa);

        // Setters
        void setNombre(std::string nombre);
};

#endif // EMPRESAARCHIVO_H
