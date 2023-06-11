#include "ClienteMenu.h"
#include "../rlutil.h"

void ClienteMenu::mostrar() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "GESTIÓN DE CLIENTES" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. AGREGAR CLIENTE" << std::endl;
        std::cout << "2. MODIFICAR CLIENTE" << std::endl;
        std::cout << "3. DAR DE BAJA CLIENTE" << std::endl;
        std::cout << "4. REACTIVAR CLIENTE" << std::endl;
        std::cout << "5. LISTAR CLIENTES" << std::endl;
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
            _clientemanager.cargar();
            break;
        case 2:
            _clientemanager.modificar();
            break;
        case 3:
            _clientemanager.darDeBaja();
            break;
        case 4:
            _clientemanager.reactivar();
            break;
        case 5:
            _clientemanager.listarClientes();
            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}
