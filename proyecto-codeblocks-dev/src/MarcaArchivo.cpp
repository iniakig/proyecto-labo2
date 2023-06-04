#include "MarcaArchivo.h"

//CONSTRUCTORES
MarcaArchivo::MarcaArchivo()
{
    _ruta = "marcas.dat";
}

MarcaArchivo::MarcaArchivo(std::string ruta)
{
    _ruta = ruta;
}

// GETTERS
int MarcaArchivo::getCantidadDeRegistros()
{
    FILE *p = fopen(_ruta.c_str(), "rb");

    if (p == NULL)
    {
        return 0;
    }

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);

    return bytes / sizeof(Marca);
}

//INTERFACES
Marca MarcaArchivo::leer(int posicion)
{
    Marca aux;
    FILE *p = fopen(_ruta.c_str(), "rb");
    if (p == NULL)
    {
        return aux;
    }

    fseek(p, posicion * sizeof(Marca), SEEK_SET);
    fread(&aux, sizeof(Marca), 1, p);
    fclose(p);
    return aux;
}

void MarcaArchivo::leer(Marca *vec, int cantidadRegistrosALeer)
{
    FILE *p = fopen(_ruta.c_str(), "rb");
    if (p == NULL)
    {
        return;
    }

    fread(vec, sizeof(Marca), cantidadRegistrosALeer, p);
    fclose(p);
}

bool MarcaArchivo::guardar(Marca reg)
{
    FILE *p = fopen(_ruta.c_str(), "ab");

    if (p == NULL)
    {
        return false;
    }

    bool pudoGuardar = fwrite(&reg, sizeof(Marca), 1, p);
    fclose(p);
    return pudoGuardar;
}

bool MarcaArchivo::guardar(Marca reg, int posicionAReemplazar)
{
    FILE *p = fopen(_ruta.c_str(), "ab");

    if (p == NULL)
    {
        return false;
    }

    fseek(p, posicionAReemplazar * sizeof(Marca), SEEK_SET);
    bool pudoGuardar = fwrite(&reg, sizeof(Marca), 1, p);
    fclose(p);
    return pudoGuardar;
}

bool MarcaArchivo::guardar(Marca *vec, int cantidadRegistrosAEscribir)
{
    FILE *p = fopen(_ruta.c_str(), "ab");
    if (p == NULL)
    {
        return false;
    }

    int cantidadRegistrosEscritos = fwrite(vec, sizeof(Marca),cantidadRegistrosAEscribir, p);
    fclose(p);
    return cantidadRegistrosEscritos == cantidadRegistrosAEscribir;
}

int MarcaArchivo::buscar(std::string nombreMarca)
{
    MarcaArchivo archivo;
    int cantidadRegistros = archivo.getCantidadDeRegistros();

    Marca aux;
    for(int i = 0; i<cantidadRegistros; i++)
    {
        aux = archivo.leer(i);
        if (strcmp(aux.getNombre(), nombreMarca.c_str()) == 0)
        {
            return i;
        }
    }
    return -1;
}

int MarcaArchivo::buscar(int ID)
{
    MarcaArchivo archivo;
    int cantidadRegistros = archivo.getCantidadDeRegistros();

    Marca aux;
    for (int i = 0; i<cantidadRegistros; i++)
    {
        aux=archivo.leer(i);
        if(aux.getID() == ID)
        {
            return i;
        }
    }
    return -1;
}

void MarcaArchivo::vaciar()
{
    FILE *p = fopen(_ruta.c_str(), "wb");
    if (p == NULL)
    {
        return ;
    }
    fclose(p);
}
