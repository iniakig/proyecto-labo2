#ifndef VENTA_H
#define VENTA_H

#include "Fecha.h"
#include "Producto.h"
#include "Cliente.h"
#include "UsuarioActivo.h"

#include <string>
#include <cstring>

class Venta
{
   private:
        int _idPedido;
        char _nroDocCliente[12];
        Fecha _fechaCompra;
        int _vecIdProducto[10];
        int _vecUnidadesxProducto[10];
        int _cantidadProductos;
        float _montoCompra;
        int _metodoPago;
        int _idVendedor;
        bool _activo;

    public:
        // CONSTRUCTORES
        Venta();
        Venta(int idPedido, std::string nroDocCliente, Fecha fechaCompra, const int vecIdProducto[], const int vecUnidadesxProducto[], int cantidadProductos, float montoCompra, int metodoPago, int idVendedor, bool activo);

        //GETTERS
        int getIdPedido();
        std::string getNroDocCliente();
        Fecha getFecha();
        const int* getVecIdProducto();
        const int* getVecUnidadesxProducto();
        int getCantidadProductos();
        float getMontoCompra();
        int getMetodoPago();
        int getIdVendedor();
        bool getActivo();

        // SETTERS
        void setIdPedido(int idPedido);
        void setNroDocCliente(std::string nroDocCliente);
        void setFechaCompra(Fecha fechaCompra);
        void setVecIdProducto(const int* vecIdProducto);
        void setVecUnidadesxProducto(const int* vecUnidadesxProducto);
        void setCantidadProductos(int cantidad);
        void setMontoCompra(float montoCompra);
        void setMetodoPago(int metodoPago);
        void setIdVendedor(int idVendedor);
        void setActivo(bool activo);
};

#endif // VENTA_H
