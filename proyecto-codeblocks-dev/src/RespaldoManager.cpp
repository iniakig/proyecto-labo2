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
            _usuarioManager.hacerCopiaDeSeguridad();
            break;
        case 2:
            _clienteManager.hacerCopiaDeSeguridad();
            break;
        case 3:
            _marcaManager.hacerCopiaSeguridad();
            break;
        case 4:
            _productoManager.HacerCopiaDeSeguridad();
            break;
        case 5:
            _ventaManager.hacerCopiaDeSeguridad();
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
            _usuarioManager.restaurarCopiaDeSeguridad();
            break;
        case 2:
            _clienteManager.restaurarCopiaDeSeguridad();
            break;
        case 3:
            _marcaManager.restaurarCopiaSeguridad();
            break;
        case 4:
            _productoManager.RestaurarCopiaDeSeguridad();
            break;
        case 5:
            _ventaManager.restaurarCopiaDeSeguridad();
            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}
