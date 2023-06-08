#include "ClienteArchivo.h"
#include "Cliente.h"

#include <iostream>
#include <string.h>

ClienteArchivo::ClienteArchivo(std::string nombre) {
    setNombre(nombre);
}

ClienteArchivo::ClienteArchivo() {
    setNombre("clientes.dat");
}

Cliente ClienteArchivo::leer(int posicion) {
    Cliente cliente;

    FILE* p;

    if (p == nullptr) {
        exit(1);
    }

    fseek(p, sizeof(Cliente) * posicion, SEEK_SET);
    fread(&cliente, sizeof(Cliente), 1, p);
    fclose(p);

    return cliente;
}

int ClienteArchivo::buscar(std::string nroDocumento) {
    // Método de búsqueda libre
    int posicion = -1;
    Cliente cliente;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        std::cout << "No se pudo abrir el archivo";
        return posicion;
    }

    int cantidadDeClientes = getCantidadDeClientes();

    for (int i = 0; i < cantidadDeClientes; i++) {
        leer(i);
        if (strstr(cliente.getNroDocumento(), nroDocumento.c_str()) != NULL) {
            posicion = i;
            return i;
        }
    }

    return posicion;
}

int ClienteArchivo::buscar(int tipoDocumento, std::string nroDocumento) {
    int posicion = -1;
    Cliente cliente;

    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        std::cout << "No se pudo abrir el archivo";
        return posicion;
    }

    int cantidadDeClientes = getCantidadDeClientes();

    for (int i = 0; i < cantidadDeClientes; i++) {
        leer(i);
        if (cliente.getTipoDocumento() == tipoDocumento && strcmp(cliente.getNroDocumento(), nroDocumento.c_str()) == 0) {
            posicion = i;
            return i;
        }
    }

    return posicion;
}

bool ClienteArchivo::crear(Cliente cliente) {
    FILE* p;

    p = fopen(_nombre.c_str(), "ab");

    if (p == nullptr) {
        std::cout << "No se pudo abrir el archivo";
        return false;
    }

    bool escribio = fread(&cliente, sizeof(Cliente), 1, p);

    fclose(p);

    return escribio;
}

bool ClienteArchivo::modificar(Cliente cliente, int posicion) {
    FILE* p;

    p = fopen(_nombre.c_str(), "rb+");

    if (p == nullptr) {
        std::cout << "No se pudo abrir el archivo";
        return false;
    }

    fseek(p, posicion * sizeof(Cliente), SEEK_SET);

    bool escribio = fwrite(&cliente, sizeof(Cliente), 1, p);

    fclose(p);

    return escribio;
}

void ClienteArchivo::vaciar() {
    FILE* p;

    p = fopen(_nombre.c_str(), "wb");

    if (p == nullptr) {
        std::cout << "No se pudo abrir el archivo";
        exit(1);
    }
}

void ClienteArchivo::setNombre(std::string nombre) {
    _nombre = nombre;
}

int ClienteArchivo::getCantidadDeClientes() {
    Cliente cliente;
    int cantidadClientes = 0;

    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        std::cout << "No se pudo abrir el archivo";
        return -1;
    }

    while (fread(&cliente, sizeof(Cliente), 1, p) == 1) {
        cantidadClientes++;
    }

    return cantidadClientes;
}
