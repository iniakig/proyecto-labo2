#include "RespaldoMenu.h"

#include <../rlutil.h>

void RespaldoMenu::mostrar() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "RESPALDOS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. CREAR RESPALDOS" << std::endl;
        std::cout << "2. RESTAURAR RESPALDOS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "0. VOLVER AL MENÚ PRINCIPAL" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "OPCIÓN SELECCIONADA: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
        case 0:
            break;
        case 1:
            _respaldoManager.mostrarCrearRespaldos();
            break;
        case 2:
            _respaldoManager.mostrarRestaurarRespaldos();
            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}
