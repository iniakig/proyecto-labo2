#include "UsuarioActivo.h"

#include <string.h>
#include <string>

UsuarioActivo::UsuarioActivo() {
    _id = -1;
    _rol = 0;
}

void UsuarioActivo::setId(int id) {
    _id = id;
}

void UsuarioActivo::setRol(int rol) {
    _rol = rol;
}

int UsuarioActivo::getId() {
    return _id;
}

int UsuarioActivo::getRol() {
    return _rol;
}

bool UsuarioActivo::crearArchivo(UsuarioActivo usuarioActivo) {
    FILE* p;

    p = fopen("usuarioActivo.dat", "wb");

    if (p == nullptr) {
        return false;
    }

    bool escribio = fwrite(&usuarioActivo, sizeof(UsuarioActivo), 1, p);

    fclose(p);

    return escribio;
}

int UsuarioActivo::getIdUsuarioActivo() {
    UsuarioActivo usuarioActivo;
    int id;

    FILE* p;

    p = fopen("usuarioActivo.dat", "rb");

    if (p == nullptr) {
        exit(666);
    }

    fread(&usuarioActivo, sizeof(UsuarioActivo), 1, p);

    id = usuarioActivo.getId();

    fclose(p);

    return id;
}

int UsuarioActivo::getRolUsuarioActivo() {
    UsuarioActivo usuarioActivo;
    int rol;

    FILE* p;

    p = fopen("usuarioActivo.dat", "rb");

    if (p == nullptr) {
        exit(666);
    }

    fread(&usuarioActivo, sizeof(UsuarioActivo), 1, p);

    rol = usuarioActivo.getRol();

    fclose(p);

    return rol;
}
