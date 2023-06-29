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

void ProductoManager::Listar(Producto producto, int tipoListado)
{
    MarcaArchivo archivoMarcas;
    Marca marca;
    marca=archivoMarcas.leer(archivoMarcas.buscar(producto.getIdMarca()));

    switch (tipoListado)
    {
    case 0:
        std::cout << "Id: " << producto.getID() << std::endl;
        std::cout << "Categoria: " << getCategoriaDescripcion(producto.getCategoria()) << std::endl;
        std::cout << "Marca: " << marca.getNombre() << std::endl;
        std::cout << "Modelo: " << producto.getModelo() << std::endl;
        std::cout << "Descripcion: " << producto.getDescripcion() << std::endl;
        std::cout << "Precio: " << std::fixed << std::setprecision(2) << producto.getPrecio() << endl;
        std::cout << "Stock: " << producto.getStock() << std::endl;
        std::cout << "Estado: " << producto.getActivo() << std::endl;
        break;
    case 1:
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(6) << producto.getID();
        std::cout << std::setw(11) << producto.getCategoria();
        std::cout << std::setw(18)<<  marca.getNombre();
        std::cout << std::setw(22) << producto.getModelo() ;
        std::cout << std::setw(28) << producto.getDescripcion();
        std::cout << std::setw(18) << std::fixed << std::setprecision(2) << producto.getPrecio();
        std::cout << std::setw(8) << producto.getStock();
        break;
    }
}

void ProductoManager::ListarTodos()
{
    rlutil::cls();
    int cantidadRegistros = _archivo.getCantidadDeRegistros ();

    for (int i = 0; i<cantidadRegistros; i++)
    {
        Producto reg = _archivo.leer(i);
        if (reg.getActivo()==true)
        {

            Listar(reg,1);
            cout << endl;
        }
    }
    rlutil::anykey();
}

void ProductoManager::listarActivos()
{
    rlutil::cls();
    std::cout << "PRODUCTOS ACTIVOS" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;

    int cantidadDeRegistros = _archivo.getCantidadRegistrosActivos();
    Producto *listaDeProductos = new Producto[cantidadDeRegistros];
    int resultadosEncontrados = 0;

    if(listaDeProductos == nullptr)
    {
        std::cout << std::endl;
        std::cout << "Ocurrió un error al visualizar el listado" << std::endl;
        return;
    }

    _archivo.leer(listaDeProductos, cantidadDeRegistros);

    // ordenadores
    ordenarPorNombreDeMarca(listaDeProductos, cantidadDeRegistros);

    for (int i = 0; i < cantidadDeRegistros; i++)
    {
        if (listaDeProductos[i].getActivo())
        {
            resultadosEncontrados++;
        }
    }

    if (resultadosEncontrados > 0)
    {
        std::cout << std::endl;
        std::cout << "Registros encontrados: " << resultadosEncontrados << std::endl;
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(6) << "Id";
        std::cout << std::setw(11) << "Categoria";
        std::cout << std::setw(18) << "Marca";
        std::cout << std::setw(22) << "Modelo";
        std::cout << std::setw(28) << "Descripcion";
        std::cout << std::setw(18) << "Precio de Venta";
        std::cout << std::setw(8) << "Stock";
        std::cout << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------------------";

        for (int i = 0; i < cantidadDeRegistros; i++)
        {
            if (listaDeProductos[i].getActivo())
            {
                Listar(listaDeProductos[i], 1);
            }
        }
        std::cout << std::endl;
        mensajeFinDelListado();
    }
    else
    {
        mensajeListadoSinDatosEncontrados();
    }

    delete[] listaDeProductos;
    rlutil::anykey();
}

