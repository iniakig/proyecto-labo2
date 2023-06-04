#include "Permiso.h"

// Constructores
Permiso::Permiso(bool lectura, bool escritura, bool modificacion, bool baja)
{
    setLectura(lectura);
    setEscritura(escritura);
    setModificacion(modificacion);
    setBaja(baja);
}

// Setters
void Permiso::setLectura(bool lectura) {
    _lectura = lectura;
}

void Permiso::setEscritura(bool escritura) {
    _escritura = escritura;
}

void Permiso::setModificacion(bool modificacion) {
    _modificacion = modificacion;
}

void Permiso::setBaja(bool baja) {
    _baja = baja;
}

// Getters
bool Permiso::getLectura() {
    return _lectura;
}

bool Permiso::getEscritura() {
    return _escritura;
}

bool Permiso::getModificacion() {
    return _modificacion;
}

bool Permiso::getBaja() {
    return _baja;
}
