#include<iostream>
#include "VentaMenu.h"
#include "../rlutil.h"

void VentaMenu::Mostrar()
{

    int opcion;
    do
    {
        rlutil::cls();
        std::cout << "GESTI�N DE VENTAS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. CARGAR VENTA" << std::endl;
        std::cout << "2. ANULAR VENTA" << std::endl;
        std::cout << "3. REACTIVAR VENTA" << std::endl;
        std::cout << "4. LISTAR VENTAS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "0. VOLVER AL MEN� PRINCIPAL" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "OPCI�N SELECCIONADA: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion)
        {
        case 0:
            break;
        case 1:
            _manager.Cargar();
            break;
        case 2:
            _manager.Anular();
            break;
        case 3:
            _manager.Reactivar();
            break;
        case 4:
            _manager.ListarTodas();
            break;
        default:
            std::cout << "La opci�n seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}

