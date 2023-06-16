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
        float _montoCompra;
        int _metodoPago;
        char _aliasVendedor[15];
        bool _activo;

    public:
        // CONSTRUCTORES
        Venta();
        Venta(int idPedido, std::string nroDocCliente, const Fecha& fechaCompra, const int vecIdProducto[], const int vecUnidadesxProducto[],float montoCompra, int metodoPago, std::string aliasVendedor, bool activo);

        //GETTERS
        int getIdPedido();
        std::string getNroDocCliente();
        Fecha getFecha();
        const int* getVecIdProducto();
        const int* getVecUnidadesxProducto();
        float getMontoCompra();
        int getMetodoPago();
        std::string getAliasVendedor();
        bool getActivo();

        // SETTERS
        void setIdPedido(int idPedido);
        void setNroDocCliente(std::string nroDocCliente);
        void setFechaCompra(Fecha fechaCompra);
        void setVecIdProducto(const int* vecIdProducto);
        void setVecUnidadesxProducto(const int* vecUnidadesxProducto);
        void setMontoCompra(float montoCompra);
        void setMetodoPago(int metodoPago);
        void setAliasVendedor(std::string aliasVendedor);
        void setActivo(bool activo);
};

#endif // VENTA_H
