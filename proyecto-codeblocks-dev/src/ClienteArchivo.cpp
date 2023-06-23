#include "ClienteArchivo.h"
#include "Cliente.h"

#include <iostream>
#include <string.h>
#include <string>
#include <../funciones.h>

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

int ClienteArchivo::buscar(std::string nroDocumento) {
    // M�todo de b�squeda libre
    // REHACER
    std::string nroNuevo;
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
        std::string nro(cliente.getNroDocumento()); // Ac� se crea una nueva variable string tomando el nroDocumento del objeto le�do.
        if (nro.length() > 8) { // Si es mayor a 8 significa que no es un DNI, sino un CUIT, entonces extrae el DNI del CUIT.
            nroNuevo = cortarCuit(nro);
        }
        else {
            nroNuevo = nro;
        }
        if (strcmp(nroNuevo.c_str(), nroDocumento.c_str()) == 0) {
            posicion = i;
            return i;
        }
        /*
        // C�digo viejo que serv�a para b�squedas libres, pero no ten�a en cuenta los dos n�meros del comienzo y el del final del CUIT

        if (strstr(cliente.getNroDocumento(), nroDocumento.c_str()) != NULL) {
            posicion = i;
            return i;
        }
        */
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
