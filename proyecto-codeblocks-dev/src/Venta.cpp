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
    strcpy(_aliasVendedor, "NULL");
    _activo = false;
}

//CONSTRUCTOR POR PARAMETROS

Venta::Venta(int idPedido, std::string nroDocCliente, const Fecha& fechaCompra, const int vecIdProducto[], const int vecUnidadesxProducto[],float montoCompra, int metodoPago, std::string aliasVendedor, bool activo)
{

    _idPedido = idPedido;
    strcpy(_nroDocCliente, nroDocCliente.c_str());
    _fechaCompra = fechaCompra;
    for (int i = 0; i < 10; i++)
    {
        _vecIdProducto[i] = vecIdProducto[i];
        _vecUnidadesxProducto[i] = vecUnidadesxProducto[i];
    }
    _montoCompra = montoCompra;
    _metodoPago = metodoPago;
    strcpy(_aliasVendedor, aliasVendedor.c_str());
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

void Venta::setMontoCompra(float montoCompra)
{
    _montoCompra = montoCompra;
}

void Venta::setMetodoPago(int metodoPago)
{
    _metodoPago = metodoPago;
}

void Venta::setAliasVendedor(std::string aliasVendedor)
{
    strcpy(_aliasVendedor, aliasVendedor.c_str());
}

void Venta::setActivo(bool activo){
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
float Venta::getMontoCompra()
{
    return _montoCompra;
}
int Venta::getMetodoPago()
{
    return _metodoPago;
}

std::string Venta::getAliasVendedor()
{
    std::string aliasVendedor;
    aliasVendedor = _aliasVendedor;
    return aliasVendedor;
}

bool Venta::getActivo(){
    return _activo;
}
