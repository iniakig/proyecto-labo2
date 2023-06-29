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
    void ListarVentas();
	void listarPorMedioDePago();
	void hacerCopiaDeSeguridad();
	void restaurarCopiaDeSeguridad();
	void setPermisos(bool adm = false, bool sup = false, bool ven = false);

	//INFORMES
	void ventasPorEmpleado();
	void recaudacionAnual();
	void vendedorConMasVentasConcretadas();
    void ventasTotalesPorVendedor();

private:
    bool _permisos[3]; // Posición 0. Adm | 1. Sup | 2. Ven
	VentaArchivo _archivo;
	VentaArchivo _archivoBkp = VentaArchivo("ventas.bkp");
	int GenerarId();
	bool restaurarStock(const int* vecProductos, const int* vecUnidades, int cantidadProductos);
	int cargarProductos(int* vecProductos, int* vecUnidades);
	std::string validarCliente();
	std::string metodoPagoAString(int metodoPago);
    void Listar(Venta venta, int tipoListado);
    void ListarTodasDetalle();
    void ListarTodasResumen();
    void ListarVentasAnuladas();
    void generarComprobante(Venta venta);
};


#endif // VENTAMANAGER_H_INCLUDED
