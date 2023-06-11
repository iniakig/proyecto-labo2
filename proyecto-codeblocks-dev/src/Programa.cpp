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
        std::cout << "MENÚ PRINCIPAL" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "1. GESTIÓN DE VENTAS" << std::endl;
        std::cout << "2. GESTIÓN DE PRODUCTOS" << std::endl;
        std::cout << "3. GESTIÓN DE MARCAS" << std::endl;
        std::cout << "4. GESTIÓN DE CLIENTES" << std::endl;
        std::cout << "5. INFORMES" << std::endl;
        std::cout << "6. CONFIGURACIÓN" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "0. SALIR DEL PROGRAMA" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "OPCIÓN SELECCIONADA: "

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



