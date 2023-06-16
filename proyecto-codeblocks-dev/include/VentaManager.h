#ifndef VENTAMANAGER_H_INCLUDED
#define VENTAMANAGER_H_INCLUDED

#include "Venta.h"
#include "VentaArchivo.h"
#include "ClienteArchivo.h"
#include "ClienteManager.h"
#include "ProductoArchivo.h"
#include "../funciones.h"

class VentaManager{
public:
	void Cargar();
	void Editar();
	void Eliminar();
    void Listar(Venta venta);
	void ventasPorEmpleado();
	void recaudacionAnual();
	void listarPorMedioDePago();
	void hacerCopiaDeSeguridad();
	void restaurarCopiaDeSeguridad();
	void setPermisos(bool adm, bool sup, bool ven);

private:
    bool _permisos[3]; // Posición 0. Adm | 1. Sup | 2. Ven
	VentaArchivo _archivo;
	VentaArchivo _archivoBkp = VentaArchivo("ventas.bkp");
	int GenerarId();
};


#endif // VENTAMANAGER_H_INCLUDED
