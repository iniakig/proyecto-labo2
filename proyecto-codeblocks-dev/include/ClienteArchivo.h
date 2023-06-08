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
        Cliente leer(int posicion);
        int buscar(std::string nroDocumento); // Método de búsqueda libre
        int buscar(int tipoDocumento, std::string nroDocumento);
        bool crear(Cliente cliente);
        bool modificar(Cliente cliente, int posicion);
        void vaciar();


        // Setters
        void setNombre(std::string nombre);

        // Getters
        int getCantidadDeClientes();

};

#endif // CLIENTEARCHIVO_H
