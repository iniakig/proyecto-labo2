#include "Cliente.h"

#include <string>

Cliente::Cliente(int tipoDocumento, const char* nroDocumento, const char* nombre, const char* apellido, const char* razonSocial, const char* email, const char* domicilio, const char* localidad, int provincia, bool estado, Fecha fechaRegistro) {
    setTipoDocumento(tipoDocumento);
    setNroDocumento(nroDocumento);
    setNombre(nombre);
    setApellido(apellido);
    setRazonSocial(razonSocial);
    setEmail(email);
    setDomicilio(domicilio);
    setLocalidad(localidad);
    setProvincia(provincia);
    setEstado(estado);
    setFechaRegistro(fechaRegistro);
}

void Cliente::setDomicilio(std::string domicilio) {
    strcpy(_domicilio, domicilio.c_str());
}

void Cliente::setLocalidad(std::string localidad) {
    strcpy(_localidad, localidad.c_str());
}

void Cliente::setProvincia(int provincia) {
    _provincia = provincia;
}

std::string Cliente::getDomicilio() {
    return _domicilio;
}

std::string Cliente::getLocalidad() {
    return _localidad;
}

int Cliente::getProvincia() {
    return _provincia;
}

std::string Cliente::getProvinciaDescripcion() {
    std::string provincia;
    std::string provincias[24] = {
        "CABA",
        "Buenos Aires",
        "Catamarca",
        "Chaco",
        "Chubut",
        "Córdoba",
        "Corrientes",
        "Entre Ríos",
        "Formosa",
        "Jujuy",
        "La Pampa",
        "La Rioja",
        "Mendoza",
        "Misiones",
        "Neuquén",
        "Río Negro",
        "Salta",
        "San Juan",
        "San Luis",
        "Santa Cruz",
        "Santa Fe",
        "Santiago del Estero",
        "Tierra del Fuego",
        "Tucumán"
    };

    provincia = provincias[getProvincia() - 1];

    return provincia;
}
