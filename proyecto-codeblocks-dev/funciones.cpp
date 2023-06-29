#include "funciones.h"

#include <iostream>
#include <locale.h>
#include <windows.h>
#include <string>
#include "rlutil.h"

void setSpanish()
{
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
}

int enteroConvertidoAInt(std::string stringParaConvertir)
{
    int numero = 0;

    numero = std::stoi(stringParaConvertir);

    return numero;
}

float stringConvertidoAFloat(std::string stringParaConvertir)
{
    float numero = 0;

    numero = std::stof(stringParaConvertir);

    return numero;
}

std::string stringAMayus(std::string cadena)
{
    std::string cadenaMayus = cadena;
    for(int i = 0; i<cadenaMayus.length(); i++)
    {
        cadenaMayus[i] = toupper(cadenaMayus[i]);
    }
    return cadenaMayus;
}

std::string cortarCuit(std::string stringParaCortar)
{
    std::string dni;

    dni = stringParaCortar.substr(2, stringParaCortar.length() - 3);

    return dni;
}

void centrarTexto(std::string texto, int posy)
{
    int posx;
    posx = rlutil::tcols() / 2 - texto.size() / 2;
    rlutil::locate(posx, posy);
    std::cout << texto;
}

void ponerCero(int *vec, int tam)
{
    for(int i = 0; i<tam; i++)
    {
        vec[i] = 0;
    }
}

void listarProvincias()
{
    const int cantidadProvincias = 24;
    std::string provincias[cantidadProvincias] =
    {
        "CABA",
        "Buenos Aires",
        "Catamarca",
        "Chaco",
        "Chubut",
        "Córdoba",
        "Corrientes",
        "Entre Ríos",
        "Formosa",
        "Jujuy",
        "La Pampa",
        "La Rioja",
        "Mendoza",
        "Misiones",
        "Neuquén",
        "Río Negro",
        "Salta",
        "San Juan",
        "San Luis",
        "Santa Cruz",
        "Santa Fe",
        "Santiago del Estero",
        "Tierra del Fuego",
        "Tucumán"
    };

    for (int i = 0; i < cantidadProvincias; i++)
    {
        std::cout << "\t" << i + 1 << ": " << provincias[i];
        std::cout << std::endl;
    }
}
