#include<iostream>
#include "MarcaManager.h"
#include "../funciones.h"
#include <../rlutil.h>
#include "../mensajes.h"
#include "../validaciones.h"

using namespace std;

int MarcaManager::generarID()
{
    return _archivo.getCantidadDeRegistros()+1;
}

void MarcaManager::listar(Marca marca, int tipoListado)
{

    switch (tipoListado)
    {
    case 0:
        std::cout << "ID: " << marca.getID() << std::endl;
        std::cout << "Nombre: " << marca.getNombre() << std::endl;
        break;
    case 1:
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(5) << marca.getID();
        std::cout << std::setw(33)<<  marca.getNombre();
        break;
    }
}

void MarcaManager::listarXID()
{
    int id;

    cout<<"INGRESE EL ID: ";
    cin>>id;
    cin.ignore();

    int pos = _archivo.buscar(id);
    if(pos >= 0)
    {
        Marca reg;
        reg = _archivo.leer(pos);
        listar(reg, 0);
    }
    else
    {
        registroNoEncontradoMensaje();
    }
}

void MarcaManager::listarXNombre()
{

    cout<<"INGRESE EL NOMBRE: ";
    std::string nombre = ingresoDeMarcaConValidacion();

    int pos = _archivo.buscar(nombre);
    if(pos >= 0)
    {
        Marca reg;
        reg = _archivo.leer(pos);
        listar(reg, 0);
    }
    else
    {
        registroNoEncontradoMensaje();
    }
    rlutil::anykey();

}

void MarcaManager::listarActivas()
{
    int cantidadRegistros = _archivo.getCantidadDeRegistros();
    int cantidadActivas = 0;
    for(int i = 0; i<cantidadRegistros; i++)
    {
        Marca reg;
        reg = _archivo.leer(i);
        if(reg.getActivo())
        {
            cantidadActivas ++;
        }
    }

    if(cantidadActivas > 0)
    {
        std::cout << "Registros encontrados: " << cantidadActivas << std::endl;
        std::cout << std::endl;
        std::cout << "MARCAS ACTIVAS" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(5) << "ID";
        std::cout << std::setw(33)<<  "MARCA";
        std::cout << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        for (int i = 0; i<cantidadRegistros; i++)
        {
            Marca reg;
            reg = _archivo.leer(i);
            if(reg.getActivo())
            {
                listar(reg,1);
            }
        }
        mensajeFinDelListado();
    }
    else
    {
        mensajeListadoSinDatosEncontrados();
    }

    rlutil::anykey();
}

void MarcaManager::listarInactivas()
{

    int cantidadRegistros = _archivo.getCantidadDeRegistros();
    int cantidadInactivas = 0;
    for(int i = 0; i<cantidadRegistros; i++)
    {
        Marca reg;
        reg = _archivo.leer(i);
        if(!reg.getActivo())
        {
            cantidadInactivas ++;
        }
    }

    if(cantidadInactivas > 0)
    {
        std::cout << "Registros encontrados: " << cantidadInactivas << std::endl;
        std::cout << std::endl;
        std::cout << "MARCAS INACTIVAS" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(5) << "ID";
        std::cout << std::setw(33)<<  "MARCA";
        std::cout << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        for (int i = 0; i<cantidadRegistros; i++)
        {
            Marca reg;
            reg = _archivo.leer(i);
            if(!reg.getActivo())
            {
                listar(reg,1);
            }
        }
        mensajeFinDelListado();
    }
    else
    {
        mensajeListadoSinDatosEncontrados();
    }

    rlutil::anykey();
}

void MarcaManager::cargar()
{
    cout<<"INGRESE EL NOMBRE DE LA MARCA: ";
    std::string nombre = ingresoDeMarcaConValidacion();

    if(_archivo.buscar(nombre)<0)
    {
        int ID = generarID();
        bool activo = true;
        Marca reg(ID,nombre.c_str(), activo);
        cout<<"CARGO LA SIGUIENTE MARCA: "<<endl;
        listar(reg,0);
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
    }
    else
    {
        Marca reg;
        reg = _archivo.leer(_archivo.buscar(nombre));
        existeRegistroMensaje();
        listar(reg,0);

    }
    rlutil::anykey();


}

int MarcaManager::cargarDesdeProducto(std::string nombreMarca)
{
    if(_archivo.buscar(nombreMarca)>=0)
    {
        Marca reg;
        reg = _archivo.leer(_archivo.buscar(nombreMarca));
        return reg.getID();
    }

    int ID = generarID();
    bool activo = true;
    Marca reg(ID,nombreMarca.c_str(), activo);
    listar(reg, 0);
    cout<<"CONTINUAR? (SI | NO): ";
    std::string decision;
    decision = ingresoDeDecisionConValidacion();
    if (decision == "SI")
    {
        if(_archivo.guardar(reg))
        {
            okMensajeCreacion();
            return ID;
        }
        else
        {
            errorMensajeCreacion();
            ID = -1;
            return ID;
        }
    }
    else if(decision == "NO")
    {
        reg = Marca();
        ID = -1;
        return ID;
    }

}

void MarcaManager::modificar()
{
    int opc;
    cout<<"BUSCAR MARCA A MODIFICAR"<<endl;
    cout<<"1 -- POR ID  // 2 -- POR NOMBRE: ";
    opc = ingresoOpcSimpleConValidacion();

    if(opc == 1)
    {
        modificarXID();
    }
    else if(opc == 2)
    {
        modificarXNombre();
    }
    rlutil::anykey();
}

