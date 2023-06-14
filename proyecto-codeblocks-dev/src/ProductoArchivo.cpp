#include "ProductoArchivo.h"

//CONSTRUCTORES
ProductoArchivo::ProductoArchivo()
{
    _ruta = "productos.dat";
}

ProductoArchivo::ProductoArchivo(std::string ruta)
{
    _ruta = ruta;
}

// GETTERS
int ProductoArchivo::getCantidadDeRegistros()
{
    FILE *p = fopen(_ruta.c_str(), "rb");

    if (p == NULL)
    {
        return 0;
    }

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);

    return bytes / sizeof(Producto);
}

//INTERFACES
Producto ProductoArchivo::leer(int posicion)
{
    Producto aux;
    FILE *p = fopen(_ruta.c_str(), "rb");
    if (p == NULL)
    {
        return aux;
    }

    fseek(p, posicion * sizeof(Producto), SEEK_SET);
    fread(&aux, sizeof(Producto), 1, p);
    fclose(p);
    return aux;
}

void ProductoArchivo::leer(Producto *vec, int cantidadRegistrosALeer)
{
    FILE *p = fopen(_ruta.c_str(), "rb");
    if (p == NULL)
    {
        return;
    }

    fread(vec, sizeof(Producto), cantidadRegistrosALeer, p);
    fclose(p);
}

bool ProductoArchivo::guardar(Producto reg)
{
    FILE *p = fopen(_ruta.c_str(), "ab");

    if (p == NULL)
    {
        return false;
    }

    bool pudoGuardar = fwrite(&reg, sizeof(Producto), 1, p);
    fclose(p);
    return pudoGuardar;
}

bool ProductoArchivo::guardar(Producto reg, int posicionAReemplazar)
{
    FILE *p = fopen(_ruta.c_str(), "rb+");

    if (p == NULL)
    {
        return false;
    }

    fseek(p, posicionAReemplazar * sizeof(Producto), SEEK_SET);
    bool pudoGuardar = fwrite(&reg, sizeof(Producto), 1, p);
    fclose(p);
    return pudoGuardar;
}

bool ProductoArchivo::guardar(Producto *vec, int cantidadRegistrosAEscribir)
{
    FILE *p = fopen(_ruta.c_str(), "ab");
    if (p == NULL)
    {
        return false;
    }

    int cantidadRegistrosEscritos = fwrite(vec, sizeof(Producto),cantidadRegistrosAEscribir, p);
    fclose(p);
    return cantidadRegistrosEscritos == cantidadRegistrosAEscribir;
}

int ProductoArchivo::buscar(int ID)
{
    int cantidadRegistros = this->getCantidadDeRegistros();
    Producto aux;
    for (int i = 0; i<cantidadRegistros; i++)
    {
        aux=this->leer(i);
        if(aux.getID() == ID)
        {
            return i;
        }
    }
    return -1;
}

void ProductoArchivo::vaciar()
{
    FILE *p = fopen(_ruta.c_str(), "wb");
    if (p == NULL)
    {
        return ;
    }
    fclose(p);
}
