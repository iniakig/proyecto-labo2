#include <iostream>
using namespace std;
#include "VentaArchivo.h"

VentaArchivo::VentaArchivo(){
_ruta="ventas.dat";
}

VentaArchivo::VentaArchivo(std::string ruta){
_ruta=ruta;
}

int VentaArchivo::getCantidadRegistros(){
 FILE *p = fopen(_ruta.c_str(), "rb");

    if (p == NULL)
    {
        return 0;
    }

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);

    return bytes / sizeof(Venta);
}

bool VentaArchivo::guardar(Venta reg){
FILE *p = fopen(_ruta.c_str(), "ab");

    if (p == NULL)
    {
        return false;
    }

    bool pudoGuardar = fwrite(&reg, sizeof(Venta), 1, p);
    fclose(p);
    return pudoGuardar;
}

bool VentaArchivo::guardar(Venta reg, int posRegAReemplazar){
    FILE *p = fopen(_ruta.c_str(), "rb+");

    if (p == NULL)
    {
        return false;
    }

    fseek(p, posRegAReemplazar * sizeof(Venta), SEEK_SET);
    bool pudoGuardar = fwrite(&reg, sizeof(Venta), 1, p);
    fclose(p);
    return pudoGuardar;
}

bool VentaArchivo::guardar(Venta *vec, int cantidadRegistrosAEscribir)
{
    FILE *p = fopen(_ruta.c_str(), "ab");
    if (p == NULL)
    {
        return false;
    }

    int cantidadRegistrosEscritos = fwrite(vec, sizeof(Venta),cantidadRegistrosAEscribir, p);
    fclose(p);
    return cantidadRegistrosEscritos == cantidadRegistrosAEscribir;
}

Venta VentaArchivo::leer(int nroRegistro){
    Venta aux;
    FILE *p = fopen(_ruta.c_str(), "rb");
    if (p == NULL)
    {
        return aux;
    }

    fseek(p, nroRegistro * sizeof(Venta), SEEK_SET);
    fread(&aux, sizeof(Venta), 1, p);
    fclose(p);
    return aux;
}

void VentaArchivo::leer(Venta *vec, int cantidadRegistrosALeer){
    FILE *p = fopen(_ruta.c_str(), "rb");
    if (p == NULL)
    {
        return;
    }

    fread(vec, sizeof(Venta), cantidadRegistrosALeer, p);
    fclose(p);
}

int VentaArchivo::buscar(int ID){
    int cantidadRegistros = this->getCantidadRegistros();
    Venta aux;
    for (int i = 0; i<cantidadRegistros; i++)
    {
        aux=this->leer(i);
        if(aux.getIdPedido() == ID)
        {
            return i;
        }
    }
    return -1;
}

void VentaArchivo::vaciar(){
FILE *p = fopen(_ruta.c_str(), "wb");
    if (p == NULL)
    {
        return ;
    }
    fclose(p);
}
