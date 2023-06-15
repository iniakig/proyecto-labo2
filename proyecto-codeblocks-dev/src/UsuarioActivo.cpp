#include "UsuarioActivo.h"

#include <string.h>
#include <string>

UsuarioActivo::UsuarioActivo() {
    strcpy(_alias, "null");
    _rol = 0;
}

void UsuarioActivo::setAlias(std::string alias) {
    strcpy(_alias, alias.c_str());
}

void UsuarioActivo::setRol(int rol) {
    _rol = rol;
}

std::string UsuarioActivo::getAlias() {
    return _alias;
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

std::string UsuarioActivo::getAliasUsuarioActivo() {
    UsuarioActivo usuarioActivo;
    std::string alias;

    FILE* p;

    p = fopen("usuarioActivo.dat", "rb");

    if (p == nullptr) {
        exit(666);
    }

    fread(&usuarioActivo, sizeof(UsuarioActivo), 1, p);

    alias = usuarioActivo.getAlias();

    fclose(p);

    return alias;
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
