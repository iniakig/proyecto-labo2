#include<iostream>
using namespace std;

#include "VentaManager.h"

int VentaManager::GenerarId()
{
    return _archivo.getCantidadRegistros()+1;
}

void VentaManager::Cargar()
{
    ClienteArchivo arClientes;
    int idPedido = GenerarId();
    int tipoDocumento;
    std::string nroDocCliente;
    Fecha fechaCompra;
    int vecIdProducto[10];
    int vecUnidadesxProducto[10];
    float montoCompra;
    int metodoPago;
    std::string aliasVendedor;
    bool activo = true;

    std::cout<<"INGRESE TIPO DE DOCUMENTO DEL CLIENTE"<<std::endl;
    int clienteValido = 0;
    do // REVISAR CON NAHUE LAS BUSQUEDAS DE CLIENTE -- PENDIENTE ESTA VALIDACION
    {
        tipoDocumento = ingresoTipoDeDocumentoConValidacion();
        std::cout<<"INGRESE NUMERO DE DOCUMENTO O CUIT DEL CLIENTE"<<std::endl;
        nroDocCliente = ingresoDeDocumentoConValidacion();
        if(arClientes.buscar(nroDocCliente)>= 0)
        {
            cout<<arClientes.buscar(nroDocCliente);
            clienteValido = 1;
        }
        else
        {
            ClienteManager clienteManager;
            clienteManager.cargar();
            clienteValido = 1;
        }
    }
    while(clienteValido=0);
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
            }else{
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
            i = 9;
        }
    }

    std::cout<<"INGRESE EL METODO DE PAGO: "<<std::endl;
    cin>>metodoPago;
    std::cout<<"ALIAS VENDEDOR: "<<std::endl; // VER CON NAHUE TEMA USUARIO ACTIVO. HARDCODEADO PARA AVANZAR
    getline(cin, aliasVendedor);

    Venta reg(idPedido, tipoDocumento, nroDocCliente, fechaCompra, vecIdProducto, vecUnidadesxProducto, montoCompra, metodoPago, aliasVendedor, activo);
    if(_archivo.guardar(reg))
    {
        okMensajeCreacion();
    }
    else
    {
        errorMensajeCreacion();
    }
}





