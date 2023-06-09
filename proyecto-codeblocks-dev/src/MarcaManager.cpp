#include<iostream>
#include "MarcaManager.h"
#include "../funciones.h"

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
        cout<<"NO EXISTE NINGUNA MARCA CON ESE ID"<<endl;
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
        cout<<"NO EXISTE NINGUNA MARCA CON ESE NOMBRE"<<endl;
    }

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
}
void MarcaManager::cargar()
{
    cout<<"INGRESE EL NOMBRE DE LA MARCA: ";
    std::string nombre = ingresoDeMarcaConValidacion();

    if(_archivo.buscar(nombre)<0)
    {
        int ID = generarID();
        int opc;
        bool activo = true;
        Marca reg(ID,nombre.c_str(), activo);
        cout<<"CARGO LA SIGUIENTE MARCA: "<<endl;
        listar(reg);
        cout<<"GUARDAR? 1--SI // 2--NO: ";
        opc = ingresoOpcSimpleConValidacion();
        if(opc == 1)
        {
            if(_archivo.guardar(reg))
            {
                cout<<"MARCA AGREGADA CORRECTAMENTE"<<endl;
            }
            else
            {
                cout<<"ERROR AL AGREGAR LA MARCA, INTENTELO NUEVAMENTE"<<endl;
            }
        }
    }
    else
    {
        Marca reg;
        reg = _archivo.leer(_archivo.buscar(nombre));
        cout<<"LA MARCA QUE ESTA INTENTANDO CARGAR YA EXISTE: "<<endl;
        listar(reg);

    }


}

int MarcaManager::cargarDesdeProducto(std::string nombreMarca)
{
    // POSIBLE OPTIMIZACION: QUE SI CUMPLE LA CONDICION DIRECTAMENTE DEVUELVA LA MARCA ENCONTRADA Y SINO PIDA CARGARLA (INVERTIR EL ORDEN DE EJECUCION)
    if(_archivo.buscar(nombreMarca)>=0)
    {
        Marca reg;
        reg = _archivo.leer(_archivo.buscar(nombreMarca));
        return reg.getID();
    }

    int ID = generarID();
    int opc;
    bool activo = true;
    Marca reg(ID,nombreMarca.c_str(), activo);
    cout<<"CARGO LA SIGUIENTE MARCA: "<<endl;
    cout<<"ID: "<<reg.getID()<<endl;
    cout<<"NOMBRE: "<<reg.getNombre()<<endl;
    cout<<"GUARDAR? 1--SI // 2--NO: ";
    opc = ingresoOpcSimpleConValidacion();
    if(opc == 1)
    {
        if(_archivo.guardar(reg))
        {
            cout<<"MARCA AGREGADA CORRECTAMENTE"<<endl;
            return ID;
        }
        else
        {
            cout<<"ERROR AL AGREGAR LA MARCA, INTENTELO NUEVAMENTE"<<endl;
            reg = Marca();
            return ID;
        }
    }
    else if(opc == 2)
    {
        reg = Marca();
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
                cout<<pos<<endl;
                cout<<"MARCA MODIFICADA CORRECTAMENTE"<<endl;
                listar(_archivo.leer(pos));
            }
            else
            {
                cout<<"ERROR AL MODIFICAR LA MARCA, INTENTELO NUEVAMENTE"<<endl;
            }
        }

    }
    else
    {
        cout<<"NO EXISTE NINGUNA MARCA CON ESE ID"<<endl;
    }
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
                    cout<<"MARCA MODIFICADA CORRECTAMENTE"<<endl;
                    listar(_archivo.leer(pos));
                }
                else
                {
                    cout<<"ERROR AL MODIFICAR LA MARCA, INTENTELO NUEVAMENTE"<<endl;
                }
            }

        }
        else
        {
            cout<<"NO EXISTE NINGUNA MARCA CON ESE NOMBRE"<<endl;
        }
    }

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
        for(int i = 0; i<cantProductos; i++)
        {
            Producto prodAux;
            prodAux = arProductos.leer(i);
            if(reg.getID() == prodAux.getIdMarca() && prodAux.getActivo())
            {
                if(!marcaAsignada)
                {
                    cout<<"NO ES POSIBLE ELIMINAR LA MARCA SELECCIONADA. LA MISMA ESTA ASIGNADA A LOS SIGUIENTES PRODUCTOS:"<<endl;
                    //MOSTRAR PRODUCTO CON EL LISTAR DE MANAGER PROD
                    cout<<"ACA SE MUESTRA EL PRODUCTO CANDO ESTE LISTAR DE MANAGER";
                    marcaAsignada = 1;
                }
                else
                {
                    //MOSTRAR PRODUCTO CON EL LISTAR DE MANAGER PROD
                    cout<<"ACA SE MUESTRA EL PRODUCTO CANDO ESTE LISTAR DE MANAGER";
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
                    cout<<"MARCA ELIMINADA CORRECTAMENTE"<<endl;
                }
                else
                {
                    cout<<"ERROR AL ELIMINAR LA MARCA, INTENTELO NUEVAMENTE"<<endl;
                }
            }
        }
    }
    else
    {
        cout<<"NO EXISTE MARCA REGISTRADA BAJO ESE ID"<<endl;
    }
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
                    cout<<"MARCA ACTIVADA CORRECTAMENTE"<<endl;
                }
                else
                {
                    cout<<"ERROR AL ACTIVAR LA MARCA, INTENTELO NUEVAMENTE"<<endl;
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
        cout<<"NO EXISTE MARCA REGISTRADA BAJO ESE ID"<<endl;
    }
}
