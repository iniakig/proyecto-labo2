#include "InformesMenu.h"

#include "../rlutil.h"

void InformesMenu::mostrar() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "INFORMES" << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
        std::cout << "1. TOTAL Y CANTIDAD DE VENTAS POR EMPLEADO DEL MES ACTUAL" << std::endl;
        std::cout << "2. RECAUDACI�N ANUAL" << std::endl;
        std::cout << "3. PRODUCTOS PR�XIMOS A AGOTARSE" << std::endl;
        std::cout << "4. LOS 5 PRODUCTOS M�S VENDIDOS DEL MES ACTUAL" << std::endl;
        std::cout << "5. VENDEDOR CON M�S VENTAS CONCRETADAS POR IMPORTE" << std::endl;
        std::cout << "6. RESUMEN DE VENTAS DIARIAS" << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
        std::cout << "0. VOLVER AL MEN� PRINCIPAL" << std::endl;
        std::cout << "-----------------------------------------------------------" << std::endl;
        std::cout << "OPCI�N SELECCIONADA: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
            case 0:
                break;
            case 1:
               _ventaManager.ventasTotalesPorVendedor();
                break;
            case 2:
                _ventaManager.recaudacionAnual();
                break;
            case 3:
                _productoManager.productosPorAgotarse();
                break;
            case 4:
                _productoManager.cincoProductosMasVendidos();
                break;
            case 5:
                _ventaManager.vendedorConMasVentasConcretadas();
            case 6:
                break;
            default:
                break;
        }
    }

    while (opcion != 0);
}