void MarcaManager::modificarXID()
{
    int id, pos;

    cout << "INGRESE EL ID: ";
    cin >> id;
    pos = _archivo.buscar(id);
    if(pos>=0)
    {
        Marca reg;
        reg = _archivo.leer(pos);
        listar(reg, 0);

        cout<<"INGRESE EL NOMBRE DE LA MARCA: ";
        std::string nombre = ingresoDeMarcaConValidacion();
        reg.setNombre(nombre.c_str());

        cout<<"MODIFICO LA SIGUIENTE MARCA: "<<endl;
        listar(reg, 0);
        cout<<"CONTINUAR? (SI | NO): ";
        std::string opc;
        opc = ingresoDeDecisionConValidacion();
        if (opc == "SI")
        {
            if(_archivo.guardar(reg, pos))
            {
                okMensajeModificacion();
                listar(_archivo.leer(pos), 0);
            }
            else
            {
                errorMensajeModificacion();
            }
        }

    }
    else
    {
        registroNoEncontradoMensaje();
    }
    rlutil::anykey();

}

void MarcaManager::modificarXNombre()
{
    {
        int pos;
        std::string nombre;

        cout << "INGRESE EL NOMBRE: ";
        nombre = ingresoDeMarcaConValidacion();
        pos = _archivo.buscar(nombre);
        if(pos>=0)
        {
            Marca reg;
            reg = _archivo.leer(pos);
            listar(reg,0);

            cout<<"INGRESE EL NOMBRE DE LA MARCA: ";
            std::string nombreModificado = ingresoDeMarcaConValidacion();
            reg.setNombre(nombreModificado.c_str());

            cout<<"MODIFICO LA SIGUIENTE MARCA: "<<endl;
            listar(reg,0);
            cout<<"CONTINUAR? (SI | NO): ";
            std::string opc;
            opc = ingresoDeDecisionConValidacion();
            if (opc == "SI")
            {
                if(_archivo.guardar(reg, pos))
                {
                    okMensajeModificacion();
                    listar(_archivo.leer(pos),0);
                }
                else
                {
                    errorMensajeModificacion();
                }
            }

        }
        else
        {
            registroNoEncontradoMensaje();
        }
    }
    rlutil::anykey();

}

void MarcaManager::hacerCopiaSeguridad()
{

    int cantidadRegs = _archivo.getCantidadDeRegistros();

    if(cantidadRegs <= 0)
    {
        errorMensajeCopiaDeSeguridadSinRegs();
        rlutil::anykey();
        return;
    }

    Marca *vec = new Marca[cantidadRegs];

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

void MarcaManager::restaurarCopiaSeguridad()
{
    int cantidadRegs = _archivoBkp.getCantidadDeRegistros();

    if(cantidadRegs <= 0)
    {
        errorMensajeCopiaDeSeguridadSinRegs();
        rlutil::anykey();
        return;
    }

    Marca *vec = new Marca[cantidadRegs];
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

void MarcaManager::eliminar()
{

    Marca reg;
    int id, posicion;
    cout<<"ID MARCA A ELIMINAR: ";
    cin>>id;
    cin.ignore();
    cout<<endl;

    posicion = _archivo.buscar(id);
    if(posicion >= 0)
    {
        ProductoArchivo arProductos;
        reg = _archivo.leer(posicion);

        if(!reg.getActivo())
        {
            cout<<"EL ID SELECCIONADO YA SE ENCUENTRA DADO DE BAJA"<<endl;
        }

        int marcaAsignada = 0;
        int cantProductos = arProductos.getCantidadDeRegistros();
        ProductoManager managerProducto;
        for(int i = 0; i<cantProductos; i++)
        {
            Producto prodAux;
            prodAux = arProductos.leer(i);
            if(reg.getID() == prodAux.getIdMarca() && prodAux.getActivo())
            {
                if(!marcaAsignada)
                {
                    cout<<"NO ES POSIBLE ELIMINAR LA MARCA SELECCIONADA. LA MISMA ESTA ASIGNADA A LOS SIGUIENTES PRODUCTOS:"<<endl;
                    managerProducto.Listar(prodAux,0);
                    marcaAsignada = 1;
                }
                else
                {
                    managerProducto.Listar(prodAux,0);
                }
            }
        }
        if(!marcaAsignada && reg.getActivo())
        {
            cout<<"ELIMINARA LA SIGUIENTE MARCA: "<<endl;
            listar(reg,0);
            cout<<"CONTINUAR? (SI | NO): ";
            std::string opc;
            opc = ingresoDeDecisionConValidacion();
            if (opc == "SI")
            {
                reg.setActivo(false);
                if(_archivo.guardar(reg, posicion))
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
        registroNoEncontradoMensaje();
    }
    rlutil::anykey();
}

void MarcaManager::reactivar()
{
    Marca reg;
    int id, posicion;
    cout<<"ID MARCA A REACTIVAR: ";
    cin>>id;
    cin.ignore();
    cout<<endl;

    posicion = _archivo.buscar(id);

    if(posicion >= 0)
    {
        reg = _archivo.leer(posicion);
        if(!reg.getActivo())
        {
            cout<<"REACTIVARA LA SIGUIENTE MARCA: "<<endl;
            listar(reg,0);
            cout<<"CONTINUAR? (SI | NO): ";
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
            cout<<"LA MARCA INGRESADA NO SE ENCUENTRA ELIMINADA"<<endl;
        }
    }
    else
    {
        registroNoEncontradoMensaje();
    }
    rlutil::anykey();
}
