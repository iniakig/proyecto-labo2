#include "Empresa.h"


Empresa::Empresa(int tipoDocumento, const char* nroDocumento, const char* nombre, const char* apellido, const char* razonSocial, const char* email, bool estado, Fecha fechaRegistro)
{
    setTipoDocumento(tipoDocumento);
    setNroDocumento(nroDocumento);
    setNombre(nombre);
    setApellido(apellido);
    setRazonSocial(razonSocial);
    setEmail(email);
    setEstado(estado);
    setFechaRegistro(fechaRegistro);
    setEstado(estado);
}
