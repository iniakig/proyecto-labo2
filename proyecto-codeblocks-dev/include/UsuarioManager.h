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
    UsuarioArchivo _archivoBkp = UsuarioArchivo("usuarios.bkp");
    bool _permisos[3]; // Posición 0. Adm | 1. Sup | 2. Ven

    int generarId(); // Hecho
    void listar(Usuario usuario, int tipoListado); // Hecho - Testear
    void listarPorAlias(); // Hecho - Testear
    void listarPorDNI(); // Hecho - Testear
    void listarActivos(); // Hecho - Testear
    void listarInactivos(); // Hecho - Testear
    void listarPorBusquedaLibre();
    void ordenarPorAlias(Usuario *listaDeUsuarios, int cantidadDeRegistros); // Hecho - Testear
    void ordenarPorFecha(Usuario *listaDeUsuarios, int cantidadDeRegistros); // Hecho - Testear

public:
    void cargar(); // Hecho - Testear
    void modificar(); // Hecho - Testear
    void darDeBaja(); // Hecho - Testear
    void reactivar(); // Hecho - Testear
    void listarUsuarios(); // Hecho - Testear
    void hacerCopiaDeSeguridad(); // Hecho - OK
	void restaurarCopiaDeSeguridad(); // Hecho - OK
	void setPermisos(bool adm = false, bool sup = false, bool ven = false); // Hecho
};

#endif // USUARIOMANAGER_H
