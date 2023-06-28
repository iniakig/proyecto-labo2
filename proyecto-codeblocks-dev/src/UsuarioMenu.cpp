#include "UsuarioMenu.h"
#include "../rlutil.h"

void UsuarioMenu::mostrar() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "GESTI�N DE USUARIOS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. AGREGAR USUARIO" << std::endl;
        std::cout << "2. MODIFICAR USUARIO" << std::endl;
        std::cout << "3. DAR DE BAJA USUARIO" << std::endl;
        std::cout << "4. REACTIVAR USUARIO" << std::endl;
        std::cout << "5. LISTAR USUARIOS" << std::endl;
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
            rlutil::cls(); // Solo en este caso porque se reutiliza la pantalla en el m�todo de registro en Programa
            _usuarioManager.cargar();
            break;
        case 2:
            _usuarioManager.modificar();
            break;
        case 3:
            _usuarioManager.darDeBaja();
            break;
        case 4:
            _usuarioManager.reactivar();
            break;
        case 5:
            _usuarioManager.listarUsuarios();
            break;
        default:
            std::cout << "La opci�n seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}
