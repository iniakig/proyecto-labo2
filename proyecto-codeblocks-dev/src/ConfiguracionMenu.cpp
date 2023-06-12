#include "ConfiguracionMenu.h"

#include "../rlutil.h"

void ConfiguracionMenu::mostrar() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "MEN� DE CONFIGURACI�N" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "1. GESTI�N DE USUARIOS" << std::endl;
        std::cout << "2. PERFIL EMPRESA" << std::endl;
        std::cout << "3. RESPALDOS" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "0. VOLVER AL MEN� PRINCIPAL" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "OPCI�N SELECCIONADA: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
            case 0:
                break;
            case 1:
                _usuarioMenu.mostrar();
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                break;
        }
    }

    while (opcion != 0);
}
