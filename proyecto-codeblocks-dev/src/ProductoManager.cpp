#include "ProductoManager.h"
#include "../funciones.h"
#include "string.h"
#include <iostream>
#include <iomanip>
#include <../rlutil.h>
using namespace std;
#include "Marca.h"
#include "MarcaManager.h"
#include "Producto.h"

int ProductoManager::GenerarId()
{



    return _archivo.getCantidadDeRegistros()+1;
}
void ProductoManager::Listar(Producto producto)
{

    std::cout<<"-----------------------------------------------------"<<std::endl;
    std::cout<<"ID: "<<producto.getID()<<std::endl;
    std::cout<<"CATEGORIA: "<<producto.getCategoria()<<std::endl;
    std::cout<<"ID MARCA: "<<producto.getIdMarca()<<std::endl;
    std::cout<<"MODELO: "<<producto.getModelo()<<std::endl;
    std::cout<<"DESCRIPCION: "<<producto.getDescripcion()<<std::endl;
    std::cout<<"PRECIO: "<<producto.getPrecio()<<std::endl;
    std::cout<<"STOCK: "<<producto.getStock()<<std::endl;

}
void ProductoManager::ListarTodos()
{

    int cantidadRegistros = _archivo.getCantidadDeRegistros ();

    for (int i = 0; i<cantidadRegistros; i++)
    {
        Producto reg = _archivo.leer(i);
        if (reg.getActivo()==true)
        {
            Listar(reg);
            cout << endl;
        }
    }
}
void ProductoManager::ListarXId()
{

    int id;

    cout << "Ingrese el ID: ";
    cin >> id;

    int posicion = _archivo.buscar(id);
    if (posicion >= 0)
    {
        Producto producto = _archivo.leer(posicion);
        if(producto.getActivo()==true)
        {
            Listar(producto);

        }
    }
    else
    {
        cout << "No existe el registro con ID: " << id << endl;
    }
}
void ProductoManager::ListarPorMarca()
{

    std::string nombre;
    int idMarca;
    MarcaArchivo archivoMarca;
    cout << "Ingrese nombre de la marca: ";
    std::cin>>nombre;

    int posicion = archivoMarca.buscar(nombre);
    if (posicion >= 0)
    {
        Marca marca = archivoMarca.leer(posicion);
        idMarca=marca.getID();
    }
    else
    {
        cout << "MARCA NO EXISTENTE "<< endl;
    }
    Producto producto;
    ProductoArchivo archivoProducto;
    int cantRegProd=archivoProducto.getCantidadDeRegistros();

    for(int i=0; i<cantRegProd; i++)
    {
        producto=archivoProducto.leer(i);
        if(producto.getIdMarca()==idMarca && producto.getActivo()==true)
        {
            Listar(producto);
        }

    }
}

void ProductoManager::ListarPorTopePrecio()
{
    float topePrecio;
    std::cout<<"INGRESE TOPE DE PRECIO "<<std::endl;
    std::cin>>topePrecio;

    Producto producto;
    ProductoArchivo archivoProducto;
    int cantProductos=archivoProducto.getCantidadDeRegistros();
    Producto *ProductosOrdenadosPorPrecio;
    ProductosOrdenadosPorPrecio= new Producto[cantProductos];
    if(ProductosOrdenadosPorPrecio==nullptr)
    {
        return;
    }

    for(int a=0; a<cantProductos; a++)
    {
        ProductosOrdenadosPorPrecio[a]=archivoProducto.leer(a);
    }
    for(int e=1; e<cantProductos; e++)
    {
        for(int i=0; i<cantProductos-e; i++)
        {
            if(ProductosOrdenadosPorPrecio[i].getPrecio()>ProductosOrdenadosPorPrecio[i+1].getPrecio())
            {
                producto=ProductosOrdenadosPorPrecio[i];
                ProductosOrdenadosPorPrecio[i]=ProductosOrdenadosPorPrecio[i+1];
                ProductosOrdenadosPorPrecio[i+1]=producto;
            }
        }
    }
    for(int a=0; a<cantProductos; a++)
    {
        producto=ProductosOrdenadosPorPrecio[a];
        if(producto.getPrecio()<=topePrecio && producto.getActivo()==true)
        {
            Listar(producto);
        }
    }

}

