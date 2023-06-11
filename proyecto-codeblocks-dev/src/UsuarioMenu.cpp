#include "UsuarioMenu.h"
#include "../rlutil.h"

void UsuarioMenu::mostrar() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "GESTIÓN DE USUARIOS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. AGREGAR USUARIO" << std::endl;
        std::cout << "2. MODIFICAR USUARIO" << std::endl;
        std::cout << "3. DAR DE BAJA USUARIO" << std::endl;
        std::cout << "4. REACTIVAR USUARIO" << std::endl;
        std::cout << "5. LISTAR USUARIOS" << std::endl;
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
            _usuarioManager.cargar();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            _usuarioManager.listarUsuarios();
            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}
