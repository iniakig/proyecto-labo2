#include<iostream>
#include "ProductoMenu.h"
#include "../rlutil.h"

void ProductoMenu::mostrar()
{
    int opcion;
    do
    {
        rlutil::cls();
        std::cout << "GESTIÓN DE PRODUCTOS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. AGREGAR PRODUCTO" << std::endl;
        std::cout << "2. MODIFICAR PRODUCTO" << std::endl;
        std::cout << "3. ELIMINAR PRODUCTO" << std::endl;
        std::cout << "4. REACTIVAR PRODUCTO" << std::endl;
        std::cout << "5. LISTAR PRODUCTOS" << std::endl;
        std::cout << "6. RESTAR STOCK" << std::endl;
        std::cout << "7. CARGAR STOCK" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "0. VOLVER AL MENÚ PRINCIPAL" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "OPCIÓN SELECCIONADA: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion)
        {
        case 0:
            break;
        case 1:
            _productoManager.Cargar();
            break;
        case 2:
            _productoManager.Editar();
            break;
        case 3:
            _productoManager.Eliminar();
            break;
        case 4:
            _productoManager.reactivar();
            break;
        case 5:
            _productoManager.listarProductos();
            break;
        case 6:
            _productoManager.RestarStock();
            break;
        case 7:
            _productoManager.CargarStock();
            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}
