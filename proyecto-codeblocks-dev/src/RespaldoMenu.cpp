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
        std::cout << "0. VOLVER AL MEN� PRINCIPAL" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "OPCI�N SELECCIONADA: ";
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
            std::cout << "La opci�n seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}
