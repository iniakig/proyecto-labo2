#include<iostream>
#include <cstdio>
#include <iomanip>

#include "../mensajes.h"
#include "../validaciones.h"

using namespace std;

#include "VentaManager.h"
#include "Empresa.h"
#include "EmpresaManager.h"

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

void VentaManager::Listar(Venta venta, int tipoListado)
{
    switch (tipoListado)
    {
    case 0:
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
        std::cout<<"IMPORTE: $"<< std::fixed << std::setprecision(2)<<venta.getMontoCompra()<<endl;
        std::cout<<"METODO PAGO: "<<metodoPago<<endl;
        UsuarioArchivo arUsuario;
        Usuario vendedor;
        vendedor = arUsuario.leer(arUsuario.buscar(venta.getIdVendedor()));
        std::cout<<"VENDEDOR: "<<vendedor.getNombre()<<" "<<vendedor.getApellido()<<endl;
    }
    break;
    case 1:
    {
        std::cout << std::left;
        std::cout << std::setw(4) << venta.getIdPedido();
        std::cout << std::setw(13) << venta.getNroDocCliente();
        std::cout << std::setw(12) << std::fixed << std::setprecision(2)<<venta.getMontoCompra();
        std::cout << std::setw(19) << metodoPagoAString(venta.getMetodoPago());
        std::cout << std::setw(11) << venta.getIdVendedor();
        std::cout << std::setw(13) << venta.getFecha().toString();
        std::cout << std::endl;
    }
    break;
    default:
        break;
    }
}

void VentaManager::ListarTodasDetalle()
{
    int cantidadRegistros = _archivo.getCantidadRegistros();

    if(cantidadRegistros <= 0)
    {
        mensajeListadoSinDatosEncontrados();
    }
    else
    {
        for (int i = 0; i < cantidadRegistros; i++)
        {
            Venta reg;
            reg = _archivo.leer(i);
            if(reg.getActivo())
            {
                Listar(reg, 0);
            }
        }
        mensajeFinDelListado();
    }
    rlutil::anykey();



}

void VentaManager::ListarTodasResumen()
{
    int cantidadRegistros = _archivo.getCantidadRegistros();

    if(cantidadRegistros <= 0)
    {
        mensajeListadoSinDatosEncontrados();
    }
    else
    {
        rlutil::cls();
        std::cout << "RESUMEN VENTAS" << std::endl;
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        std::cout << std::left;
        std::cout << std::setw(4) << "Id";
        std::cout << std::setw(13) << "Cliente";
        std::cout << std::setw(12) << "Importe $";
        std::cout << std::setw(19) << "Forma Pago";
        std::cout << std::setw(11) << "Vendedor";
        std::cout << std::setw(13) << "F. Venta";
        std::cout << std::endl;
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        for (int i = 0; i < cantidadRegistros; i++)
        {
            Venta reg;
            reg = _archivo.leer(i);

            if(reg.getActivo())
            {
                Listar(reg, 1);
            }
        }
        mensajeFinDelListado();
    }
    rlutil::anykey();
}

void VentaManager::ListarVentasAnuladas()
{
    int cantidadRegistros = _archivo.getCantidadRegistros();
    int cantidadAnuladas = 0;

    for(int i = 0; i < cantidadRegistros; i++)
    {
        Venta reg;
        reg = _archivo.leer(i);
        if(!reg.getActivo())
        {
            cantidadAnuladas ++;
        }
    }

    if(cantidadAnuladas <= 0)
    {
        mensajeListadoSinDatosEncontrados();
    }
    else
    {

        Venta *ventasAnuladas = new Venta[cantidadAnuladas];

        if (ventasAnuladas == nullptr)
        {
            std::cout << "Ocurri� un error al visualizar el listado" << std::endl;
            return;
        }

        int ultimaPosicionGrabada = 0;

        std::cout << std::left;
        std::cout << std::setw(4) << "Id";
        std::cout << std::setw(13) << "Cliente";
        std::cout << std::setw(12) << "Importe $";
        std::cout << std::setw(19) << "Forma Pago";
        std::cout << std::setw(11) << "Vendedor";
        std::cout << std::setw(13) << "F. Venta";
        std::cout << std::endl;
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        for(int i = 0; i < cantidadRegistros; i ++)
        {
            Venta reg;
            reg = _archivo.leer(i);
            if(!reg.getActivo())
            {
                ventasAnuladas[ultimaPosicionGrabada] = reg;
                Listar(reg, 1);
            }
        }
        delete [] ventasAnuladas;
        mensajeFinDelListado();
    }
    rlutil::anykey();
}

