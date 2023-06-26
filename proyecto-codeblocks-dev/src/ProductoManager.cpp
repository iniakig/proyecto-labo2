using namespace std;

#include "ProductoManager.h"
#include "../funciones.h"
#include <../rlutil.h>
#include "../validaciones.h"
#include "../mensajes.h"
#include "string.h"
#include <iostream>
#include <iomanip>
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
    std::cout<<"ESTADO: "<<producto.getActivo()<<std::endl;
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
    rlutil::anykey();
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
        registroNoEncontradoMensaje();
    }
    rlutil::anykey();
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
        registroNoEncontradoMensaje();
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
    rlutil::anykey();
}

void ProductoManager::ListarPorTopePrecio()
{
    float topePrecio;
    std::cout<<"INGRESE TOPE DE PRECIO "<<std::endl;
    std::cin>>topePrecio; // VALIDACION PENDIENTE

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
    rlutil::anykey();

}

void ProductoManager::HacerCopiaDeSeguridad()
{
    int cantidadRegs = _archivo.getCantidadDeRegistros();

    Producto *vec = new Producto[cantidadRegs];

    if (vec == nullptr)
    {
        errorMensajeCopiaDeSeguridad();
        return;
    }

    _archivo.leer(vec, cantidadRegs);
    _archivoBkp.vaciar();

    if(_archivoBkp.guardar(vec, cantidadRegs))
    {
        okMensajeCopiaDeSeguridad();
    }
    else
    {
        errorMensajeCopiaDeSeguridad();
    }

    delete []vec;
    rlutil::anykey();
}

