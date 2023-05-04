#include "Usuario.h"

// Constructores
Usuario::Usuario(int tipoDocumento, const char* nroDocumento, const char* nombre, const char* apellido, const char* email, bool estado, Fecha fechaRegistro, const char* usuario, const char* contrasenia, int tipoPerfil) {
    setTipoDocumento(tipoDocumento);
    setNroDocumento(nroDocumento);
    setNombre(nombre);
    setApellido(apellido);
    setEmail(email);
    setEstado(estado);
    setFechaRegistro(fechaRegistro);
    setUsuario(usuario);
    setContrasenia(contrasenia);
    setTipoPerfil(tipoPerfil);
}

// Interfaces

void Mostrar();

// Setters
void Usuario::setUsuario(const char* usuario) {
    strcpy(_usuario, usuario);
}

void Usuario::setContrasenia(const char* contrasenia) {
    strcpy(_contrasenia, contrasenia);
}

void Usuario::setTipoPerfil(int tipoPerfil) {
    _tipoPerfil = tipoPerfil;
}

// Getters

const char* Usuario::getUsuario() {
    return _usuario;
}

const char* Usuario::getContrasenia() {
    return _contrasenia;
}

int Usuario::getTipoPerfil() {
    return _tipoPerfil;
}
