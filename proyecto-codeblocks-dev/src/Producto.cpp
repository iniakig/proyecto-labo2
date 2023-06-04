#include<iostream>
using namespace std;
#include "Producto.h"

//CONSTRUCTOR POR DEFECTO
Producto::Producto()
{
    _ID = 0;
    _categoria = -1;
    _marca = Marca();
    strcpy(_modelo, "NULL");
    strcpy(_descripcion, "NULL");
    _precioVenta = 0;
    _stock = 0;
    _activo = false;
}

Producto::Producto(int ID, Marca marca, std::string modelo, std::string descripcion, float precioVenta, int stock, bool activo)
{
    _ID = ID;
    _marca = marca;
    strcpy(_modelo, modelo.c_str());
    strcpy(_descripcion, descripcion.c_str());
    _precioVenta = precioVenta;
    _stock = stock;
    activo = true;
}

//SETTERS

void Producto::setID(int ID)
{
    _ID = ID;
}

void Producto::setCategoria(int categoria)
{
    _categoria = categoria;
}

void Producto::setMarca(Marca marca)
{
    _marca = marca;
}

void Producto::setModelo(std::string modelo)
{
    strcpy(_modelo, modelo.c_str());
}

void Producto::setDescripcion(std::string descripcion)
{
    strcpy(_descripcion, descripcion.c_str());
}

void Producto::setPrecio(float precioVenta)
{
    _precioVenta = precioVenta;
}

void Producto::setStock(int stock)
{
    _stock = stock;
}

void Producto::setActivo(bool activo)
{
    _activo = activo;
}

//GETTERS
int Producto::getID()
{
    return _ID;
}

int Producto::getCategoria()
{
    return _categoria;
}


Marca Producto::getMarca()
{
    return _marca;
}


std::string Producto::getModelo()
{
    std::string modelo;
    modelo = _modelo;
    return modelo;
}

std::string Producto::getDescripcion()
{
    std::string descripcion;
    descripcion = _descripcion;
    return descripcion;
}

float Producto::getPrecio()
{
    return _precioVenta;
}

int Producto::getStock()
{
    return _stock;
}

bool Producto::getActivo()
{
    return _activo;
}


