#ifndef CLIENTEARCHIVO_H
#define CLIENTEARCHIVO_H

#include "Cliente.h"

#include <string>

class ClienteArchivo
{
    private:
        std::string _nombre;

    public:
        // Constructores
        ClienteArchivo(std::string nombre);
        ClienteArchivo();

        // Interfaces
        Cliente leer(int posicion); // Hecho - Testear
        Cliente leer(Cliente* listaDeClientes, int cantidadDeClientes);
        int buscar(std::string nroDocumentoIngresado);
        int buscar(int tipoDocumento, std::string nroDocumento);
        bool crear(Cliente cliente); // Hecho - Testear
        bool crear(Cliente* listaDeClientes, int cantidadDeClientes);
        bool modificar(Cliente cliente, int posicion); // Hecho - Testear
        void vaciar(); // Hecho - Testear


        // Setters
        void setNombre(std::string nombre); // Hecho

        // Getters
        int getCantidadDeClientes(); // Hecho

};

#endif // CLIENTEARCHIVO_H
