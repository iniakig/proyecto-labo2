#include<iostream>
using namespace std;

#include "VentaManager.h"

int VentaManager::GenerarId()
{
    return _archivo.getCantidadRegistros()+1;
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

void VentaManager::Cargar()
{
    ClienteArchivo arClientes;
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
                if(clienteManager.reactivarDesdeVenta(nroDocCliente))
                {
                    clienteValido = true;
                }
            }
        }
        else
        {
            ClienteManager clienteManager;
            if(clienteManager.cargar(nroDocCliente)){
                clienteValido = true;
            }

        } // AGREGAR VALIDACION POR SI NO SE CARGO CORRECTAMENTE
    }
    while(!clienteValido);
    fechaCompra = Fecha().fechaActual();
    for(int i = 0; i<10; i++)
    {
        ProductoArchivo arProducto;
        std::cout<<"INGRESE EL ID DEL PRODUCTO"<<std::endl;
        int existeProducto = 0;
        do
        {
            int id;
            cin>>id;
            if(arProducto.buscar(id)>= 0)
            {
                vecIdProducto[i] = id;
                existeProducto = 1;
            }
            else
            {
                cout<<"NO EXISTE UN PRODUCTO BAJO ESE ID, INGRESELO NUEVAMENTE"<<endl;
            }
        }
        while(existeProducto == 0);
        std::cout<<"INGRESE UNIDADES DEL PRODUCTO"<<std::endl;
        int unidades;
        cin>>unidades;
        vecUnidadesxProducto[i] = unidades;
        Producto producto;
        producto = arProducto.leer(arProducto.buscar(vecIdProducto[i]));
        float montoProductos = producto.getPrecio() * unidades; // REFACTORIZAR
        montoCompra += montoProductos;
        std::cout<<"QUIERE AGREGAR OTRO PRODUCTO? (SI | NO): "<<std::endl;
        std::string decision = ingresoDeDecisionConValidacion();

        if (decision == "NO")
        {
            cantidadProductos = i+1;
            i = 9;
        }
    }

    std::cout<<"INGRESE EL METODO DE PAGO: "<<std::endl;
    cin>>metodoPago;
    std::cout<<"ALIAS VENDEDOR: "<<std::endl; // VER CON NAHUE TEMA USUARIO ACTIVO. HARDCODEADO PARA AVANZAR
    getline(cin, aliasVendedor);

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
        }
        else
        {
            errorMensajeCreacion();
        }

    }
}





