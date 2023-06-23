#include "UsuarioArchivo.h"

#include "../mensajes.h"

// Constructores
UsuarioArchivo::UsuarioArchivo() {
    setNombre("usuarios.dat");
}

UsuarioArchivo::UsuarioArchivo(std::string nombre)
{
    setNombre(nombre);
}

// Interfaces
int UsuarioArchivo::buscar(int id) {
    Usuario usuario;
    int posicion = -1;
    int cantidadDeUsuarios = getCantidadDeUsuarios();

    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        return -1;
    }

    for (int i = 0; i < cantidadDeUsuarios; i++) {
        usuario = leer(i);
        if (usuario.getId() == id) {
            posicion = i;
        }
    }

    return posicion;
}

int UsuarioArchivo::buscar(std::string nroDocumento) {
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
        if (strcmp(usuario.getNroDocumento(), nroDocumento.c_str()) == 0) {
            posicion = i;
        }
    }

    return posicion;
}

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

/*
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
*/

bool UsuarioArchivo::crear(Usuario reg) {
    FILE* p;

    p = fopen(_nombre.c_str(), "ab");

    if (p == nullptr) {
        mensajeNoSePudoCrearArchivo();
        return false;
    }

    bool escribio = fwrite(&reg, sizeof(Usuario), 1, p);

    fclose(p);

    return escribio;
}

Usuario UsuarioArchivo::leer(int posicion) {
    Usuario reg;
    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        mensajeNoSePudoLeerArchivo();
        return reg;
    }

    fseek(p, sizeof(Usuario) * posicion, SEEK_SET);
    fread(&reg, sizeof(Usuario), 1, p);
    fclose(p);

    return reg;
}

Usuario UsuarioArchivo::leer(Usuario* listadoDeUsuarios, int cantidadDeRegistros) {
    Usuario reg;
    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        mensajeNoSePudoLeerArchivo();
        return reg;
    }

    fread(listadoDeUsuarios, sizeof(Usuario), cantidadDeRegistros, p);
    fclose(p);
}

bool UsuarioArchivo::modificar(Usuario reg, int posicion) {
    FILE* p;

    p = fopen(_nombre.c_str(), "rb+");

    if (p == nullptr) {
        mensajeNoSePudoLeerArchivo();
        return false;
    }

    fseek(p, posicion * sizeof(Usuario), SEEK_SET);

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
        mensajeNoSePudoLeerArchivo();
        return false;
    }

    while (fread(&reg, sizeof (Usuario), 1, p) == 1) {
        cantidadDeUsuarios++;
    }

    fclose(p);

    return cantidadDeUsuarios;
}
