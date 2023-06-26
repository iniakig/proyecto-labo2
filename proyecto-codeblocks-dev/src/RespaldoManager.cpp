#include "RespaldoManager.h"

#include "../rlutil.h"

void RespaldoManager::mostrarCrearRespaldos() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "CREAR RESPALDOS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. USUARIOS" << std::endl;
        std::cout << "2. CLIENTES" << std::endl;
        std::cout << "3. MARCAS" << std::endl;
        std::cout << "4. PRODUCTOS" << std::endl;
        std::cout << "5. VENTAS" << std::endl;
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

            break;
        case 2:

            break;
        case 3:
            _marcaManager.hacerCopiaSeguridad();
            break;
        case 4:

            break;
        case 5:

            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}

void RespaldoManager::mostrarRestaurarRespaldos() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "RESTAURAR RESPALDOS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. USUARIOS" << std::endl;
        std::cout << "2. CLIENTES" << std::endl;
        std::cout << "3. MARCAS" << std::endl;
        std::cout << "4. PRODUCTOS" << std::endl;
        std::cout << "5. VENTAS" << std::endl;
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

            break;
        case 2:

            break;
        case 3:
            _marcaManager.restaurarCopiaSeguridad();
            break;
        case 4:

            break;
        case 5:

            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}
