#include<iostream>
using namespace std;
#include "Producto.h"

//CONSTRUCTOR POR DEFECTO
Producto::Producto()
{
    _ID = 0;
    _categoria = -1;
    _idMarca = 0;
    strcpy(_modelo, "NULL");
    strcpy(_descripcion, "NULL");
    _precioVenta = 0;
    _stock = 0;
    _activo = false;
}
 // CONSTRUCTOR POR PARAMETROS
Producto::Producto(int ID,int categoria, int idMarca, std::string modelo, std::string descripcion, float precioVenta, int stock, bool activo)
{
    _ID = ID;
    _categoria=categoria;
    _idMarca = idMarca;
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

void Producto::setMarca(int idMarca)
{
    _idMarca = idMarca;
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


int Producto::getIdMarca()
{
    return _idMarca;
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


