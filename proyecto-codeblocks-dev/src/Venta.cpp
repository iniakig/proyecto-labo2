#include<iostream>
using namespace std;
#include "Venta.h"

//CONSTRUCTOR POR DEFECTO
Venta::Venta()
{
    _idPedido = 0;
    strcpy(_nroDocCliente, "NULL");
    _fechaCompra = Fecha();
    _vecIdProducto[10] = {};
    _vecUnidadesxProducto[10] = {};
    _montoCompra = 0;
    _metodoPago = 0;
    _idVendedor = 0;
    _activo = false;
}

//CONSTRUCTOR POR PARAMETROS

Venta::Venta(int idPedido, std::string nroDocCliente, Fecha fechaCompra, const int vecIdProducto[], const int vecUnidadesxProducto[], int cantidadProductos, float montoCompra, int metodoPago, int idVendedor, bool activo)
{

    _idPedido = idPedido;
    strcpy(_nroDocCliente, nroDocCliente.c_str());
    _fechaCompra = fechaCompra;
    for (int i = 0; i < 10; i++)
    {
        _vecIdProducto[i] = vecIdProducto[i];
        _vecUnidadesxProducto[i] = vecUnidadesxProducto[i];
    }
    _cantidadProductos = cantidadProductos;
    _montoCompra = montoCompra;
    _metodoPago = metodoPago;
    _idVendedor = idVendedor;
    _activo = activo;
}

//SETTERS

void Venta::setIdPedido(int idPedido)
{
    _idPedido = idPedido;
}

void Venta::setNroDocCliente(std::string nroDocCliente)
{
    strcpy(_nroDocCliente, nroDocCliente.c_str());
}

void Venta::setFechaCompra(Fecha fechaCompra)
{
    _fechaCompra = fechaCompra;
}


void Venta::setVecIdProducto(const int* vecIdProducto)
{
    for (int i = 0; i < 10; i++)
    {
        _vecIdProducto[i] = vecIdProducto[i];
    }
}

void Venta::setVecUnidadesxProducto(const int* vecUnidadesxProducto)
{
    for (int i = 0; i < 10; i++)
    {
        _vecUnidadesxProducto[i] = vecUnidadesxProducto[i];
    }
}

void Venta::setCantidadProductos(int cantidad){
    _cantidadProductos = cantidad;
}

void Venta::setMontoCompra(float montoCompra)
{
    _montoCompra = montoCompra;
}

void Venta::setMetodoPago(int metodoPago)
{
    _metodoPago = metodoPago;
}

void Venta::setIdVendedor(int idVendedor)
{
    _idVendedor = idVendedor;
}

void Venta::setActivo(bool activo)
{
    _activo = activo;
}

//GETTERS
int  Venta::getIdPedido()
{
    return _idPedido;
}

std::string Venta::getNroDocCliente()
{
    std::string nroDocCliente;
    nroDocCliente = _nroDocCliente;
    return nroDocCliente;
}

Fecha Venta::getFecha()
{
    return _fechaCompra;
}

const int* Venta::getVecIdProducto()
{
    return _vecIdProducto;
}

const int* Venta::getVecUnidadesxProducto()
{
    return _vecUnidadesxProducto;
}

int Venta::getCantidadProductos()
{
    return _cantidadProductos;
}

float Venta::getMontoCompra()
{
    return _montoCompra;
}

int Venta::getMetodoPago()
{
    return _metodoPago;
}

int Venta::getIdVendedor()
{
    return _idVendedor;
}

bool Venta::getActivo()
{
    return _activo;
}
