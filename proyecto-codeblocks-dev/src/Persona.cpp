#include "Persona.h"

// Constructores
Persona::Persona(int id, int tipoDocumento, const char* nroDocumento, const char* nombre, const char* apellido, const char* razonSocial, const char* email, bool estado, Fecha fechaRegistro) {
    setId(id);
    setTipoDocumento(tipoDocumento);
    setNroDocumento(nroDocumento);
    setNombre(nombre);
    setApellido(apellido);
    setRazonSocial(razonSocial);
    setEmail(email);
    setEstado(estado);
    setFechaRegistro(fechaRegistro);
}

// Setters
void Persona::setId(int id) {
    _id = id;
}

void Persona::setTipoDocumento(int tipoDocumento) {
    _tipoDocumento = tipoDocumento;
}

void Persona::setNroDocumento(const char* nroDocumento) {
    strcpy(_nroDocumento, nroDocumento);
}

void Persona::setNombre(const char* nombre) {
    strcpy(_nombre, nombre);
}

void Persona::setApellido(const char* apellido) {
    strcpy(_apellido, apellido);
}

void Persona::setRazonSocial(const char* razonSocial) {
    strcpy(_razonSocial, razonSocial);
}

void Persona::setEmail(const char* email) {
    strcpy(_email, email);
}

void Persona::setEstado(bool estado) {
    _estado = estado;
}

void Persona::setFechaRegistro(Fecha fechaRegistro) {
        _fechaRegistro = fechaRegistro;
}

// Getters
int Persona::getId() {
    return _id;
}

int Persona::getTipoDocumento() {
    return _tipoDocumento;
}

std::string Persona::getTipoDocumentoDescripcion() {
    std::string tipoDocumento[3] = {"DNI", "CUIT"};

    int tipoDocumentoInt = getTipoDocumento();

    return tipoDocumento[tipoDocumentoInt - 1];
}

const char* Persona::getNroDocumento() {
    return _nroDocumento;
}

const char* Persona::getNombre() {
    return _nombre;
}

const char* Persona::getApellido() {
    return _apellido;
}

const char* Persona::getRazonSocial() {
    return _razonSocial;
}

const char* Persona::getEmail() {
    return _email;
}

bool Persona::getEstado() {
    return _estado;
}

Fecha Persona::getFechaRegistro() {
    return _fechaRegistro;
}

std::string Persona::getEstadoDescripcion() {
    if (getEstado()) {
        return "Activo";
    }
    else {
        return "Inactivo";
    }
}
