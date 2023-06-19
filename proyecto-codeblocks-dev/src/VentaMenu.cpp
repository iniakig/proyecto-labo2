#include<iostream>
#include "VentaMenu.h"
#include "../rlutil.h"

void VentaMenu::Mostrar()
{
    int opcion;
    do
    {
        rlutil::cls();
        std::cout << "GESTIÓN DE VENTAS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << " 1. CARGAR VENTA" << std::endl;
        std::cout << " 2. EDITAR VENTA" << std::endl;
        std::cout << " 3. ELIMINAR VENTA" << std::endl;
        std::cout << " 4. REACTIVAR VENTA" << std::endl;
        std::cout << " 5. LISTAR VENTAS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << " 0. VOLVER AL MENÚ PRINCIPAL" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "OPCIÓN SELECCIONADA: ";
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
                std::cout<<"ACA SE EDITARAN LAS VENTAS"<<std::endl;
            break;
        case 3:
                _manager.Eliminar();
            break;
        case 4:
                _manager.Reactivar();
            break;
        case 5:
                std::cout<<"ACA SE LISTARAN LAS VENTAS"<<std::endl;
            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}

