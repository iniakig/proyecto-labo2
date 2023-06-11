#include "Programa.h"
#include "../rlutil.h"
#include "ClienteManager.h"

// Constructores
Programa::Programa(bool estado) {
    setEstado(estado);
}

// Interfaces

void login() {
    ;
}

void ejecutar() {
    int opcion = -1;

    do {
        std::cout << "MEN� PRINCIPAL" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "1. GESTI�N DE VENTAS" << std::endl;
        std::cout << "2. GESTI�N DE PRODUCTOS" << std::endl;
        std::cout << "3. GESTI�N DE MARCAS" << std::endl;
        std::cout << "4. GESTI�N DE CLIENTES" << std::endl;
        std::cout << "5. INFORMES" << std::endl;
        std::cout << "6. CONFIGURACI�N" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "0. SALIR DEL PROGRAMA" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "OPCI�N SELECCIONADA: "

        switch(opcion) {
        case 0:
            std::cout << std::endl;
            mensajeSalidaDelPrograma();
            rlutil::anykey();
        }
    }

    while (opcion != 0);


}


// Setters
void Programa::setEstado(bool estado) {
    _estado = estado;
}

// Getters
bool Programa::getEstado() {
    return _estado;
}



