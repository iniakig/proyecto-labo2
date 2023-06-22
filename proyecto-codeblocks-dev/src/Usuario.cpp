#include "Usuario.h"

// Constructores
Usuario::Usuario(int id, int tipoDocumento, const char* nroDocumento, const char* nombre, const char* apellido, const char* email, bool estado, Fecha fechaRegistro, const char* alias, const char* contrasenia, int rol) {
    setId(id);
    setTipoDocumento(tipoDocumento);
    setNroDocumento(nroDocumento);
    setNombre(nombre);
    setApellido(apellido);
    setEmail(email);
    setEstado(estado);
    setFechaRegistro(fechaRegistro);
    setAlias(alias);
    setContrasenia(contrasenia);
    setRol(rol);
}

// Interfaces

void Mostrar();

// Setters
void Usuario::setAlias(const char* alias) {
    strcpy(_alias, alias);
}

void Usuario::setContrasenia(const char* contrasenia) {
    strcpy(_contrasenia, contrasenia);
}

void Usuario::setRol(int rol) {
    _rol = rol;
}

// Getters

const char* Usuario::getAlias() {
    return _alias;
}

const char* Usuario::getContrasenia() {
    return _contrasenia;
}

int Usuario::getRol() {
    return _rol;
}

std::string Usuario::getRolDescripcion() {
    std::string rolDecripcion[3] = {"Administrador", "Supervisor", "Vendedor"};
    int rol = getRol();

    return rolDecripcion[rol];
}
