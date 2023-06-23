#ifndef EMPRESA_H
#define EMPRESA_H

#include "Persona.h"

class Empresa: public Persona
{
    private:
        char _domicilio[45];
        char _localidad[20];
        int _provincia;

    public:
        Empresa(int tipoDocumento = 2, const char* nroDocumento = "null", const char* nombre = "null", const char* apellido = "null", const char* razonSocial = "null", const char* email = "null", const char* domicilio = "null", const char* localidad = "null", int provincia = 0, bool estado = false, Fecha fechaRegistro = Fecha());

        // Setters
        void setDomicilio(std::string domicilio);
        void setLocalidad(std::string localidad);
        void setProvincia(int provincia);

        // Getters
        std::string getDomicilio();
        std::string getLocalidad();
        int getProvincia();
        std::string getProvinciaDescripcion();
};

#endif // EMPRESA_H