void ProductoManager::ListarXId()
{
    rlutil::cls();
    int id;

    cout << "Ingrese el ID: ";
    cin >> id;

    int posicion = _archivo.buscar(id);
    if (posicion >= 0)
    {
        Producto producto = _archivo.leer(posicion);
        if(producto.getActivo()==true)
        {
            std::cout << std::endl;
            std::cout << std::left;
            std::cout << std::setw(6) << "Id";
            std::cout << std::setw(11) << "Categoria";
            std::cout << std::setw(8) << "Marca";
            std::cout << std::setw(16) << "Modelo";
            std::cout << std::setw(15) << "Descripcion";
            std::cout << std::setw(18) << "Precio de Venta";
            std::cout << std::setw(8) << "Stock";
            std::cout << std::endl;
            std::cout << "----------------------------------------------------------------------------------" << std::endl;

            Listar(producto,1);

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
    rlutil::cls();
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
        system("pause");

        return;
    }
    Producto producto;
    ProductoArchivo archivoProducto;
    int cantRegProd=archivoProducto.getCantidadDeRegistros();
    std::cout << std::endl;
    std::cout << std::left;
    std::cout << std::setw(6) << "Id";
    std::cout << std::setw(11) << "Categoria";
    std::cout << std::setw(14) << "Marca";
    std::cout << std::setw(16) << "Modelo";
    std::cout << std::setw(15) << "Descripcion";
    std::cout << std::setw(18) << "Precio de Venta";
    std::cout << std::setw(8) << "Stock";
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------------------" << std::endl;
    for(int i=0; i<cantRegProd; i++)
    {
        producto=archivoProducto.leer(i);
        if(producto.getIdMarca()==idMarca && producto.getActivo()==true)
        {
            Listar(producto,1);
            std::cout << std::endl;
        }

    }
    rlutil::anykey();
}

void ProductoManager::ListarPorTopePrecio()
{
    rlutil::cls();
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
    std::cout << std::endl;
    std::cout << std::left;
    std::cout << std::setw(6) << "Id";
    std::cout << std::setw(11) << "Categoria";
    std::cout << std::setw(8) << "Marca";
    std::cout << std::setw(16) << "Modelo";
    std::cout << std::setw(15) << "Descripcion";
    std::cout << std::setw(18) << "Precio de Venta";
    std::cout << std::setw(8) << "Stock";
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------------------" << std::endl;
    for(int a=0; a<cantProductos; a++)
    {
        producto=ProductosOrdenadosPorPrecio[a];
        if(producto.getPrecio()<=topePrecio && producto.getActivo()==true)
        {
            Listar(producto,1);
            std::cout << std::endl;
        }
    }
    rlutil::anykey();

}

void ProductoManager::HacerCopiaDeSeguridad()
{
    rlutil::cls();
    int cantidadRegs = _archivo.getCantidadDeRegistros();
    if(cantidadRegs <= 0)
    {
        //errorMensajeCopiaDeSeguridadSinRegs();
        rlutil::anykey();
        return;
    }
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
    rlutil::cls();
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


    rlutil::cls();
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
    std::cout << std::endl;
    std::cout << std::left;
    std::cout << std::setw(5) << "Id";
    std::cout << std::setw(12) << "Categoria";
    std::cout << std::setw(14) << "Marca";
    std::cout << std::setw(16) << "Modelo";
    std::cout << std::setw(14) << "Descripcion";
    std::cout << std::setw(18) << "Precio de Venta";
    std::cout << std::setw(8) << "Stock";
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------------------" << std::endl;
    for(int a=0; a<cantProductos; a++)
    {
        producto=ProductosOrdenadosStock[a];
        if(producto.getActivo()==true)
        {

            Listar(producto,1);
            std::cout << std::endl;
        }
    }
    delete []ProductosOrdenadosStock;
    rlutil::anykey();
}

void ProductoManager::Cargar()
{
    rlutil::cls();
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

    std::cout << "AGREGAR USUARIO" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;

    ID=GenerarId();
    std::cout<<"INGRESE CATEGORIA DEL PRODUCTO (1. CELULARES | 2. TABLETS | 3. ACCESORIOS): ";
    categoria = ingresoCategoriaProdConValidacion();
    do
    {
        std::cout<<"INGRESE NOMBRE DE LA MARCA DEL PRODUCTO: ";
        nombreMarca=ingresoDeMarcaConValidacion();
        idMarca=managerMarca.cargarDesdeProducto(nombreMarca);
    }
    while(idMarca<=0);
    std::cout<<"INGRESE MODELO DEL PRODUCTO: ";
    modelo = ingresoModeloConValidacion();
    std::cout<<"INGRESE DESCRIPCION DEL PRODUCTO: ";// Convertir a mayuscula pendiente
    descripcion = ingresoDescripcionConValidacion();
    std::cout<<"INGRESE PRECIO DE VENTA: ";
    precioVenta = ingresoPrecioConValidacion();
    std::cout<<"INGRESE STOCK: ";
    stock = ingresoStockConValidacion();

    Producto reg(ID, categoria, idMarca,modelo, descripcion, precioVenta, stock, activo);
    std::cout << std::endl;
    cout<<"CARGÓ EL SIGUIENTE PRODUCTO: "<<endl;
    Listar(reg,0);
    std::cout<<"CONTINUAR? (SI | NO): ";
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
    rlutil::cls();
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
            std::cout << "---------------------------------------------------" << std::endl;
            std::cout << "0. VOLVER AL MENÚ DE GESTIÓN DE PRODUCTOS" << std::endl;
            std::cout << "---------------------------------------------------" << std::endl;
            std::cout << "OPCIÓN SELECCIONADA: ";
            std::cin >> opcion;
            std::cin.ignore();

            switch(opcion)
            {
            case 0:
                seguirModificando = false;
                break;
            case 1:
            {
                std::cout <<"INGRESE CATEGORIA: "<< std::endl;
                categoria = ingresoCategoriaProdConValidacion();
                producto.setCategoria(categoria);
                edito = 1;

                std::cout<<"¿Desea seguir haciendo modificaciones? (SI/NO)"<<std::endl;
                std::string respuesta;
                respuesta = ingresoDeDecisionConValidacion();
                if (respuesta == "NO")
                {
                    seguirModificando = false;
                }
                rlutil::cls();

                break;
            }
            case 2:
            {
                do
                {
                    std::cout <<"INGRESE MARCA: "<< std::endl;
                    nombreMarca=ingresoDeMarcaConValidacion();
                    producto.setMarca(managerMarca.cargarDesdeProducto(nombreMarca));
                }
                while(producto.getIdMarca()<=0);
                edito = 1;
                std::cout<<"¿Desea seguir haciendo modificaciones? (SI/NO)"<<std::endl;
                std::string respuesta;
                respuesta = ingresoDeDecisionConValidacion();
                if (respuesta == "NO")
                {
                    seguirModificando = false;
                }
                break;
            }
            case 3:
            {
                std::cout <<"INGRESE MODELO: "<< std::endl;
                modelo = ingresoModeloConValidacion();
                producto.setModelo(modelo);
                edito = 1;
                std::cout<<"¿Desea seguir haciendo modificaciones? (SI/NO)"<<std::endl;
                std::string respuesta;
                respuesta = ingresoDeDecisionConValidacion();
                if (respuesta == "NO")
                {
                    seguirModificando = false;
                }
                break;
            }
            case 4:
            {
                std::cout <<"INGRESE DESCRIPCION: "<< std::endl;
                descripcion = ingresoDescripcionConValidacion();
                producto.setDescripcion(descripcion);
                edito = 1;
                std::cout<<"¿Desea seguir haciendo modificaciones? (SI/NO)"<<std::endl;
                std::string respuesta;
                respuesta = ingresoDeDecisionConValidacion();
                if (respuesta == "NO")
                {
                    seguirModificando = false;
                }
                break;
            }
            case 5:
            {
                std::cout <<"INGRESE PRECIO DE VENTA: "<< std::endl;
                precioVenta = ingresoPrecioConValidacion();
                producto.setPrecio(precioVenta);
                edito = 1;
                std::cout<<"¿Desea seguir haciendo modificaciones? (SI/NO)"<<std::endl;
                std::string respuesta;
                respuesta = ingresoDeDecisionConValidacion();
                if (respuesta == "NO")
                {
                    seguirModificando = false;
                }
                break;
            }
            default:
                std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;

            }
        }
        while(seguirModificando);
        if(edito)
        {
            std::cout<<"MODIFICO EL SIGUIENTE PRODUCTO: "<<endl;
            Listar(producto,0);
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
    rlutil::cls();
    Producto producto;
    int id, posicion;
    cout << "ID A ELIMINAR: ";
    cin >> id;
    cin.ignore();
    cout << endl;

    posicion = _archivo.buscar(id);
    if (posicion >= 0)
    {
        producto = _archivo.leer(posicion);
        if(producto.getActivo())
        {
            if(producto.getStock()>0)
            {
                cout<<"NO ES POSIBLE ELIMINAR EL PRODUCTO SELECCIONADO. AUN CUENTA CON STOCK DISPONIBLE.";
            }
            else
            {
                Listar(producto,0);
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
    rlutil::cls();
    Producto reg;
    int id, posicion;
    cout<<"ID PRODUCTO A REACTIVAR: ";
    cin>>id;
    cin.ignore();
    cout<<endl;

    posicion = _archivo.buscar(id);

    if(posicion >= 0)
    {
        reg = _archivo.leer(posicion);
        if(!reg.getActivo())
        {
            cout<<"REACTIVARA EL SIGUIENTE PRODUCTO: "<<endl;
            Listar(reg,0);
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
    setPermisos(1,1,0);

    UsuarioActivo usuario;
    int rolUsuario = usuario.getRolUsuarioActivo();

    if(_permisos[rolUsuario])
    {
        rlutil::cls();
        Producto reg;
        int id, posicion;
        cout<<"INGRESE EL ID DEL PRODUCTO: ";
        cin>>id;
        cin.ignore();
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
                Listar(reg,0);

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
    else
    {
        mensajeAccesoRestringido();
        rlutil::anykey();
    }
}

bool ProductoManager::RestaurarStock(int id, int unidades)
{
    rlutil::cls();
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
    setPermisos(1,1,0);

    UsuarioActivo usuario;
    int rolUsuario = usuario.getRolUsuarioActivo();

    if(_permisos[rolUsuario])
    {
        rlutil::cls();
        Producto reg;
        int id, posicion;
        cout<<"INGRESE EL ID DEL PRODUCTO: ";
        cin>>id;
        cin.ignore();
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
                Listar(reg,0);

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
    else
    {
        mensajeAccesoRestringido();
        rlutil::anykey();
    }
}

bool ProductoManager::RestarStock(int id, int unidades)
{
    rlutil::cls();
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

std::string ProductoManager::getCategoriaDescripcion(int categoria)
{
    {
        if(categoria == 1)
        {
            std::string stringCategoria ="CELULARES";
            return stringCategoria;
        }
        else if(categoria == 2)
        {
            std::string stringCategoria = "TABLETS";
            return stringCategoria;
        }
        else
        {
            std::string stringCategoria = "ACCESORIOS";
            return stringCategoria;
        }
    }
}

void ProductoManager::setPermisos(bool adm, bool sup, bool ven)
{
    _permisos[0] = adm;
    _permisos[1] = sup;
    _permisos[2] = ven;
}

void ProductoManager::listarProductos()
{
    int opcion = -1;

    do
    {
        rlutil::cls();
        std::cout << "LISTAR PRODUCTOS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. POR ID" << std::endl;
        std::cout << "2. POR STOCK" << std::endl;
        std::cout << "3. POR TOPE DE PRECIO" << std::endl;
        std::cout << "4. POR MARCA" << std::endl;
        std::cout << "5. PRODUCTOS ACTIVOS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "0. VOLVER AL MENÚ ANTERIOR" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "OPCIÓN SELECCIONADA: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion)
        {
        case 0:
            break;
        case 1:
            ListarXId();
            break;
        case 2:
            ListarPorStock();
            break;
        case 3:
            ListarPorTopePrecio();
            break;
        case 4:
            ListarPorMarca();
            break;
        case 5:
            listarActivos();
            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}

void ProductoManager::productosPorAgotarse()
{
    int cantidadMinimaProductos = 0;

    rlutil::cls();
    std::cout << "PRODUCTOS PRÓXIMOS A AGOTAR STOCK" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Ingrese la cantidad mínima de stock de referencia: ";
    cantidadMinimaProductos = ingresoDeNumeroEnteroConValidacion();

    int cantidadDeRegistros = _archivo.getCantidadRegistrosActivos();
    Producto *listaDeProductos = new Producto[cantidadDeRegistros];
    int resultadosEncontrados = 0;

    if(listaDeProductos == nullptr)
    {
        std::cout << std::endl;
        std::cout << "Ocurrió un error al visualizar el listado" << std::endl;
        return;
    }

    _archivo.leer(listaDeProductos, cantidadDeRegistros);

    ordenarPorNombreDeMarca(listaDeProductos, cantidadDeRegistros);

    for (int i = 0; i < cantidadDeRegistros; i++)
    {
        if (listaDeProductos[i].getStock() < cantidadMinimaProductos && listaDeProductos[i].getActivo() == true)
        {
            resultadosEncontrados++;
        }
    }

    if (resultadosEncontrados > 0)
    {
        std::cout << std::endl;
        std::cout << "Registros encontrados: " << resultadosEncontrados << std::endl;
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(6) << "Id";
        std::cout << std::setw(11) << "Categoria";
        std::cout << std::setw(18) << "Marca";
        std::cout << std::setw(22) << "Modelo";
        std::cout << std::setw(28) << "Descripcion";
        std::cout << std::setw(18) << "Precio de Venta";
        std::cout << std::setw(8) << "Stock";
        std::cout << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------------------";

        for (int i = 0; i < cantidadDeRegistros; i++)
        {
            if (listaDeProductos[i].getStock() < cantidadMinimaProductos && listaDeProductos[i].getActivo() == true)
            {
                Listar(listaDeProductos[i], 1);
            }
        }
        std::cout << std::endl;
        mensajeFinDelListado();
    }
    else
    {
        mensajeListadoSinDatosEncontrados();
    }

    delete[] listaDeProductos;
    rlutil::anykey();
}

void ProductoManager::ordenarPorNombreDeMarca(Producto *listaDeProductos, int cantidadDeRegistros)
{
    Marca marca;
    MarcaArchivo marcaArchivo;
    Producto producto;
    ProductoArchivo productoArchivo;

    int menor = 0;

    for (int i = 0; i < cantidadDeRegistros - 1; i++)
    {
        menor = i;

        int posicionMarca = marcaArchivo.buscar(listaDeProductos[i].getIdMarca());
        marca = marcaArchivo.leer(posicionMarca);
        std::string marcaDescripcion = marca.getNombre();

        for (int j = i + 1; j < cantidadDeRegistros; j++)
        {
            int posicionMarcaActual = marcaArchivo.buscar(listaDeProductos[j].getIdMarca());
            marca = marcaArchivo.leer(posicionMarcaActual);
            std::string marcaDescripcionActual = marca.getNombre();

            if (marcaDescripcionActual < marcaDescripcion)
            {
                menor = j;
                marcaDescripcion = marcaDescripcionActual;
            }

        }

        if (i != menor)
        {
            producto = listaDeProductos[i];
            listaDeProductos[i] = listaDeProductos[menor];
            listaDeProductos[menor] = producto;
        }
    }
}

void ProductoManager::cincoProductosMasVendidos()
{
    VentaArchivo archivoVenta("ventas.dat");
    Venta venta;
    Producto producto;
    int cantVentas=archivoVenta.getCantidadRegistros();
    int cantProd=_archivo.getCantidadDeRegistros();
    const int *vecIdprod;
    const int *vecUnidadesPorProd;
    int *vecProdXId= new int[cantProd];
    int *vecUnidadesTotales=new int [cantProd];
    ponerCero(vecUnidadesTotales, cantProd);
    Fecha fechaActual= fechaActual.fechaActual();
//GUARDA EN vecProXId LOS ID DE CADA PRODUCTO REGISTRADO
    for(int i=0; i<cantProd; i++)
    {
        producto=_archivo.leer(i);
        vecProdXId[i]=producto.getID();
    }
//LEE CADA REGISTRO DE VENTA, SI COINCIDE MES Y AÑO ACTUAL ASIGNA EL VECTOR DE ID DE PRODUCTO A OTRO VECTOR DE ID PRODUCTO
//ASIGNA A VECTOR DE UNIDADES OTRO VECTOR DE UNIDADES DE LA VENTA QUE ESTA SIENDO LEIDA
    for(int a=0; a<cantVentas; a++)
    {
        venta=archivoVenta.leer(a);
        if(venta.getFecha().getAnio() == fechaActual.getAnio() && venta.getFecha().getMes()== fechaActual.getMes())
        {
            vecIdprod=venta.getVecIdProducto();//VECTOR QUE CONTIENE LOS ID DE LOS PRODUCTOS DE LA VENTA
            vecUnidadesPorProd=venta.getVecUnidadesxProducto();
        }//UNIDADES DE ESOS PRODUCTOS

        for(int e=0; e<cantProd; e++)
        {
            for(int o=0; o<10; o++)
            {
                if(vecProdXId[e]==vecIdprod[o])
                {
                    vecUnidadesTotales[e]+=vecUnidadesPorProd[o];
                }
            }
        }
    }

    for (int i = 0; i < cantProd - 1; i++)
    {
        for (int j = i + 1; j < cantProd; j++)
        {
            if (vecUnidadesTotales[i] < vecUnidadesTotales[j])
            {
                int aux = vecUnidadesTotales[i];
                vecUnidadesTotales[i] = vecUnidadesTotales[j];
                vecUnidadesTotales[j] = aux;

                aux = vecProdXId[i];
                vecProdXId[i] = vecProdXId[j];
                vecProdXId[j] = aux;
            }
        }
    }
    rlutil::cls();
    std::cout<<"                5 PRODUCTOS MAS VENDIDOS DEL MES"<<std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;

    for(int i=0; i<5; i++)
    {
        producto=_archivo.leer(_archivo.buscar(vecProdXId[i]));

        std::cout<<"ID DE PRODUCTO: "<<vecProdXId[i]<<std::endl;
        std::cout<<"ID DE MARCA: "<<producto.getIdMarca()<<std::endl;
        std::cout<<"MODELO: "<<producto.getModelo()<<std::endl;
        std::cout<<"UNIDADES VENDIDAS: "<<vecUnidadesTotales[i]<<std::endl;
        std::cout<<std::endl;
    }
    rlutil::anykey();

}


