#include<iostream>
#include <cstdio>
using namespace std;

#include "VentaManager.h"

int VentaManager::GenerarId()
{
    return _archivo.getCantidadRegistros()+1;
}

bool VentaManager::restaurarStock(const int* vecProductos, const int* vecUnidades, int cantidadProductos)
{
    ProductoManager productoManager;
    for(int i = 0; i<cantidadProductos; i++)
    {
        productoManager.RestaurarStock(vecProductos[i], vecUnidades[i]);
    }
}

int VentaManager::cargarProductos(int* vecProductos, int* vecUnidades)
{
    int cantidadProductos;
    for(int i = 0; i<10; i++)
    {
        ProductoArchivo arProducto;
        Producto producto;
        bool productoValido = false;
        do
        {
            bool existeProducto = false;
            do
            {
                std::cout<<"INGRESE EL ID DEL PRODUCTO"<<std::endl;
                int id;
                cin>>id;
                cin.ignore();
                if(arProducto.buscar(id)>= 0)
                {
                    producto = arProducto.leer(arProducto.buscar(id));
                    if(producto.getActivo())
                    {
                        vecProductos[i] = id;
                        existeProducto = true;
                    }
                    else
                    {
                        std::cout<<"EL PRODUCTO INGRESADO ESTA DADO DE BAJA:"<<std::endl;
                    }
                }
                else
                {
                    cout<<"NO EXISTE UN PRODUCTO BAJO ESE ID, INGRESELO NUEVAMENTE"<<endl;
                }
            }
            while(!existeProducto);
            std::cout<<"INGRESE UNIDADES DEL PRODUCTO"<<std::endl;
            int unidades;
            unidades = ingresoStockConValidacion();
            ProductoManager productoManager;
            if(productoManager.RestarStock(producto.getID(), unidades))
            {
                vecUnidades[i] = unidades;
                std::cout<<"QUIERE AGREGAR OTRO PRODUCTO? (SI | NO): "<<std::endl;
                std::string decision = ingresoDeDecisionConValidacion();

                if (decision == "NO")
                {
                    cantidadProductos = i+1;
                    i = 9;
                }
                productoValido = true;
            }
        }
        while(!productoValido);
    }
    return cantidadProductos;
}

std::string VentaManager::validarCliente(){
    std::string nroDocCliente;
    ClienteArchivo arClientes;
    bool clienteValido = false;
    do // REVISAR CON NAHUE LAS BUSQUEDAS DE CLIENTE -- PENDIENTE ESTA VALIDACION
    {
        std::cout<<"INGRESE NUMERO DE DOCUMENTO O CUIT DEL CLIENTE"<<std::endl;
        nroDocCliente = ingresoDeDocumentoConValidacion();
        if(arClientes.buscar(nroDocCliente)>= 0)
        {
            Cliente clienteAux;
            clienteAux = arClientes.leer(arClientes.buscar(nroDocCliente));
            if(clienteAux.getEstado())
            {
                std::cout<<"CLIENTE REGISTRADO EN LA BASE DE DATOS:"<<std::endl;
                clienteAux.Mostrar();
                std::cout<<"CONTINUAR? (SI | NO): ";
                std::string decision = ingresoDeDecisionConValidacion();
                if (decision == "SI")
                {
                    clienteValido = true;
                }
            }
            else
            {
                ClienteManager clienteManager;
                std::cout<<"EL CLIENTE ESTA REGISTRADO PERO DADO DE BAJA:"<<std::endl;
                if(clienteManager.reactivar(nroDocCliente))
                {
                    clienteValido = true;
                }
            }
        }
        else
        {
            ClienteManager clienteManager;
            if(clienteManager.cargar(nroDocCliente))
            {
                clienteValido = true;
            }

        } // AGREGAR VALIDACION POR SI NO SE CARGO CORRECTAMENTE
    }
    while(!clienteValido);
    return nroDocCliente;
}

void VentaManager::Listar(Venta venta) // MOSTRAR OK, AGREGAR TEMA DE BUSCAR ID PRODUCTO PARA QUE SALGA NOMBRE
{

    std::cout<<"ID PEDIDO: "<<venta.getIdPedido()<<std::endl;
    std::cout<<"DOCUMENTO CLIENTE "<<venta.getNroDocCliente()<<std::endl;
    std::cout<<"FECHA: "<<venta.getFecha().toString()<<std::endl;
    std::cout<<"PRODUCTOS:"<<endl;
    const int* vecProductos = venta.getVecIdProducto();
    const int* vecUnidades = venta.getVecUnidadesxProducto();
    for(int i = 0; i<venta.getCantidadProductos(); i++)
    {
        // REVISAR ESTO, PROBABLEMENTE DEBA TRAERLO DESDE UNA FUNCION DE MANAGER PROD Y MANAGER MARCA TAMBIEN
        ProductoArchivo arProducto;
        MarcaArchivo arMarca;
        Producto productoAux;
        productoAux = arProducto.leer(arProducto.buscar(vecProductos[i]));
        Marca marcaAux;
        marcaAux = arMarca.leer(arMarca.buscar(productoAux.getIdMarca()));
        std::cout<<marcaAux.getNombre()<<" "<< productoAux.getModelo()<<std::endl;
        std::cout<<"CANTIDAD: "<<vecUnidades[i]<<std::endl;
    }
    std::cout<<"IMPORTE: $"<<venta.getMontoCompra()<<endl;
    std::cout<<"METODO PAGO: "<<venta.getMetodoPago()<<endl;
    std::cout<<"VENDEDOR: "<<venta.getAliasVendedor()<<endl;
}

