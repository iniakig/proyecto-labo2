#ifndef EMPRESA_H
#define EMPRESA_H

#include "Persona.h"

class Empresa: public Persona
{
    private:

    public:
        Empresa(int tipoDocumento = 2, const char* nroDocumento = "null", const char* nombre = "null", const char* apellido = "null", const char* razonSocial = "null", const char* email = "null", bool estado = false, Fecha fechaRegistro = Fecha());
};

#endif // EMPRESA_H
