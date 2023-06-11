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
        int buscar(std::string nroDocumento); // Método de búsqueda libre
        int buscar(int tipoDocumento, std::string nroDocumento);
        bool crear(Cliente cliente); // Hecho - Testear
        bool modificar(Cliente cliente, int posicion); // Hecho - Testear
        void vaciar(); // Hecho - Testear


        // Setters
        void setNombre(std::string nombre); // Hecho

        // Getters
        int getCantidadDeClientes(); // Hecho

};

#endif // CLIENTEARCHIVO_H
