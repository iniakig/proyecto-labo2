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

void MarcaManager::listarXNombre(){

    cout<<"INGRESE EL NOMBRE: ";
    std::string nombre = ingresoDeMarcaConValidacion();

    int pos = _archivo.buscar(nombre);
    if(pos >= 0){
        Marca reg;
        reg = _archivo.leer(pos);
        listar(reg);
    }else{
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
        Marca reg(ID, nombre.c_str());
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

Marca MarcaManager::cargarDesdeProducto(std::string nombreMarca)
{
    if(_archivo.buscar(nombreMarca)<0)
    {
        int ID = generarID();
        int opc;
        Marca reg(ID, nombreMarca.c_str());
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
                return reg;
            }
            else
            {
                cout<<"ERROR AL AGREGAR LA MARCA, INTENTELO NUEVAMENTE"<<endl;
                reg = Marca();
                return reg;
            }
        }
        else if(opc == 2)
        {
            reg = Marca();
            return reg;
        }
    }
    Marca reg;
    reg = _archivo.leer(_archivo.buscar(nombreMarca));
    return reg;
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
        modificaarXNombre();
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

void MarcaManager::modificaarXNombre()
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
