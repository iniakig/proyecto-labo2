#include "ClienteArchivo.h"
#include "Cliente.h"

#include <iostream>
#include <string.h>
#include <string>

#include <../funciones.h>
#include <../mensajes.h>

// Constructores
ClienteArchivo::ClienteArchivo(std::string nombre) {
    setNombre(nombre);
}

ClienteArchivo::ClienteArchivo() {
    setNombre("clientes.dat");
}

// Interfaces
Cliente ClienteArchivo::leer(int posicion) {
    Cliente cliente;

    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        exit(1);
    }

    fseek(p, sizeof(Cliente) * posicion, SEEK_SET);
    fread(&cliente, sizeof(Cliente), 1, p);
    fclose(p);

    return cliente;
}

Cliente ClienteArchivo::leer(Cliente* listaDeClientes, int cantidadDeClientes) {
    Cliente reg;
    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        mensajeNoSePudoLeerArchivo();
        return reg;
    }

    fread(listaDeClientes, sizeof(Cliente), cantidadDeClientes, p);
    fclose(p);
}

int ClienteArchivo::buscar(std::string nroDocumentoIngresado) {
    // Método de búsqueda libre
    // REHACER
    int posicion = -1;
    Cliente cliente;

    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        return posicion;
    }

    int cantidadDeClientes = getCantidadDeClientes();

    for (int i = 0; i < cantidadDeClientes; i++) {
        cliente = leer(i);
        std::string nroDocumento(cliente.getNroDocumento()); // Acá se crea una nueva variable string tomando el nroDocumento del objeto leído.
        if (nroDocumento.length() > 8) { // Si es mayor a 8 significa que no es un DNI, sino un CUIT, entonces extrae el DNI del CUIT.
            nroDocumento = cortarCuit(nroDocumento);
        }

        if (nroDocumentoIngresado.length() > 8) {
            nroDocumentoIngresado = cortarCuit(nroDocumentoIngresado);
        }

        if (strcmp(nroDocumento.c_str(), nroDocumentoIngresado.c_str()) == 0) {
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

    bool escribio = fwrite(&cliente, sizeof(Cliente), 1, p);

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

// Setters
void ClienteArchivo::setNombre(std::string nombre) {
    _nombre = nombre;
}

// Getters
int ClienteArchivo::getCantidadDeClientes() {
    Cliente cliente;
    int cantidadClientes = 0;

    FILE* p;

    p = fopen(_nombre.c_str(), "rb");

    if (p == nullptr) {
        return cantidadClientes;
    }

    while (fread(&cliente, sizeof(Cliente), 1, p) == 1) {
        cantidadClientes++;
    }

    return cantidadClientes;
}
