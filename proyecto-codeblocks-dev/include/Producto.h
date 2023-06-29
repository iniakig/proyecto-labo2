#ifndef PRODUCTO_H
#define PRODUCTO_H

#include "Marca.h"
#include <string>
#include <cstring>


class Producto
{
public:
    //CONSTRUCTORES
    Producto();
    Producto(int ID, int categoria, int idMarca, std::string modelo, std::string descripcion, float precioVenta, int stock, bool activo);

    //SETTERS
    void setID(int ID);
    void setCategoria (int categoria);
    void setMarca (int idMarca);
    void setModelo(std::string modelo);
    void setDescripcion(std::string descripcion);
    void setPrecio (float precioVenta);
    void setStock (int stock);
    void setActivo (bool activo);

    //GETTERS
    int getID();
    int getCategoria ();
    int getIdMarca ();
    std::string getModelo();
    std::string getDescripcion();
    float getPrecio ();
    int getStock ();
    bool getActivo ();

private:
    int _ID;
    int _categoria;
    int _idMarca;
    char _modelo[15];
    char _descripcion[50];
    float _precioVenta;
    int _stock;
    bool _activo;
};

#endif // PRODUCTO_H
