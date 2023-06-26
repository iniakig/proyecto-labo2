#ifndef VENTAMANAGER_H_INCLUDED
#define VENTAMANAGER_H_INCLUDED

#include "VentaArchivo.h"
#include "ClienteManager.h"
#include "ProductoManager.h"
#include "MarcaArchivo.h"
#include "UsuarioArchivo.h"

#include "../funciones.h"
#include <../rlutil.h>

class VentaManager{
public:
	void Cargar();
	void Anular();
    void Reactivar();
    void Listar(Venta venta);
    void ListarTodas();
    void generarComprobante(Venta venta);
	void ventasPorEmpleado();
	void recaudacionAnual();
	void listarPorMedioDePago();
	void hacerCopiaDeSeguridad();
	void restaurarCopiaDeSeguridad();
	void setPermisos(bool adm, bool sup, bool ven);

private:
    bool _permisos[3]; // Posici�n 0. Adm | 1. Sup | 2. Ven
	VentaArchivo _archivo;
	VentaArchivo _archivoBkp = VentaArchivo("ventas.bkp");
	int GenerarId();
	bool restaurarStock(const int* vecProductos, const int* vecUnidades, int cantidadProductos);
	int cargarProductos(int* vecProductos, int* vecUnidades);
	std::string validarCliente();
	std::string metodoPagoAString(int metodoPago);
};


#endif // VENTAMANAGER_H_INCLUDED