void ProductoManager::RestaurarCopiaDeSeguridad()
{
    int cantidadRegs = _archivoBkp.getCantidadDeRegistros();

    Producto *vec = new Producto[cantidadRegs];
    if (vec == nullptr)
    {
        errorMensajeRestauracionCopiaDeSeguridad();
        return;
    }

    _archivoBkp.leer(vec, cantidadRegs);
    _archivo.vaciar();

    if(_archivo.guardar(vec, cantidadRegs))
    {

        okMensajeRestauracionCopiaDeSeguridad();
    }
    else
    {
        errorMensajeRestauracionCopiaDeSeguridad();
    }

    delete []vec;
    rlutil::anykey();
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
    rlutil::anykey();
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
    std::cout<<"INGRESE CATEGORIA DEL PRODUCTO (1. CELULARES | 2. TABLETS | 3. ACCESORIOS):"<<std::endl;
    categoria = ingresoCategoriaProdConValidacion();
    do
    {
        std::cout<<"INGRESE NOMBRE DE LA MARCA DEL PRODUCTO"<<std::endl;
        nombreMarca=ingresoDeMarcaConValidacion();
        idMarca=managerMarca.cargarDesdeProducto(nombreMarca);
    }
    while(idMarca<=0);
    std::cout<<"INGRESE MODELO DEL PRODUCTO"<<std::endl;
    modelo = ingresoModeloConValidacion();
    std::cout<<"INGRESE DESCRIPCION DEL PRODUCTO"<<std::endl;// Convertir a mayuscula pendiente
    descripcion = ingresoDescripcionConValidacion();
    std::cout<<"INGRESE PRECIO DE VENTA"<<std::endl;
    precioVenta = ingresoPrecioConValidacion();
    std::cout<<"INGRESE STOCK"<<std::endl;
    stock = ingresoStockConValidacion();

    Producto reg(ID, categoria, idMarca,modelo, descripcion, precioVenta, stock, activo);
    cout<<"CARGO EL SIGUIENTE PRODUCTO: "<<endl;
    Listar(reg);
    cout<<"CONTINUAR? (SI | NO): ";
    std::string opc;
    opc = ingresoDeDecisionConValidacion();
    if (opc == "SI")
    {
        if(_archivo.guardar(reg))
        {
            okMensajeCreacion();
        }
        else
        {
            errorMensajeCreacion();
        }
    }
    rlutil::anykey();
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
        registroNoEncontradoMensaje();
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
        bool seguirModificando = true;
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
            std::cout << "0. VOLVER AL MENÚ DE GESTIÓN DE PRODUCTOS" << std::endl;
            std::cout << "---------------------------------------------------" << std::endl;
            std::cout << "OPCIÓN SELECCIONADA: ";
            std::cin >> opcion;
            std::cin.ignore();

            switch(opcion)
            {
            case 0:
                break;
            case 1:{
                std::cout <<"INGRESE CATEGORIA: "<< std::endl;
                categoria = ingresoCategoriaProdConValidacion();
                producto.setCategoria(categoria);
                edito = 1;
                // Preguntar al usuario si quiere seguir modificando
                cout<<"¿Desea seguir haciendo modificaciones? (SI/NO)"<<endl;
                std::string respuesta; // variable para almacenar la respuesta del usuario
                respuesta = ingresoDeDecisionConValidacion(); // leer la respuesta del usuario
                if (respuesta == "NO") { // si no quiere seguir modificando
                  seguirModificando = false; // indicar que no quiere seguir modificando
                }
                break;}
            case 2:{
                do
                {
                    std::cout <<"INGRESE MARCA: "<< std::endl;
                    nombreMarca=ingresoDeMarcaConValidacion();
                    producto.setMarca(managerMarca.cargarDesdeProducto(nombreMarca));
                }
                while(producto.getIdMarca()<=0);
                edito = 1;
                // Preguntar al usuario si quiere seguir modificando
                cout<<"¿Desea seguir haciendo modificaciones? (SI/NO)"<<endl;
                std::string respuesta; // variable para almacenar la respuesta del usuario
                respuesta = ingresoDeDecisionConValidacion(); // leer la respuesta del usuario
                if (respuesta == "NO") { // si no quiere seguir modificando
                  seguirModificando = false; // indicar que no quiere seguir modificando
                }
                break;}
            case 3:{
                std::cout <<"INGRESE MODELO: "<< std::endl;
                modelo = ingresoModeloConValidacion();
                producto.setModelo(modelo);
                edito = 1;
                // Preguntar al usuario si quiere seguir modificando
                cout<<"¿Desea seguir haciendo modificaciones? (SI/NO)"<<endl;
                std::string respuesta; // variable para almacenar la respuesta del usuario
                respuesta = ingresoDeDecisionConValidacion(); // leer la respuesta del usuario
                if (respuesta == "NO") { // si no quiere seguir modificando
                  seguirModificando = false; // indicar que no quiere seguir modificando
                }
                break;}
            case 4:{
                std::cout <<"INGRESE DESCRIPCION: "<< std::endl;
                descripcion = ingresoDescripcionConValidacion();
                producto.setDescripcion(descripcion);
                edito = 1;
                // Preguntar al usuario si quiere seguir modificando
                cout<<"¿Desea seguir haciendo modificaciones? (SI/NO)"<<endl;
                std::string respuesta; // variable para almacenar la respuesta del usuario
                respuesta = ingresoDeDecisionConValidacion(); // leer la respuesta del usuario
                if (respuesta == "NO") { // si no quiere seguir modificando
                  seguirModificando = false; // indicar que no quiere seguir modificando
                }
                break;}
            case 5:{
                std::cout <<"INGRESE PRECIO DE VENTA: "<< std::endl;
                precioVenta = ingresoPrecioConValidacion();
                producto.setPrecio(precioVenta);
                edito = 1;
                // Preguntar al usuario si quiere seguir modificando
                cout<<"¿Desea seguir haciendo modificaciones? (SI/NO)"<<endl;
                std::string respuesta; // variable para almacenar la respuesta del usuario
                respuesta = ingresoDeDecisionConValidacion(); // leer la respuesta del usuario
                if (respuesta == "NO") { // si no quiere seguir modificando
                  seguirModificando = false; // indicar que no quiere seguir modificando
                }
                break;}
            case 6:{
                std::cout <<"INGRESE STOCK: "<< std::endl;
                stock = ingresoStockConValidacion();
                producto.setStock(stock);
                edito = 1;
               // Preguntar al usuario si quiere seguir modificando
                cout<<"¿Desea seguir haciendo modificaciones? (SI/NO)"<<endl;
                std::string respuesta; // variable para almacenar la respuesta del usuario
                respuesta = ingresoDeDecisionConValidacion(); // leer la respuesta del usuario
                if (respuesta == "NO") { // si no quiere seguir modificando
                  seguirModificando = false; // indicar que no quiere seguir modificando
                }
                break;}
            default:
                std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;

            }
        }
        while(seguirModificando);
        if(edito)
        {
            cout<<"MODIFICO EL SIGUIENTE PRODUCTO: "<<endl;
            Listar(producto);
            cout<<"CONTINUAR? (SI | NO): ";
            std::string opc;
            opc = ingresoDeDecisionConValidacion();
            if (opc == "SI")
            {
                if(_archivo.guardar(producto, posicion))
                {
                    okMensajeModificacion();
                }
                else
                {
                    errorMensajeModificacion();
                }
            }

        }
    }
    rlutil::anykey();
}

