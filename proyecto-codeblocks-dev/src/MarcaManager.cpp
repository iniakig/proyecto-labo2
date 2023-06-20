#include<iostream>
#include "MarcaManager.h"
#include "../funciones.h"
#include <../rlutil.h>

using namespace std;


int MarcaManager::generarID()
{
    return _archivo.getCantidadDeRegistros()+1;
}

void MarcaManager::listar(Marca marca)
{
    cout<<"ID: "<<marca.getID()<<endl;
    cout<<"NOMBRE: "<<marca.getNombre()<<endl;
    cout<<"ESTADO: :"<<marca.getActivo()<<endl;
    rlutil::anykey();
}

void MarcaManager::listarXID()
{
    int id;

    cout<<"INGRESE EL ID: ";
    cin>>id;

    int pos = _archivo.buscar(id);
    if(pos >= 0)
    {
        Marca reg;
        reg = _archivo.leer(pos);
        listar(reg);
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
        listar(reg);
    }
    else
    {
        registroNoEncontradoMensaje();
    }
    rlutil::anykey();

}
void MarcaManager::listarTodos()
{
    int cantidadRegistros = _archivo.getCantidadDeRegistros();

    for (int i = 0; i<cantidadRegistros; i++)
    {
        Marca reg;
        reg = _archivo.leer(i);
        listar(reg);
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
        listar(reg);
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
        listar(reg);

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
    cout<<"CARGO LA SIGUIENTE MARCA: "<<endl;
    cout<<"ID: "<<reg.getID()<<endl;
    cout<<"NOMBRE: "<<reg.getNombre()<<endl;
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
        listar(reg);

        cout<<"INGRESE EL NOMBRE DE LA MARCA: ";
        std::string nombre = ingresoDeMarcaConValidacion();
        reg.setNombre(nombre.c_str());

        cout<<"MODIFICO LA SIGUIENTE MARCA: "<<endl;
        listar(reg);
        cout<<"GUARDAR? 1--SI // 2--NO: ";
        int opc;
        opc = ingresoOpcSimpleConValidacion();
        if(opc == 1)
        {
            if(_archivo.guardar(reg, pos))
            {
                okMensajeModificacion();
                listar(_archivo.leer(pos));
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
            listar(reg);

            cout<<"INGRESE EL NOMBRE DE LA MARCA: ";
            std::string nombreModificado = ingresoDeMarcaConValidacion();
            reg.setNombre(nombreModificado.c_str());

            cout<<"MODIFICO LA SIGUIENTE MARCA: "<<endl;
            listar(reg);
            cout<<"GUARDAR? 1--SI // 2--NO: ";
            int opc;
            opc = ingresoOpcSimpleConValidacion();
            if(opc == 1)
            {
                if(_archivo.guardar(reg, pos))
                {
                    okMensajeModificacion();
                    listar(_archivo.leer(pos));
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

    Marca *vec = new Marca[cantidadRegs];

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
    rlutil::anykey();
}

void MarcaManager::restaurarCopiaSeguridad()
{
    int cantidadRegs = _archivoBkp.getCantidadDeRegistros();

    Marca *vec = new Marca[cantidadRegs];
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
    rlutil::anykey();
}

void MarcaManager::eliminar()
{

    Marca reg;
    int id, posicion;
    cout<<"ID MARCA A ELIMINAR: ";
    cin>>id;
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
                    managerProducto.Listar(prodAux);
                    marcaAsignada = 1;
                }
                else
                {
                    managerProducto.Listar(prodAux);
                }
            }
        }
        if(!marcaAsignada && reg.getActivo())
        {
            cout<<"ELIMINARA LA SIGUIENTE MARCA: "<<endl;
            listar(reg);
            cout<<"CONFIRMAR? 1--SI // 2--NO: ";
            int opc;
            opc = ingresoOpcSimpleConValidacion();
            if(opc == 1)
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
    cout<<endl;

    posicion = _archivo.buscar(id);

    if(posicion >= 0)
    {
        reg = _archivo.leer(posicion);
        if(!reg.getActivo())
        {
            cout<<"REACTIVARA LA SIGUIENTE MARCA: "<<endl;
            listar(reg);
            cout<<"CONFIRMAR? 1--SI // 2--NO: ";
            int opc;
            opc = ingresoOpcSimpleConValidacion();
            if(opc == 1)
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
