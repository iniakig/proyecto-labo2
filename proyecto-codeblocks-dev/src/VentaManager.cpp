#include<iostream>
#include <cstdio>
#include <iomanip>

#include "../mensajes.h"
#include "../validaciones.h"

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
                        if(producto.getStock() > 0 )
                        {
                            vecProductos[i] = id;
                            existeProducto = true;

                        }
                        else
                        {
                            rlutil::setColor(rlutil::LIGHTRED);
                            std::cout<<"EL PRODUCTO INGRESADO NO CUENTA CON STOCK DISPONIBLE"<<std::endl;
                            rlutil::setColor(rlutil::WHITE);
                        }
                    }
                    else
                    {
                        rlutil::setColor(rlutil::LIGHTRED);
                        std::cout<<"EL PRODUCTO INGRESADO ESTA DADO DE BAJA:"<<std::endl;
                        rlutil::setColor(rlutil::WHITE);
                    }
                }
                else
                {
                    rlutil::setColor(rlutil::LIGHTRED);
                    cout<<"NO EXISTE UN PRODUCTO BAJO ESE ID, INGRESELO NUEVAMENTE"<<endl;
                    rlutil::setColor(rlutil::WHITE);
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

std::string VentaManager::validarCliente()
{
    std::string nroDocCliente;
    ClienteArchivo arClientes;
    bool clienteValido = false;
    do // REVISAR CON NAHUE LAS BUSQUEDAS DE CLIENTE -- PENDIENTE ESTA VALIDACION
    {
        std::cout<<"INGRESE NUMERO DE DOCUMENTO O CUIT DEL CLIENTE: ";
        nroDocCliente = ingresoDeDocumentoConValidacion();
        std::cout << std::endl;

        if(arClientes.buscar(nroDocCliente)>= 0)
        {
            Cliente clienteAux;
            clienteAux = arClientes.leer(arClientes.buscar(nroDocCliente));
            if(clienteAux.getEstado())
            {
                std::cout<<"CLIENTE REGISTRADO EN LA BASE DE DATOS:"<<std::endl;
                //clienteAux.Mostrar();
                ClienteManager clienteManager;
                clienteManager.listar(clienteAux, 0);
                std::cout << std::endl;
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

std::string VentaManager::metodoPagoAString(int metodoPago)
{
    if(metodoPago == 1)
    {
        std::string stringMetodoPago ="EFECTIVO";
        return stringMetodoPago;
    }
    else if(metodoPago == 2)
    {
        std::string stringMetodoPago = "TARJETA";
        return stringMetodoPago;
    }
    else
    {
        std::string stringMetodoPago = "TRANSFERENCIA";
        return stringMetodoPago;
    }
}

void VentaManager::Listar(Venta venta)
{

    std::cout<<"ID PEDIDO: "<<venta.getIdPedido()<<std::endl;
    std::cout<<"DOCUMENTO CLIENTE "<<venta.getNroDocCliente()<<std::endl;
    std::cout<<"FECHA: "<<venta.getFecha().toString()<<std::endl;
    std::cout<<"PRODUCTOS:"<<endl;
    const int* vecProductos = venta.getVecIdProducto();
    const int* vecUnidades = venta.getVecUnidadesxProducto();
    std::string metodoPago = metodoPagoAString(venta.getMetodoPago());
    for(int i = 0; i<venta.getCantidadProductos(); i++)
    {
        // REVISAR ESTO, PROBABLEMENTE DEBA TRAERLO DESDE UNA FUNCION DE MANAGER PROD Y MANAGER MARCA TAMBIEN
        ProductoArchivo arProducto;
        MarcaArchivo arMarca;
        Producto productoAux;
        productoAux = arProducto.leer(arProducto.buscar(vecProductos[i]));
        Marca marcaAux;
        marcaAux = arMarca.leer(arMarca.buscar(productoAux.getIdMarca()));
        std::cout<<"ID: "<<vecProductos[i]<<" | "<<marcaAux.getNombre()<<" | "<< productoAux.getModelo()<<std::endl;
        std::cout<<"CANTIDAD: "<<vecUnidades[i]<<std::endl;
    }
    std::cout<<"IMPORTE: $"<<venta.getMontoCompra()<<endl;
    std::cout<<"METODO PAGO: "<<metodoPago<<endl;
    UsuarioArchivo arUsuario;
    Usuario vendedor;
    vendedor = arUsuario.leer(arUsuario.buscar(venta.getIdVendedor()));
    std::cout<<"VENDEDOR: "<<vendedor.getNombre()<<" "<<vendedor.getApellido()<<endl;
}

void VentaManager::ListarTodas()
{
    int cantidadRegistros = _archivo.getCantidadRegistros();
    int cantidadActivos = 0;
    for(int i = 0; i < cantidadRegistros; i++)
    {
        Venta reg;
        reg = _archivo.leer(i);
        if(reg.getActivo())
        {
            cantidadActivos ++;
        }
    }

    if(cantidadActivos <= 0)
    {
        mensajeListadoSinDatosEncontrados();
    }
    else
    {
        Venta *listadoVentas = new Venta [cantidadActivos];

        if(listadoVentas == nullptr)
        {
            cout << "Error al generar el listado";
            return;
        }

        int ultimaPos = 0;
        for(int i = 0; i < cantidadRegistros; i ++)
        {
            Venta reg;
            reg = _archivo.leer(i);
            if(reg.getActivo())
            {
                listadoVentas[ultimaPos] = reg;
                ultimaPos ++;
            }
        }
            std::cout << "Registros encontrados: " << cantidadActivos << std::endl;
            std::cout << std::endl;
            std::cout << std::left;
            std::cout << std::setw(4) << "Id";
            std::cout << std::setw(13) << "Cliente";
            std::cout << std::setw(12) << "Importe $";
            std::cout << std::setw(19) << "Forma Pago";
            std::cout << std::setw(11) << "Vendedor";
            std::cout << std::setw(13) << "F. Venta";
            std::cout << std::endl;
            std::cout << "-------------------------------------------------------------------------" << std::endl;

            for(int i = 0; i<cantidadActivos; i++)
            {
                std::cout << std::left;
                std::cout << std::setw(4) << listadoVentas[i].getIdPedido();
                std::cout << std::setw(13) << listadoVentas[i].getNroDocCliente();
                std::cout << std::setw(12) << listadoVentas[i].getMontoCompra();
                std::cout << std::setw(19) << metodoPagoAString(listadoVentas[i].getMetodoPago());
                std::cout << std::setw(11) << listadoVentas[i].getIdVendedor();
                std::cout << std::setw(13) << listadoVentas[i].getFecha().toString();
                std::cout << std::endl;
            }
            mensajeFinDelListado();
            delete[] listadoVentas;
    }
    rlutil::anykey();
}

void VentaManager::generarComprobante(Venta venta)
{

    std::string nombreArchivo = "/Venta"+std::to_string(venta.getIdPedido())+".txt";
    //char archivo [50];
    //strcpy(archivo, nombreArchivo.c_str());

    std::string directorio = "/Comprobantes";
    std::string rutaTxt = directorio + nombreArchivo;

    //std::string rutaCompleta = directorio + nombreArchivo;
    cout<<rutaTxt<<endl;

    const int* vecIdProducto = venta.getVecIdProducto();
    const int* vecUnidadesProducto = venta.getVecUnidadesxProducto();
    int cantidadProductos = venta.getCantidadProductos();

    FILE* archivoTxt = fopen(rutaTxt.c_str(), "ab");
    if (archivoTxt != nullptr)
    {
        fprintf(archivoTxt, "Información de venta:\n");
        fprintf(archivoTxt, "CLIENTE: %s\n", venta.getNroDocCliente().c_str());
        fprintf(archivoTxt, "FECHA COMPRA: %s\n", venta.getFecha().toString().c_str());
        for(int i = 0; i<cantidadProductos; i++)
        {
            ProductoArchivo arProducto;
            MarcaArchivo arMarca;
            Producto productoAux;
            productoAux = arProducto.leer(arProducto.buscar(vecIdProducto[i]));
            Marca marcaAux;
            marcaAux = arMarca.leer(arMarca.buscar(productoAux.getIdMarca()));
            std::string nombreString(marcaAux.getNombre());
            std::string productoString = nombreString + " | " + productoAux.getModelo();
            fprintf(archivoTxt, "%s\n", productoString.c_str());
            fprintf(archivoTxt, "UNIDADES: %d\n", vecUnidadesProducto[i]);
        }
        fprintf(archivoTxt, "IMPORTE FINAL:$ %f\n", venta.getMontoCompra());

        UsuarioArchivo arUsuario;
        Usuario vendedor;
        vendedor = arUsuario.leer(arUsuario.buscar(venta.getIdVendedor()));
        std::string nombreVendedor = (vendedor.getNombre());
        std::string apellidoVendedor = (vendedor.getApellido());

        std::string vendedorString = "VENDEDOR: " + nombreVendedor + " " + apellidoVendedor;
        fprintf(archivoTxt, "%s\n", vendedorString.c_str());
        fclose(archivoTxt);
    }

}

void VentaManager::Cargar()
{
    ProductoArchivo arProducto;
    if(arProducto.getCantidadRegistrosActivos() <= 0)
    {
        std::cout << std::endl;
        rlutil::setColor(rlutil::LIGHTRED);
        std::cout << "NO ES POSIBLE CARGAR LA VENTA. NO HAY NINGUN PRODUCTO REGISTRADO" << std::endl;
        rlutil::setColor(rlutil::WHITE);
        rlutil::anykey();
    }
    else
    {
        UsuarioActivo usuario;
        int idPedido = GenerarId();
        std::string nroDocCliente;
        Fecha fechaCompra;
        int vecIdProducto[10];
        int vecUnidadesxProducto[10];
        int cantidadProductos = 0;
        float montoCompra;
        int metodoPago;
        int idVendedor;
        bool activo = true;

        nroDocCliente = validarCliente();
        fechaCompra = Fecha().fechaActual();

        cantidadProductos = cargarProductos(vecIdProducto, vecUnidadesxProducto);

        for(int i = 0; i<cantidadProductos; i++)
        {
            int posicion = arProducto.buscar(vecIdProducto[i]);
            Producto producto;

            producto = arProducto.leer(posicion);

            float monto = producto.getPrecio() * vecUnidadesxProducto[i];
            montoCompra += monto;
        }

        idVendedor = usuario.getIdUsuarioActivo();
        std::cout<<"INGRESE EL METODO DE PAGO: 1. EFECTIVO | 2. TARJETA | 3. TRANSFERENCIA."<<std::endl;
        metodoPago = ingresoMetodoPagoConValidacion();
        Venta reg(idPedido, nroDocCliente, fechaCompra, vecIdProducto, vecUnidadesxProducto, cantidadProductos, montoCompra, metodoPago, idVendedor, activo);
        std::cout<<"HA CARGADO LA SIGUIENTE VENTA: "<<std::endl;
        Listar(reg);
        std::cout<<"QUIERE GUARDARLA? (SI | NO): "<<std::endl;
        std::string decision = ingresoDeDecisionConValidacion();

        if (decision == "SI")
        {
            if(_archivo.guardar(reg))
            {
                okMensajeCreacion();
                generarComprobante(reg);
                rlutil::anykey();
            }
            else
            {
                restaurarStock(vecIdProducto, vecUnidadesxProducto, cantidadProductos);
                errorMensajeCreacion();
                rlutil::anykey();
            }

        }
        else
        {
            restaurarStock(vecIdProducto, vecUnidadesxProducto, cantidadProductos);
        }
    }
}

void VentaManager::Anular()
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
                    const int* vecIdProductos = reg.getVecIdProducto();
                    const int* vecUnidadesXProducto = reg.getVecUnidadesxProducto();
                    int cantidadProductos = reg.getCantidadProductos();
                    restaurarStock(vecIdProductos, vecUnidadesXProducto, cantidadProductos);
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
                    ProductoManager managerProducto;
                    const int* vecIdProductos = reg.getVecIdProducto();
                    const int* vecUnidadesProductos = reg.getVecUnidadesxProducto();
                    int cantidadProductos = reg.getCantidadProductos();
                    for(int i = 0; i < cantidadProductos; i++)
                    {
                        managerProducto.RestarStock(vecIdProductos[i], vecUnidadesProductos[i]);
                    }
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

void VentaManager::hacerCopiaDeSeguridad()
{
    int cantidadRegs = _archivo.getCantidadRegistros();
    if(cantidadRegs <= 0)
    {
        errorMensajeCopiaDeSeguridadSinRegs();
        rlutil::anykey();
        return;
    }

    Venta *vec = new Venta[cantidadRegs];

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

void VentaManager::restaurarCopiaDeSeguridad()
{
    int cantidadRegs = _archivoBkp.getCantidadRegistros();

    if(cantidadRegs <= 0)
    {
        errorMensajeCopiaDeSeguridadSinRegs();
        rlutil::anykey();
        return;
    }

    Venta *vec = new Venta[cantidadRegs];
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