void ProductoManager::Eliminar()
{

    Producto producto;
    int id, posicion;
    cout << "ID A ELIMINAR: ";
    cin >> id;
    cout << endl;

    posicion = _archivo.buscar(id);
    if (posicion >= 0)
    {
        producto = _archivo.leer(posicion);
        if(producto.getActivo())
        {
            Listar(producto);
            cout<<"CONTINUAR? (SI | NO): ";
            std::string opc;
            opc = ingresoDeDecisionConValidacion();
            if (opc == "SI")
            {
                producto.setActivo(false);
                if(_archivo.guardar(producto, posicion))
                {
                    okMensajeBaja();
                }
                else
                {
                    errorMensajeBaja();
                }
            }
        }
        else
        {
            cout<<"EL REGISTRO INGRESADO YA SE ENCUENTRA ELIMINADO"<<endl;
            rlutil::anykey();
        }
    }
    else
    {
        registroNoEncontradoMensaje();
    }
    rlutil::anykey();
}

void ProductoManager::reactivar()
{
    Producto reg;
    int id, posicion;
    cout<<"ID PRODUCTO A REACTIVAR: ";
    cin>>id;
    cout<<endl;

    posicion = _archivo.buscar(id);

    if(posicion >= 0)
    {
        reg = _archivo.leer(posicion);
        if(!reg.getActivo())
        {
            cout<<"REACTIVARA EL SIGUIENTE PRODUCTO: "<<endl;
            Listar(reg);
            cout<<"CONFIRMAR? (SI | NO): ";
            std::string opc;
            opc = ingresoDeDecisionConValidacion();
            if (opc == "SI")
            {
                reg.setActivo(true);
                if(_archivo.guardar(reg, posicion))
                {
                    okMensajeReactivacion();
                }
                else
                {
                    errorMensajeReactivacion();
                }
            }
        }
        else
        {
            cout<<"EL REGISTRO INGRESADO NO SE ENCUENTRA ELIMINADO"<<endl;
            rlutil::anykey();
        }
    }
    else
    {
        registroNoEncontradoMensaje();
    }
    rlutil::anykey();
}

