#include<iostream>
#include "MarcaMenu.h"
#include "../rlutil.h"

void MarcaMenu::mostrar()
{
    int opcion;
    do
    {
        //rlutil::cls();
        std::cout << "GESTI�N DE MARCAS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. AGREGAR MARCA" << std::endl;
        std::cout << "2. MODIFICAR MARCA" << std::endl;
        std::cout << "3. ELIMINAR MARCA" << std::endl;
        std::cout << "4. REACTIVAR MARCA" << std::endl;
        std::cout << "5. LISTAR MARCAS" << std::endl;
        std::cout << "6. BUSCAR MARCA" << std::endl;
        std::cout << "7. REALIZAR COPIA SEGURIDAD" << std::endl;
        std::cout << "8. RESTAURAR COPIA SEGURIDAD" << std::endl;
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
            _marcaManager.cargar();
            break;
        case 2:
            _marcaManager.modificar();
            break;
        case 3:
            _marcaManager.eliminar();
            break;
        case 4:
            _marcaManager.reactivar();
            break;
        case 5:
            _marcaManager.listarTodos();
            break;
        case 6:
            _marcaManager.listarXNombre();
            break;
        case 7:
            _marcaManager.hacerCopiaSeguridad();
            break;
        case 8:
            _marcaManager.restaurarCopiaSeguridad();
            break;

        default:
            std::cout << "La opci�n seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}
