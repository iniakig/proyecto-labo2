#ifndef USUARIOARCHIVO_H
#define USUARIOARCHIVO_H

#include <iostream>
#include <string>
#include <Usuario.h>

class UsuarioArchivo
{
private:
    std::string _nombre;

public:
    // Constructores
    UsuarioArchivo();
    UsuarioArchivo(std::string nombre);

    // Interfaces
    int buscar(std::string nroDocumento);
    int buscar(int tipoDocumento, std::string nroDocumento);
    //int buscar(std::string alias);

    bool crear(Usuario reg);
    Usuario leer(int posicion);
    Usuario leer(Usuario* listadoDeUsuarios, int cantidadDeRegistros);
    bool modificar(Usuario reg, int posicion);
    bool darDeBaja (Usuario reg, int posicion);

    // Setters
    void setNombre(std::string nombre);

    // Getters
    int getCantidadDeUsuarios();
};

#endif // USUARIOARCHIVO_H
