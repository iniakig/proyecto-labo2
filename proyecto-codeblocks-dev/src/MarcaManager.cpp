#include<iostream>
#include "MarcaManager.h"
#include "../funciones.h"

using namespace std;


int MarcaManager::generarID(){
    return _archivo.getCantidadDeRegistros()+1;
}

void MarcaManager::cargar(){
    cout<<"INGRESE EL NOMBRE DE LA MARCA: ";
    std::string nombre = ingresoDeMarcaConValidacion();
    int ID = generarID();

    Marca reg(ID, nombre.c_str());

    cout<<"CARGO LA SIGUIENTE MARCA: "<<endl;
    cout<<"ID: "<<reg.getID()<<endl;
    cout<<"NOMBRE: "<<reg.getNombre();
    cout<<"GUARDAR? 1--SI // 2--NO"<<endl;

}
