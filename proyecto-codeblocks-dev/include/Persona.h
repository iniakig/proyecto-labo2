#ifndef PERSONA_H
#define PERSONA_H

#include "Fecha.h"

class Persona {
private:
    int _tipoDocumento; // Puede ser: ( 1. DNI | 2. CUIL | 3. CUIT )
    char _nroDocumento[12];
    char _nombre[15];
    char _apellido[15];
    char _razonSocial[30];
    char _email[35];
    bool _estado;
    Fecha _fechaRegistro;

public:
    // Constructores
    Persona(int tipoDocumento = 0, const char* nroDocumento = "null", const char* nombre = "null", const char* apellido = "null", const char* razonSocial = "null", const char* email = "null", bool estado = "false", Fecha fechaRegistro = Fecha());

    // Interfaces
    void Mostrar();

    // Setters
    void setTipoDocumento(int tipoDocumento);
    void setNroDocumento(const char* nroDocumento);
    void setNombre(const char* nombre);
    void setApellido(const char* apellido);
    void setRazonSocial(const char* razonSocial);
    void setEmail(const char* email);
    void setEstado(bool estado);
    void setFechaRegistro(Fecha fechaRegistro);

    // Getters
    int getTipoDocumento();
    std::string getTipoDocumentoDescripcion();
    const char* getNroDocumento();
    const char* getNombre();
    const char* getApellido();
    const char* getRazonSocial();
    const char* getEmail();
    bool getEstado();
    std::string getEstadoDescripcion();
    Fecha getFechaRegistro();
};

#endif // PERSONA_H
