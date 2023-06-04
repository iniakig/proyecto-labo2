#include "UsuarioArchivo.h"

// Constructor
UsuarioArchivo::UsuarioArchivo() {
    setNombre("usuarios.dat");
}

UsuarioArchivo::UsuarioArchivo(std::string nombre)
{
    setNombre(nombre);
}

// Interfaces
int UsuarioArchivo::buscar(int tipoDocumento, std::string nroDocumento) {
    Usuario reg;
    int posicion = -1;
    int cantidadDeUsuarios = getCantidadDeUsuarios();

    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        return false;
    }

    for (int i = 0; i < cantidadDeUsuarios; i++) {
        reg = leer(i);
        if (reg.getTipoDocumento() == tipoDocumento && strcmp(reg.getNroDocumento(), nroDocumento.c_str()) == 0) {
            posicion = i;
        }
    }

    return posicion;
}

int UsuarioArchivo::buscar(std::string alias) {
    Usuario usuario;
    int posicion = -1;
    int cantidadDeUsuarios = getCantidadDeUsuarios();

    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        return false;
    }

    for (int i = 0; i < cantidadDeUsuarios; i++) {
        usuario = leer(i);
        if (strcmp(usuario.getAlias(), alias.c_str()) == 0) {
            posicion = i;
        }
    }

    return posicion;
}

Usuario UsuarioArchivo::leer(int posicion) {
    Usuario reg;
    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        return false;
    }

    fseek(p, sizeof(Usuario) * posicion, SEEK_SET);
    fread(&reg, sizeof(Usuario), 1, p);
    fclose(p);

    return reg;
}

bool UsuarioArchivo::crear(Usuario reg) {
    FILE* p;

    p = fopen(_nombre.c_str(), "ab");

    if (p == nullptr) {
        return false;
    }

    bool escribio = fwrite(&reg, sizeof(Usuario), 1, p);

    fclose(p);

    return escribio;
}

// Setters
void UsuarioArchivo::setNombre(std::string nombre) {
    _nombre = nombre;
}

// Getters
int UsuarioArchivo::getCantidadDeUsuarios() {
    Usuario reg;
    int cantidadDeUsuarios = 0;

    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        return false;
    }

    while (fread(&reg, sizeof (Usuario), 1, p) == 1) {
        cantidadDeUsuarios++;
    }

    fclose(p);

    return cantidadDeUsuarios;
}