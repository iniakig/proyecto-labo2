#ifndef USUARIO_H
#define USUARIO_H

#include "Persona.h"

class Usuario: public Persona {
private:
    char _alias[15];
    char _contrasenia[15];
    int _rol; // Puede ser: (0. ADMINISTRADOR | 1. SUPERVISOR | 2. USUARIO )

public:
    // Constructores
    Usuario(int tipoDocumento = 0, const char* nroDocumento = "null", const char* nombre = "null", const char* apellido = "null", const char* email = "null", bool estado = false, Fecha fechaRegistro = Fecha(), const char* alias = "null", const char* contrasenia = "null", int rol = -1);

    // Interfaces

    // Setters
    void setAlias(const char* alias);
    void setContrasenia(const char* contrasenia);
    void setRol(int rol);

    // Getters
    const char* getAlias();
    const char* getContrasenia();
    int getRol();
    std::string getRolDescripcion();

};

#endif // USUARIO_H
