#include "UsuarioActivo.h"

#include <string.h>
#include <string>

UsuarioActivo::UsuarioActivo() {
    strcpy(_alias, "null");
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

std::string UsuarioActivo::leerArchivo() {
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

void UsuarioActivo::setAlias(std::string alias) {
    strcpy(_alias, alias.c_str());
}

std::string UsuarioActivo::getAlias() {
    return _alias;
}
