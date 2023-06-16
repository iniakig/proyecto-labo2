#ifndef USUARIOMANAGER_H
#define USUARIOMANAGER_H

#include "UsuarioArchivo.h"
#include "Usuario.h"
#include "../funciones.h"
#include <iostream>
#include <iomanip>
#include <../rlutil.h>

class UsuarioManager
{
private:
    UsuarioArchivo _archivo;
    bool _permisos[3]; // Posición 0. Adm | 1. Sup | 2. Ven

    void listar(Usuario usuario, int tipoListado); // En curso
    void listarPorAlias(); // Hecho - Testear
    void listarPorDNI(); // Hecho - Testear
    void listarActivos(); // En curso
    void listarInactivos(); // Para rehacer con memoria dinámica y ordenadores
    void ordenarPorAlias(Usuario *listaDeUsuarios, int cantidadDeRegistros); // Hecho - Testear
    void ordenarPorFecha(Usuario *listaDeUsuarios, int cantidadDeRegistros); // Hecho - Testear

public:
    void cargar(); // Hecho - Testear
    void modificar(); // Hecho - Testear
    void darDeBaja(); // Hecho - Testear
    void reactivar(); // Hecho - Testear
    void listarUsuarios(); // En curso
    void setPermisos(bool adm = false, bool sup = false, bool ven = false); // Hecho
};

#endif // USUARIOMANAGER_H
