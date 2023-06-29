#ifndef PRODUCTOMANAGER_H_INCLUDED
#define PRODUCTOMANAGER_H_INCLUDED

#include <iostream>
#include <iomanip>
#include "string.h"

#include "../funciones.h"
#include <../rlutil.h>
#include "../validaciones.h"
#include "../mensajes.h"

#include "ProductoArchivo.h"
#include "VentaManager.h"
#include "MarcaManager.h"
#include "Producto.h"


class ProductoManager{
public:
	void Cargar();
	void Editar();
	void Eliminar();
	void reactivar();
    void Listar(Producto producto, int tipoListado);
    void CargarStock();
    bool RestaurarStock(int id, int unidades);
    void RestarStock();
    bool RestarStock(int id, int unidades);
	void HacerCopiaDeSeguridad();
	void RestaurarCopiaDeSeguridad();
	void setPermisos(bool adm, bool sup, bool ven);
    void listarProductos();
    void buscarProductos();
    void listarActivos();
    std::string getCategoriaDescripcion(int categoria);


    void ordenarPorNombreDeMarca(Producto *listaDeProductos, int cantidadDeRegistros);

    // Informes
    void productosPorAgotarse();
    void cincoProductosMasVendidos();

private:
	void ListarTodos();
	void ListarXId();
	void ListarPorMarca();
	void ListarPorTopePrecio();
	void ListarPorStock();
    void ListarPorProxAgotarse();
    void ListarPorMasVendidos();
    bool _permisos[3]; // Posición 0. Adm | 1. Sup | 2. Ven
	ProductoArchivo _archivo;
	ProductoArchivo _archivoBkp = ProductoArchivo("productos.bkp");
	int GenerarId();
};


#endif // PRODUCTOMANAGER_H_INCLUDED
