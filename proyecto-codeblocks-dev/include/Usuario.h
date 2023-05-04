#ifndef USUARIO_H
#define USUARIO_H

#include "Persona.h"

class Usuario: private Persona {
private:
    char _usuario[30];
    char _contrasenia[30];
    int _tipoPerfil; // Puede ser: ( 1. SUPERADMINISTRADOR | 2. ADMINISTRADOR | 3. SUPERVISOR | 4. USUARIO )

public:
    // Constructores
    Usuario(int tipoDocumento = 0, const char* nroDocumento = "null", const char* nombre = "null", const char* apellido = "null", const char* email = "null", bool estado = "false", Fecha fechaRegistro = Fecha(), const char* usuario = "null", const char* contrasenia = "null", int tipoPerfil = 0);

    // Interfaces

    // Setters
    void setUsuario(const char* usuario);
    void setContrasenia(const char* contrasenia);
    void setTipoPerfil(int tipoPerfil);

    // Getters
    const char* getUsuario();
    const char* getContrasenia();
    int getTipoPerfil();

};

#endif // USUARIO_H
