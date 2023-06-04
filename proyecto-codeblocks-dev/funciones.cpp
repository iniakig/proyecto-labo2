#include <iostream>

#include <locale.h>
#include <regex>
#include <windows.h>

#include "funciones.h"

void setSpanish() {
    setlocale(LC_ALL, "Spanish");
}

int enteroConvertidoAInt(std::string stringParaConvertir) {
    int numero = 0;

    numero = std::stoi(stringParaConvertir);

    return numero;
}

// TO DO por I�AQUI

/*

string stringEnMayuscula(string stringParaConvertir) { //Ac� entra de cualquier manera
    string convertido; // auxiliar

    convertido = convertirAMayuscula(stringParaConvertir) // Al auxiliar lo convertimos si o si a mayuscula

    return convertido; // devolvemos el string en mayuscula
}

*/

int ingresoTipoDeDocumentoConValidacion() {
    std::string tipoDocumentoAux;
    int tipoDocumento;
    const std::regex expresionRegular("[1-2]");

    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, tipoDocumentoAux);
    while (!std::regex_match(tipoDocumentoAux, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El valor ingresado no es v�lido. El valor permitido es un n�mero entero entre 1 y 2. Ingrese nuevamente: ";
        getline(std::cin, tipoDocumentoAux);
    }

    tipoDocumento = enteroConvertidoAInt(tipoDocumentoAux);
    return tipoDocumento;
}

std::string ingresoDeDocumentoConValidacion() {
    std::string nroDocumento;
    const std::regex expresionRegular("[1000000-99999999999]+"); // Desde un mill�n hasta 99999999999 porque es el l�mite de n�meros entre un DNI m�nimo y un CUIT m�ximo.

    getline(std::cin, nroDocumento);
    while (!std::regex_match(nroDocumento, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El valor ingresado no es v�lido. Ingrese nuevamente: ";
        getline(std::cin, nroDocumento);
    }

    return nroDocumento;
}

std::string ingresoDeTextoConValidacion() {
    std::string texto;
    const std::regex expresionRegular("[A-Za-z]{4,}");

    getline(std::cin, texto);
    while (!std::regex_match(texto, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es v�lido. Ingrese nuevamente: ";
        getline(std::cin, texto);
    }

    return texto;
}

std::string ingresoDeAliasConValidacion() {
    std::string alias;
    const std::regex expresionRegular("[A-Za-z]{4, 14}");

    getline(std::cin, alias);
    while (!std::regex_match(alias, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es v�lido. Ingrese nuevamente: ";
        getline(std::cin, alias);
    }

    stringEnMayuscula(alias); // Ac� lo convierte en may�scula // TODO POR I�AQUI

    return alias;
}

std::string ingresoDeContraseniaConValidacion() {
    std::string contrasenia;
    const std::regex expresionRegular("[A-Za-z0-9!.%$_-]{8, 14}");

    getline(std::cin, contrasenia);
    while (!std::regex_match(contrasenia, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es v�lido. Ingrese nuevamente: ";
        getline(std::cin, contrasenia);
    }

    return contrasenia;
}

std::string ingresoDeEmailConValidacion() {
    std::string email;
    const std::regex expresionRegular("[a-zA-Z0-9._]+@[a-zA-Z0-9.-]\\.[a-zA-Z]{2,}");

    getline(std::cin, email);
    while (!std::regex_match(email, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no corresponde a un formato de email. Ingrese nuevamente: ";
        getline(std::cin, email);
    }

    return email;
}