void VentaManager::ListarTodas()
{
    int cantidadRegistros = _archivo.getCantidadRegistros();

    for(int i = 0; i < cantidadRegistros; i++)
    {
        Venta reg;
        reg = _archivo.leer(i);

        Listar(reg);
        rlutil::anykey();

    }
}

void VentaManager::Cargar()
{
    int idPedido = GenerarId();
    std::string nroDocCliente;
    Fecha fechaCompra;
    int vecIdProducto[10];
    int vecUnidadesxProducto[10];
    int cantidadProductos = 0;
    float montoCompra;
    int metodoPago;
    std::string aliasVendedor;
    bool activo = true;

    nroDocCliente = validarCliente();
    fechaCompra = Fecha().fechaActual();

    cantidadProductos = cargarProductos(vecIdProducto, vecUnidadesxProducto);

    std::cout<<"INGRESE EL METODO DE PAGO: "<<std::endl;
    cin>>metodoPago;
    std::cout<<"ALIAS VENDEDOR: "<<std::endl; // VER CON NAHUE TEMA USUARIO ACTIVO. HARDCODEADO PARA AVANZAR
    getline(cin, aliasVendedor);

    for(int i = 0; i<cantidadProductos; i++){
        ProductoArchivo arProducto;
        int posicion = arProducto.buscar(vecIdProducto[i]);
        Producto producto;

        producto = arProducto.leer(posicion);

        float monto = producto.getPrecio() * vecUnidadesxProducto[i];
        montoCompra += monto;
    }
    Venta reg(idPedido, nroDocCliente, fechaCompra, vecIdProducto, vecUnidadesxProducto, cantidadProductos, montoCompra, metodoPago, aliasVendedor, activo);
    std::cout<<"HA CARGADO LA SIGUIENTE VENTA: "<<std::endl;
    Listar(reg);
    std::cout<<"QUIERE GUARDARLA? (SI | NO): "<<std::endl;
    std::string decision = ingresoDeDecisionConValidacion();

    if (decision == "SI")
    {
        if(_archivo.guardar(reg))
        {
            okMensajeCreacion();
            rlutil::anykey();
        }
        else
        {
            errorMensajeCreacion();
            rlutil::anykey();
        }

    }
    else
    {
        restaurarStock(vecIdProducto, vecUnidadesxProducto, cantidadProductos);
    }
}

void VentaManager::Eliminar()
{

    int posicion, idVenta;
    std::cout<<"ID VENTA A ELIMINAR: "<<std::endl;
    std::cin>>idVenta;

    posicion = _archivo.buscar(idVenta);

    if(posicion >= 0)
    {
        Venta reg;
        reg = _archivo.leer(posicion);
        if(reg.getActivo())
        {
            std::cout<<"ELIMINARA LA SIGUIENTE VENTA: "<<std::endl;
            Listar(reg);
            std::cout<<"CONTINUAR? (SI | NO): "<<std::endl;
            std::string decision = ingresoDeDecisionConValidacion();

            if(decision == "SI")
            {
                reg.setActivo(false);
                if(_archivo.guardar(reg, posicion))
                {
                    okMensajeBaja();
                    rlutil::anykey();
                }
                else
                {
                    errorMensajeBaja();
                    rlutil::anykey();
                }
            }
        }
        else
        {
            registroYaEliminado();
            rlutil::anykey();
        }
    }
    else
    {
        registroNoEncontradoMensaje();
        rlutil::anykey();
    }

}

void VentaManager::Reactivar()
{

    int posicion, idVenta;
    std::cout<<"ID VENTA A REACTIVAR: "<<std::endl;
    std::cin>>idVenta;

    posicion = _archivo.buscar(idVenta);

    if(posicion >= 0)
    {
        Venta reg;
        reg = _archivo.leer(posicion);

        if(!reg.getActivo())
        {
            std::cout<<"REACTIVARA LA SIGUIENTE VENTA: "<<std::endl;
            Listar(reg);
            std::cout<<"CONTINUAR? (SI | NO): "<<std::endl;
            std::string decision = ingresoDeDecisionConValidacion();

            if(decision == "SI")
            {
                reg.setActivo(true);
                if(_archivo.guardar(reg, posicion))
                {
                    okMensajeReactivacion();
                    rlutil::anykey();
                }
                else
                {
                    errorMensajeReactivacion();
                    rlutil::anykey();
                }
            }
        }
        else
        {
            registroNoEliminado();
            rlutil::anykey();
        }
    }
    else
    {
        registroNoEncontradoMensaje();
        rlutil::anykey();
    }
}