void ProductoManager::HacerCopiaDeSeguridad()
{


    int cantidadRegs = _archivo.getCantidadDeRegistros();

    Producto *vec = new Producto[cantidadRegs];

    if (vec == nullptr)
    {
        cout << "ERROR AL REALIZAR LA COPIA DE SEGURIDAD" << endl;
        return;
    }

    _archivo.leer(vec, cantidadRegs);
    _archivoBkp.vaciar();

    if(_archivoBkp.guardar(vec, cantidadRegs))
    {
        cout << "COPIA DE SEGURIDAD REALIZADA CON EXITO" << endl;
    }
    else
    {
        cout << "ERROR AL REALIZAR LA COPIA DE SEGURIDAD" << endl;
    }

    delete []vec;
}
void ProductoManager::RestaurarCopiaDeSeguridad()
{


    int cantidadRegs = _archivoBkp.getCantidadDeRegistros();

    Producto *vec = new Producto[cantidadRegs];
    if (vec == nullptr)
    {
        cout << "ERROR AL RESTAURAR LA COPIA DE SEGURIDAD" << endl;
        return;
    }

    _archivoBkp.leer(vec, cantidadRegs);
    _archivo.vaciar();

    if(_archivo.guardar(vec, cantidadRegs))
    {

        cout << "COPIA DE SEGURIDAD RESTAURADA CON EXITO" << endl;
    }
    else
    {
        cout << "ERROR AL REALIZAR LA COPIA DE SEGURIDAD" << endl;
    }

    delete []vec;
}
void ProductoManager::ListarPorStock()
{



    Producto producto;
    ProductoArchivo archivoProducto;
    int cantProductos=archivoProducto.getCantidadDeRegistros();
    Producto *ProductosOrdenadosStock;
    ProductosOrdenadosStock= new Producto[cantProductos];
    if(ProductosOrdenadosStock==nullptr)
    {
        return;
    }

    for(int a=0; a<cantProductos; a++)
    {
        ProductosOrdenadosStock[a]=archivoProducto.leer(a);
    }
    for(int e=1; e<cantProductos; e++)
    {
        for(int i=0; i<cantProductos-e; i++)
        {
            if(ProductosOrdenadosStock[i].getStock()<ProductosOrdenadosStock[i+1].getStock())
            {
                producto=ProductosOrdenadosStock[i];
                ProductosOrdenadosStock[i]=ProductosOrdenadosStock[i+1];
                ProductosOrdenadosStock[i+1]=producto;
            }
        }
    }
    for(int a=0; a<cantProductos; a++)
    {
        producto=ProductosOrdenadosStock[a];
        if(producto.getActivo()==true)
        {

            Listar(producto);
        }
    }
    delete []ProductosOrdenadosStock;
}
void ProductoManager::Cargar()
{

    int ID;
    int categoria;
    int  idMarca;
    std::string modelo;
    std::string descripcion;
    float precioVenta;
    int stock;
    bool activo=true;
    std::string nombreMarca;
    MarcaManager managerMarca;

    ID=GenerarId();
    std::cout<<"INGRESE CATEGORIA DEL PRODUCTO"<<std::endl;
    std::cin>>categoria;
    cout<<categoria;
    std::cout<<"INGRESE NOMBRE DE LA MARCA DEL PRODUCTO"<<std::endl;
    do
    {
        nombreMarca=ingresoDeMarcaConValidacion();
        idMarca=managerMarca.cargarDesdeProducto(nombreMarca);
    }
    while(idMarca<=0);
    std::cout<<"INGRESE MODELO DEL PRODUCTO"<<std::endl;// Convertir a mayuscula pendiente
    std::cin.ignore();
    getline(std::cin, modelo);
    std::cout<<"INGRESE DESCRIPCION DEL PRODUCTO"<<std::endl;// Convertir a mayuscula pendiente
    std::cin.ignore();
    getline(cin, descripcion);
    std::cout<<"INGRESE PRECIO DE VENTA"<<std::endl;
    std::cin>>precioVenta;
    std::cout<<"INGRESE STOCK"<<std::endl;
    std::cin>>stock;

    Producto reg(ID, categoria, idMarca,modelo, descripcion, precioVenta, stock, activo);
    Listar(reg);
    cout<<"CARGO EL SIGUIENTE PRODUCTO: "<<endl;
    Listar(reg);
    cout<<"GUARDAR? 1--SI // 2--NO: ";
    int opc = ingresoOpcSimpleConValidacion();
    if(opc == 1)
    {
        if(_archivo.guardar(reg))
        {
            cout<<"PRODUCTO AGREGADO CORRECTAMENTE"<<endl;
        }
        else
        {
            cout<<"ERROR AL AGREGAR EL PRODUCTO, INTENTELO NUEVAMENTE"<<endl;
        }
    }

}
void ProductoManager::Editar()
{
    Producto producto;
    int id, posicion;

    std::cout << "INGRESE ID DE PRODUCTO A MODIFICAR" << std::endl;
    std::cin>>id;
    posicion=_archivo.buscar(id);
    if(posicion<0)
    {
        std::cout<<"EL ID NO EXISTE"<<std::endl;
    }
    else
    {
        producto=_archivo.leer(posicion);
        int opcion;
        //DECLARACION VARIABLES A UTILIZAR EN SWITCH
        MarcaManager managerMarca;
        int categoria;
        std::string nombreMarca;
        std::string descripcion;
        std::string modelo;
        float precioVenta;
        int stock;
        bool edito = 0;

        do
        {
            rlutil::cls();
            std::cout << "ELIJA EL CAMPO QUE DESEA MODIFICAR" << std::endl;
            std::cout << "---------------------------------------------------" << std::endl;
            std::cout << "1. CATEGORIA" << std::endl;
            std::cout << "2. NOMBRE DE MARCA" << std::endl;
            std::cout << "3. MODELO" << std::endl;
            std::cout << "4. DESCRIPCION" << std::endl;
            std::cout << "5. PRECIO DE VENTA" << std::endl;
            std::cout << "6. STOCK" << std::endl;
            std::cout << "---------------------------------------------------" << std::endl;
            std::cout << "0. VOLVER AL MENÚ DE GESTIÓN DE USUARIOS" << std::endl;
            std::cout << "---------------------------------------------------" << std::endl;
            std::cout << "OPCIÓN SELECCIONADA: ";
            std::cin >> opcion;
            std::cin.ignore();

            switch(opcion)
            {
            case 0:
                break;
            case 1:
                std::cout <<"INGRESE CATEGORIA: "<< std::endl;
                std::cin>>categoria;
                producto.setCategoria(categoria);
                edito = 1;
                break;
            case 2:
                do
                {
                    std::cout <<"INGRESE MARCA: "<< std::endl;
                    nombreMarca=ingresoDeMarcaConValidacion();
                    producto.setMarca(managerMarca.cargarDesdeProducto(nombreMarca));
                }
                while(producto.getIdMarca()<=0);
                edito = 1;
                break;
            case 3:
                std::cout <<"INGRESE MODELO: "<< std::endl;
                getline(cin, modelo);
                producto.setModelo(modelo);
                edito = 1;
                break;
            case 4:
                std::cout <<"INGRESE DESCRIPCION: "<< std::endl;
                getline(cin, descripcion);
                producto.setDescripcion(descripcion);
                edito = 1;
                break;
            case 5:
                std::cout <<"INGRESE PRECIO DE VENTA: "<< std::endl;
                cin>>precioVenta;
                producto.setPrecio(precioVenta);
                edito = 1;
                break;
            case 6:
                std::cout <<"INGRESE STOCK: "<< std::endl;
                cin>>stock;
                producto.setStock(stock);
                edito = 1;
                break;
            default:
                std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
                break;
            }
        }
        while(opcion != 0);
        if(edito)
        {
            cout<<"MODIFICO EL SIGUIENTE PRODUCTO: "<<endl;
            Listar(producto);
            cout<<"GUARDAR CAMBIOS? 1--SI // 2--NO: ";
            int opc = ingresoOpcSimpleConValidacion();
            if(opc == 1)
            {
                if(_archivo.guardar(producto, posicion))
                {
                    cout<<"PRODUCTO MODIFICADO CORRECTAMENTE"<<endl;
                }
                else
                {
                    cout<<"ERROR AL MODIFICAR EL PRODUCTO, INTENTELO NUEVAMENTE"<<endl;
                }
            }

        }
    }
}

void ProductoManager::Eliminar()
{

    Producto producto;
    int id, posicion;
    cout << "ID a buscar: ";
    cin >> id;
    cout << endl;

    posicion = _archivo.buscar(id);
    if (posicion >= 0)
    {
        producto = _archivo.leer(posicion);
        Listar(producto);
        cout << endl;
        producto.setActivo(false);
        _archivo.guardar(producto, posicion);
        cout << "Registro #" << id << " eliminado correctamente" << endl;
    }
    else
    {
        cout << "No existe el registro con ID #" << id << endl;
    }
}
void ProductoManager::setPermisos(bool adm, bool sup, bool ven)
{
    _permisos[0] = adm;
    _permisos[1] = sup;
    _permisos[2] = ven;
}
