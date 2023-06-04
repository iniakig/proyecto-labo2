#ifndef USUARIOMANAGER_H
#define USUARIOMANAGER_H

#include "UsuarioArchivo.h"

class UsuarioManager
{
private:
    UsuarioArchivo _archivo;
    bool _permisos[3]; // Posición 0. Adm | 1. Sup | 2. Ven

    int generarId();

    void listar(Usuario usuario, int tipoListad0o);
    void listarPorAlias();
    void listarPorDNI();
    void listarActivos();
    void listarInactivos();

public:
    void cargar();
    void listarUsuarios();
    void ordenarPorAlias();
    void modificar();
    void darDeBaja();
    void setPermisos(bool adm = false, bool sup = false, bool ven = false);
};

#endif // USUARIOMANAGER_H
