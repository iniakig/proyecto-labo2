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
        std::cout << " 1. AGREGAR PRODUCTO" << std::endl;
        std::cout << " 2. MODIFICAR PRODUCTO" << std::endl;
        std::cout << " 3. ELIMINAR PRODUCTO" << std::endl;
        std::cout << " 4. REACTIVAR PRODUCTO" << std::endl;
        std::cout << " 5. LISTAR PRODUCTOS" << std::endl;
        std::cout << " 6. BUSCAR PRODUCTO POR ID" << std::endl;
        std::cout << " 7. LISTAR POR MARCA" << std::endl;
        std::cout << " 8. LISTAR POR TOPE DE PRECIO" << std::endl;
        std::cout << " 9. LISTAR POR STOCK" << std::endl;
        std::cout << " 10. REALIZAR COPIA SEGURIDAD" << std::endl;
        std::cout << "11. RESTAURAR COPIA SEGURIDAD" << std::endl;
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
            _productoManager.ListarTodos();
            break;
        case 6:
            _productoManager.ListarXId();
            break;
        case 7:
            _productoManager.ListarPorMarca();
            break;
        case 8:
            _productoManager.ListarPorTopePrecio();
            break;
        case 9:
            _productoManager.ListarPorStock();
            break;
        case 10:
            _productoManager.HacerCopiaDeSeguridad();
            break;
        case 11:
            _productoManager.RestaurarCopiaDeSeguridad();
            break;

        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}