void VentaManager::ListarVentas()
{
    int opcion = -1;

    do
    {
        rlutil::cls();
        std::cout << "ELIJA EL TIPO DE LISTADO" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. LISTAR TODAS LAS VENTAS DETALLADAS" << std::endl;
        std::cout << "2. LISTAR RESUMEN DE VENTAS" << std::endl;
        std::cout << "3. LISTAR VENTAS ANULADAS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "0. VOLVER AL MEN� DE GESTI�N DE VENTAS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "OPCI�N SELECCIONADA: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion)
        {
        case 0:
            break;
        case 1:
            //std::cout << std::endl;
            ListarTodasDetalle();
            break;
        case 2:
            //std::cout << std::endl;
            ListarTodasResumen();
            break;
        case 3:
            ListarVentasAnuladas();
            break;
        case 4:
            //std::cout << std::endl;
            break;
        case 5:
            break;
        default:
            std::cout << "La opci�n seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}

void VentaManager::generarComprobante(Venta venta)
{

    std::string nombreArchivo = "/Venta"+std::to_string(venta.getIdPedido())+"_"+venta.getFecha().toString("DD-MM-YYYY")+".txt";
    std::string directorio = "./comprobantes";
    std::string rutaTxt = directorio + nombreArchivo;

    const int* vecIdProducto = venta.getVecIdProducto();
    const int* vecUnidadesProducto = venta.getVecUnidadesxProducto();
    int cantidadProductos = venta.getCantidadProductos();

    FILE* archivoTxt = fopen(rutaTxt.c_str(), "ab");
    if (archivoTxt != nullptr)
    {
        fprintf(archivoTxt, "COMPROBANTE DE VENTA\n");
        fprintf(archivoTxt, "(Documento no v�lido como factura)\n");
        fprintf(archivoTxt, "------------------------------------------------------------------------\n");

        fprintf(archivoTxt, "CLIENTE: %s\n", venta.getNroDocCliente().c_str());
        fprintf(archivoTxt, "FECHA COMPRA: %s\n", venta.getFecha().toString().c_str());
        fprintf(archivoTxt, "PRODUCTOS: \n");
        fprintf(archivoTxt, "\n");
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
            fprintf(archivoTxt, "   %s\n", productoString.c_str());
            fprintf(archivoTxt, "   UNIDADES: %d\n", vecUnidadesProducto[i]);
            fprintf(archivoTxt, "\n");
        }
        fprintf(archivoTxt, "------------------------------------------------------------------------\n");
        fprintf(archivoTxt, "IMPORTE FINAL: $%.2f\n", venta.getMontoCompra());

        UsuarioArchivo arUsuario;
        Usuario vendedor;
        vendedor = arUsuario.leer(arUsuario.buscar(venta.getIdVendedor()));
        std::string nombreVendedor = (vendedor.getNombre());
        std::string apellidoVendedor = (vendedor.getApellido());

        std::string vendedorString = "VENDEDOR: " + nombreVendedor + " " + apellidoVendedor;
        fprintf(archivoTxt, "%s\n", vendedorString.c_str());


        // Datos de empresa
        Empresa empresa;
        EmpresaArchivo empresaArchivo;
        empresa = empresaArchivo.leer();

        std::string razonSocial(empresa.getRazonSocial());
        std::string cuit(empresa.getNroDocumento());
        std::string domicilio(empresa.getDomicilio());
        std::string localidad(empresa.getLocalidad());
        std::string provincia(empresa.getProvinciaDescripcion());
        std::string domicilioCompleto = domicilio + " | " + localidad + " | " + provincia;

        fprintf(archivoTxt, "------------------------------------------------------------------------\n");
        fprintf(archivoTxt, "%s\n", razonSocial.c_str());
        fprintf(archivoTxt, "CUIT %s\n", cuit.c_str());
        fprintf(archivoTxt, "%s\n", domicilioCompleto.c_str());

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
        Listar(reg,0);
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
    setPermisos(1, 1, 0);


    UsuarioActivo usuario;
    int rolUsuario = usuario.getRolUsuarioActivo();

    if(validarRol(_permisos, rolUsuario))
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
                Listar(reg,0);
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
        }
    }
    else
    {
        mensajeAccesoRestringido();
    }
    rlutil::anykey();


}

void VentaManager::Reactivar()
{
    setPermisos(1, 1, 0);


    UsuarioActivo usuario;
    int rolUsuario = usuario.getRolUsuarioActivo();

    if(validarRol(_permisos, rolUsuario))
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
                Listar(reg,0);
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
    else
    {
        mensajeAccesoRestringido();
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

void VentaManager::recaudacionAnual()
{
    setPermisos(1,1,0);
    UsuarioActivo usuario;
    int rolUsuario = usuario.getRolUsuarioActivo();

    if(validarRol(_permisos, rolUsuario))
    {
        rlutil::cls();
        std::cout << "RECAUDACI�N ANUAL" << std::endl;
        std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "Ingrese el a�o de consulta: ";

        int anio;
        std::cin >> anio;
        bool tieneRegistros = false;

        int cantidadDeVentas = _archivo.getCantidadRegistros();
        Venta* listaDeVentas = new Venta[cantidadDeVentas];

        _archivo.leer(listaDeVentas, cantidadDeVentas);

        float meses[12] = {};

        for (int i = 0; i < cantidadDeVentas; i++)
        {
            if (listaDeVentas[i].getFecha().getAnio() == anio && listaDeVentas[i].getActivo())
            {
                int mes = listaDeVentas[i].getFecha().getMes();
                meses[mes - 1] += listaDeVentas[i].getMontoCompra();
                tieneRegistros = true;
            }
        }

        std::string mesesDescripcion[12] =
        {
            "Enero",
            "Febrero",
            "Marzo",
            "Abril",
            "Mayo",
            "Junio",
            "Julio",
            "Agosto",
            "Septiembre",
            "Octubre",
            "Noviembre",
            "Diciembre"
        };

        if (tieneRegistros)
        {
            std::cout << std::endl;
            std::cout << "-----------------------------------" << std::endl;
            std::cout << "   MES              IMPORTE" << std::endl;
            std::cout << "-----------------------------------" << std::endl;
            std::cout << "  " << mesesDescripcion[0] << "             $" << std::fixed << std::setprecision(2)<< meses[0] << std::endl;
            std::cout << "  " << mesesDescripcion[1] << "           $" << std::fixed << std::setprecision(2)<< meses[1] << std::endl;
            std::cout << "  " << mesesDescripcion[2] << "             $" << std::fixed << std::setprecision(2)<< meses[2] << std::endl;
            std::cout << "  " << mesesDescripcion[3] << "             $" << std::fixed << std::setprecision(2)<< meses[3] << std::endl;
            std::cout << "  " << mesesDescripcion[4] << "              $" << std::fixed << std::setprecision(2)<< meses[4] << std::endl;
            std::cout << "  " << mesesDescripcion[5] << "             $" << std::fixed << std::setprecision(2)<< meses[5] << std::endl;
            std::cout << "  " << mesesDescripcion[6] << "             $" << std::fixed << std::setprecision(2)<< meses[6] << std::endl;
            std::cout << "  " << mesesDescripcion[7] << "            $" << std::fixed << std::setprecision(2)<< meses[7] << std::endl;
            std::cout << "  " << mesesDescripcion[8] << "        $" << std::fixed << std::setprecision(2)<< meses[8] << std::endl;
            std::cout << "  " << mesesDescripcion[9] << "           $" << std::fixed << std::setprecision(2)<< meses[9] << std::endl;
            std::cout << "  " << mesesDescripcion[10] << "         $" << std::fixed << std::setprecision(2)<< meses[10] << std::endl;
            std::cout << "  " << mesesDescripcion[11] << "         $" << std::fixed << std::setprecision(2)<< meses[11] << std::endl;
            std::cout << "-----------------------------------" << std::endl;

            mensajeFinDelListado();
        }
        else
        {
            mensajeListadoSinDatosEncontrados();
        }

        delete[] listaDeVentas;
    }
    else
    {
        mensajeAccesoRestringido();
    }
    rlutil::anykey();
}

void VentaManager::vendedorConMasVentasConcretadas()
{
    rlutil::cls();
    std::cout << "VENDEDOR CON M�S VENTAS CONCRETADAS POR IMPORTE" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Ingrese el a�o de consulta: ";

    int anio;
    std::cin >> anio;
    bool tieneRegistros = false;

    int cantidadDeVentas = _archivo.getCantidadRegistros();
    Venta* listaDeVentas = new Venta[cantidadDeVentas];

    _archivo.leer(listaDeVentas, cantidadDeVentas);

    Usuario usuario;
    UsuarioArchivo usuarioArchivo;
    int cantidadDeVendedores = usuarioArchivo.getCantidadDeUsuarios();
    float* montosPorVendedor = new float[cantidadDeVendedores];

    for (int i = 0; i < cantidadDeVendedores; i++)
    {
        montosPorVendedor[i] = 0;
    }

    for (int i = 0; i < cantidadDeVentas; i++)
    {
        if (listaDeVentas[i].getFecha().getAnio() == anio && listaDeVentas[i].getActivo())
        {
            int idVendedor = listaDeVentas[i].getIdVendedor();
            montosPorVendedor[idVendedor - 1] += listaDeVentas[i].getMontoCompra();
            tieneRegistros = true;
        }
    }

    if (tieneRegistros)
    {
        int posicionMayor = 0;
        for (int i = 0; i < cantidadDeVendedores; i++)
        {
            if (montosPorVendedor[i] > montosPorVendedor[posicionMayor])
            {
                posicionMayor = i;
            }
        }

        int posicionMayorVendedor = usuarioArchivo.buscar(posicionMayor+1);
        usuario = usuarioArchivo.leer(posicionMayorVendedor);
        std::string aliasMayorVendedor(usuario.getAlias());

        std::cout << std::endl;
        rlutil::setColor(rlutil::LIGHTGREEN);
        std::cout << "El vendedor con mayores ventas es: " << aliasMayorVendedor << std::endl;
        rlutil::setColor(rlutil::WHITE);
        std::cout << std::endl;

        std::cout << "---------------------------------------------------------------" << std::endl;
        for (int i = 0; i < cantidadDeVendedores; i++)
        {
            if (montosPorVendedor[i] > 0)
            {
                std::cout << "ID del vendedor: " << i + 1 << std::endl;

                int posicion = usuarioArchivo.buscar(i + 1);
                usuario = usuarioArchivo.leer(posicion);
                std::string alias(usuario.getAlias());

                std::cout << "ALIAS: " << alias << std::endl;
                std::cout << "MONTO VENDIDO: $" << montosPorVendedor[i] << std::endl;
                std::cout << "---------------------------------------------------------------" << std::endl;
            }
        }
        mensajeFinDelListado();
    }
    else
    {
        mensajeListadoSinDatosEncontrados();
    }

    rlutil::anykey();
    delete[] listaDeVentas;
    delete[] montosPorVendedor;
}

void VentaManager::ventasTotalesPorVendedor()
{
    setPermisos(1,1,0);
    UsuarioActivo usuario;

    int rolUsuario = usuario.getRolUsuarioActivo();

    if(validarRol(_permisos, rolUsuario))
    {
        Fecha fechaActual= fechaActual.fechaActual();
        Usuario usuario;
        UsuarioArchivo arUsuario;
        int cantUsuarios=arUsuario.getCantidadDeUsuarios();
        Venta venta;
        int cantVentas=_archivo.getCantidadRegistros();
        rlutil::cls();
        std::cout<<"                CANTIDAD E IMPORTE DE VENTAS POR VENDEDOR"<<std::endl;
        std::cout << "------------------------------------------------------------------" << std::endl;
        for(int i=0; i<cantUsuarios; i++)
        {
            usuario =arUsuario.leer(i);
            float importeMensual=0;
            int cantVentasMensual=0;
            for(int a=0; a<cantVentas; a++)
            {
                venta=_archivo.leer(a);
                if(usuario.getEstado()==true && venta.getFecha().getMes()== fechaActual.getMes() && venta.getFecha().getAnio()==fechaActual.getAnio() && venta.getActivo())
                {
                    if(usuario.getId()==venta.getIdVendedor())
                    {
                        importeMensual+=venta.getMontoCompra();
                        cantVentasMensual++;
                    }
                }
            }

            if(cantVentasMensual > 0)
            {
                std::cout<<"ID VENDEDOR: "<<usuario.getId()<<std::endl;
                std::cout<<"NOMBRE Y APELLIDO: "<<usuario.getNombre()<<" "<<usuario.getApellido()<<std::endl;
                std::cout<<"CANTIDAD DE VENTAS EN EL MES: "<<cantVentasMensual<<std::endl;
                std::cout<<"IMPORTE MENSUAL TOTAL: "<< std::fixed << std::setprecision(2)<< importeMensual<<std::endl;
                std::cout<<std::endl;
            }
        }
        mensajeFinDelListado();
    }
    else
    {
        mensajeAccesoRestringido();
    }
    rlutil::anykey();

}

void VentaManager::resumenVentasDiarias()
{
    rlutil::cls();
    std::cout<<std::endl;
    std::cout<<"----- DETALLE VENTAS DIARIAS -----"<<std::endl;
    std::cout<<std::endl;
    std::cout << "1. LISTAR LAS VENTAS DEL DIA DE HOY" << std::endl;
    std::cout << "2. LISTAR VENTAS DE DIAS ANTERIORES" << std::endl;
    int opcion;
    opcion = ingresoOpcSimpleConValidacion();

    if(opcion == 1)
    {
        Fecha fechaActual;
        fechaActual = Fecha().fechaActual();
        int cantidadVentasValidas = 0;

        int cantidadVentas = _archivo.getCantidadRegistros();
        for(int i = 0; i<cantidadVentas; i++)
        {
            Venta reg;
            reg = _archivo.leer(i);
            Fecha fechaVenta;
            fechaVenta = reg.getFecha();

            if(fechaVenta.getDia() == fechaActual.getDia() && fechaVenta.getMes() == fechaActual.getMes() && fechaVenta.getAnio() == fechaActual.getAnio() && reg.getActivo())
            {
                cantidadVentasValidas ++;
            }
        }

        if(cantidadVentasValidas > 0)
        {
            rlutil::cls();
            float montoAcumulado = 0;
            std::cout<<"----- VENTAS DEL DIA "<<fechaActual.toString()<<" -----"<<std::endl;
            std::cout<<std::endl;
            std::cout << std::left;
            std::cout << std::setw(4) << "Id";
            std::cout << std::setw(13) << "Cliente";
            std::cout << std::setw(12) << "Importe $";
            std::cout << std::setw(19) << "Forma Pago";
            std::cout << std::setw(11) << "Vendedor";
            std::cout << std::setw(13) << "F. Venta";
            std::cout << std::endl;
            std::cout << "-------------------------------------------------------------------------" << std::endl;

            for(int i = 0; i<cantidadVentas; i++)
            {
                Venta reg;
                reg = _archivo.leer(i);
                Fecha fechaVenta;
                fechaVenta = reg.getFecha();

                if(fechaVenta.getDia() == fechaActual.getDia() && fechaVenta.getMes() == fechaActual.getMes() && fechaVenta.getAnio() == fechaActual.getAnio() && reg.getActivo())
                {
                    Listar(reg, 1);
                    montoAcumulado += reg.getMontoCompra();
                }
            }
            rlutil::setColor(rlutil::GREEN);
            std::cout<<std::endl;
            std::cout << "IMPORTE TOTAL VENDIDO $"<< std::fixed << std::setprecision(2)<< montoAcumulado << std::endl;
            rlutil::setColor(rlutil::WHITE);
            std::cout << "-------------------------------------------------------------------------" << std::endl;
            mensajeFinDelListado();
        }
        else
        {
            mensajeListadoSinDatosEncontrados();
        }
        rlutil::anykey();
    }
    else
    {
        rlutil::cls();
        int dia, mes, anio;
        std::cout << "INGRESE EL DIA: ";
        std::cin >> dia;
        std::cout << "INGRESE EL MES: ";
        std::cin >> mes;
        std::cout << "INGRESE EL A�O: ";
        std::cin >> anio;
        cin.ignore();

        Fecha fechaSeleccionada(dia, mes, anio);

        if(fechaSeleccionada.getAnio() == 1900)
        {
            std::cout << "LA FECHA INGRESADA ES INVALIDA.";
        }
        else
        {
            int cantidadVentasValidas = 0;
            int cantidadVentas = _archivo.getCantidadRegistros();

            for (int i = 0; i<cantidadVentas; i ++)
            {
                Venta reg;
                reg = _archivo.leer(i);
                Fecha fechaVenta = reg.getFecha();

                if(fechaSeleccionada.getDia() == fechaVenta.getDia() && fechaSeleccionada.getMes() == fechaVenta.getMes() && fechaSeleccionada.getAnio() == fechaVenta.getAnio() && reg.getActivo())
                {
                    cantidadVentasValidas ++;
                }
            }



            if(cantidadVentasValidas > 0)
            {
                rlutil::cls();
                float montoAcumulado = 0;
                std::cout<<"----- VENTAS DEL DIA "<<fechaSeleccionada.toString()<<" -----"<<std::endl;
                std::cout<<std::endl;
                std::cout << std::left;
                std::cout << std::setw(4) << "Id";
                std::cout << std::setw(13) << "Cliente";
                std::cout << std::setw(12) << "Importe $";
                std::cout << std::setw(19) << "Forma Pago";
                std::cout << std::setw(11) << "Vendedor";
                std::cout << std::setw(13) << "F. Venta";
                std::cout << std::endl;
                std::cout << "-------------------------------------------------------------------------" << std::endl;
                for(int i = 0; i<cantidadVentas; i++)
                {
                    Venta reg;
                    reg = _archivo.leer(i);
                    Fecha fechaVenta;
                    fechaVenta = reg.getFecha();

                    if(fechaVenta.getDia() == fechaSeleccionada.getDia() && fechaVenta.getMes() == fechaSeleccionada.getMes() && fechaVenta.getAnio() == fechaSeleccionada.getAnio() && reg.getActivo())
                    {
                        Listar(reg, 1);
                        montoAcumulado += reg.getMontoCompra();
                    }
                }
                rlutil::setColor(rlutil::GREEN);
                std::cout<<std::endl;
                std::cout << "IMPORTE TOTAL VENDIDO $"<< std::fixed << std::setprecision(2)<< montoAcumulado << std::endl;
                rlutil::setColor(rlutil::WHITE);
                std::cout << "-------------------------------------------------------------------------" << std::endl;
                mensajeFinDelListado();

            }
            else
            {
                mensajeListadoSinDatosEncontrados();
            }
        }
    }
    rlutil::anykey();

}

void VentaManager::setPermisos(bool adm, bool sup, bool ven)
{
    _permisos[0] = adm;
    _permisos[1] = sup;
    _permisos[2] = ven;
}
