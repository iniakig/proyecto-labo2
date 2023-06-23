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

        bool crear(Empresa empresa); // Hecho - Testear
        Empresa leer(); // Hecho - Testear

        // Setters
        void setNombre(std::string nombre);
};

#endif // EMPRESAARCHIVO_H
