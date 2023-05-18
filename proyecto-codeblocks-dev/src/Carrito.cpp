#include "Carrito.h"

Carrito::Carrito()
{
    //ctor
}

void Carrito::setCantProductos(int cantidad){
    _cantProductos = cantidad;
}

int Carrito::getCantProductos(){
    return _cantProductos;
}

// GETTER Y SETTER CLIENTE (FALTA CLASE CLIENTE)
/*void Carrito::setCliente(Cliente cliente){
    _cliente = cliente;
}

Cliente Carrito::getCliente(){
    return _cliente;
}


