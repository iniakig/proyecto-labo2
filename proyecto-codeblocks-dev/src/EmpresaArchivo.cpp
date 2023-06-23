#include "EmpresaArchivo.h"

#include "../mensajes.h"

EmpresaArchivo::EmpresaArchivo()
{
    setNombre("perfilEmpresa.dat");
}

EmpresaArchivo::EmpresaArchivo(std::string nombre) {
    setNombre(nombre.c_str());
}

bool EmpresaArchivo::crear(Empresa empresa) {
    FILE* p;

    p = fopen(_nombre.c_str(), "wb");

    if (p == nullptr) {
        mensajeNoSePudoCrearArchivo();
        return false;
    }

    bool escribio = fwrite(&empresa, sizeof(Empresa), 1, p);

    fclose(p);

    return escribio;
}

Empresa EmpresaArchivo::leer() {
    Empresa empresa;
    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        mensajeNoSePudoLeerArchivo();
        return empresa;
    }

    fread(&empresa, sizeof(Empresa), 1, p);

    fclose(p);

    return empresa;
}

void EmpresaArchivo::setNombre(std::string nombre) {
    _nombre = nombre;
}
