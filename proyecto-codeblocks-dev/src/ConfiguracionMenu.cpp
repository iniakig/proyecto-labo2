#include "ConfiguracionMenu.h"

#include "../rlutil.h"

void ConfiguracionMenu::mostrar() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "MENÚ DE CONFIGURACIÓN" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "1. GESTIÓN DE USUARIOS" << std::endl;
        std::cout << "2. PERFIL EMPRESA" << std::endl;
        std::cout << "3. RESPALDOS" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "0. VOLVER AL MENÚ PRINCIPAL" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "OPCIÓN SELECCIONADA: ";
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
