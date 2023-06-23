#include "EmpresaMenu.h"

#include "../rlutil.h"

void EmpresaMenu::mostrar() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "PERFIL EMPRESA" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. CARGAR PERFIL EMPRESA" << std::endl;
        std::cout << "2. LISTAR PERFIL EMPRESA" << std::endl;
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
            _empresaManager.cargar();
            break;
        case 2:
            _empresaManager.listar();
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}
