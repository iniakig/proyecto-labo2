#ifndef PRODUCTOMANAGER_H_INCLUDED
#define PRODUCTOMANAGER_H_INCLUDED

#include "Producto.h"
#include "ProductoArchivo.h"

class ProductoManager{
public:
	void Cargar();
	void Editar();
	void Eliminar();
	void ListarTodos();
	void ListarXId();
	void ListarPorMarca();
	void ListarPorTopePrecio();
	void ListarPorStock();
    void ListarPorProxAgotarse();
    void ListarPorMasVendidos();
    void Listar(Producto producto);
	void HacerCopiaDeSeguridad();
	void RestaurarCopiaDeSeguridad();
	void setPermisos(bool adm, bool sup, bool ven);

private:
    bool _permisos[3]; // Posición 0. Adm | 1. Sup | 2. Ven
	ProductoArchivo _archivo;
	ProductoArchivo _archivoBkp = ProductoArchivo("productos.bkp");
	int GenerarId();
};

#endif // PRODUCTOMANAGER_H_INCLUDED