void ProductoManager::CargarStock()
{
    Producto reg;
    int id, posicion;
    cout<<"INGRESE EL ID DEL PRODUCTO: ";
    cin>>id;
    cout<<endl;

    posicion = _archivo.buscar(id);

    if(posicion >=0 )
    {
        reg = _archivo.leer(posicion);
        if(!reg.getActivo())
        {
            std::cout<<"EL PRODUCTO INGRESADO SE ENCUENTRA DADO DE BAJA"<<std::endl;
            rlutil::anykey();
        }
        else
        {
            std::cout<<"ACTUALIZARA EL STOCK DEL SIGUIENTE PRODUCTO:"<<std::endl;
            Listar(reg);

            cout<<"CONTINUAR? (SI | NO): ";
            std::string opc;
            opc = ingresoDeDecisionConValidacion();
            if (opc == "SI")
            {
                int stockActual = reg.getStock();
                int unidadesNuevas;
                std::cout<<"INGRESE LA CANTIDAD DE UNIDADES A AGREGAR: "<<std::endl;
                unidadesNuevas = ingresoStockConValidacion();
                reg.setStock(stockActual + unidadesNuevas);
                if(_archivo.guardar(reg, posicion))
                {
                    std::cout<<"STOCK ACTUALIZADO"<<std::endl;
                    rlutil::anykey();
                }
                else
                {
                    std::cout<<"ERROR AL ACTUALIZAR EL STOCK"<<std::endl;
                    rlutil::anykey();
                }
            }
        }
    }
    else
    {
        registroNoEncontradoMensaje();
        rlutil::anykey();
    }
}

bool ProductoManager::RestaurarStock(int id, int unidades)
{

    Producto reg;
    int posicion = _archivo.buscar(id);
    reg = _archivo.leer(posicion);

    int stockActual = reg.getStock();
    reg.setStock(stockActual + unidades);

    if(_archivo.guardar(reg, posicion))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ProductoManager::RestarStock()
{
    Producto reg;
    int id, posicion;
    cout<<"INGRESE EL ID DEL PRODUCTO: ";
    cin>>id;
    cout<<endl;

    posicion = _archivo.buscar(id);

    if(posicion >=0 )
    {
        reg = _archivo.leer(posicion);
        if(!reg.getActivo())
        {
            std::cout<<"EL PRODUCTO INGRESADO SE ENCUENTRA DADO DE BAJA"<<std::endl;
            rlutil::anykey();
        }
        else
        {
            std::cout<<"ACTUALIZARA EL STOCK DEL SIGUIENTE PRODUCTO:"<<std::endl;
            Listar(reg);

            cout<<"CONTINUAR? (SI | NO): ";
            std::string opc;
            opc = ingresoDeDecisionConValidacion();
            if (opc == "SI")
            {
                int stockActual = reg.getStock();
                int unidades;
                std::cout<<"INGRESE LA CANTIDAD DE UNIDADES A RESTAR: "<<std::endl;
                unidades = ingresoStockConValidacion();
                if(stockActual - unidades >=0)
                {
                    reg.setStock(stockActual - unidades);
                    if(_archivo.guardar(reg, posicion))
                    {
                        std::cout<<"STOCK ACTUALIZADO"<<std::endl;
                        rlutil::anykey();
                    }
                    else
                    {
                        std::cout<<"ERROR AL ACTUALIZAR EL STOCK"<<std::endl;
                        rlutil::anykey();
                    }

                }
                else
                {
                    std::cout<<"NO ES POSIBLE RESTAR EL STOCK, INGRESO MAS UNIDADES DE LAS DISPONIBLES"<<std::endl;
                    rlutil::anykey();
                }
            }
        }
    }
    else
    {
        registroNoEncontradoMensaje();
        rlutil::anykey();
    }
}

bool ProductoManager::RestarStock(int id, int unidades)
{
    int posicion = _archivo.buscar(id);
    Producto reg;
    reg = _archivo.leer(posicion);
    if(reg.getStock()-unidades >= 0)
    {
        int stockActual = reg.getStock();
        reg.setStock(stockActual - unidades);
        if(_archivo.guardar(reg, posicion))
        {
            return true;
        }
        else
        {
            std::cout<<"ERROR AL MODIFICAR EL REGISTRO DE STOCK, INTENTELO NUEVAMENTE"<<std::endl;
            return false;
        }
    }
    else
    {
        std::cout<<"STOCK INSUFICIENTE. UNIDADES DISPONIBLES: "<<reg.getStock()<<std::endl;
        return false;
    }

}

void ProductoManager::setPermisos(bool adm, bool sup, bool ven)
{
    _permisos[0] = adm;
    _permisos[1] = sup;
    _permisos[2] = ven;
}
