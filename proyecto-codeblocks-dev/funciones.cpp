#include "funciones.h"

#include <iostream>
#include <locale.h>
#include <windows.h>
#include <string>
#include "rlutil.h"

/*
void setSpanish()
{
    setlocale(LC_ALL, "Spanish");
}
*/

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

float stringConvertidoAFloat(std::string stringParaConvertir){
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

std::string cortarCuit(std::string stringParaCortar) {
    std::string dni;

    dni = stringParaCortar.substr(2, stringParaCortar.length() - 3);

    return dni;
}

void centrarTexto(std::string texto, int posy) {
	int posx;
	posx = rlutil::tcols() / 2 - texto.size() / 2;
	rlutil::locate(posx, posy);
	std::cout << texto;
}
