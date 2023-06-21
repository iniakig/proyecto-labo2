#include "validaciones.h"

#include <iostream>
#include <string>
#include <regex>
#include "funciones.h"

int ingresoTipoDeDocumentoConValidacion() {
    std::string tipoDocumentoAux;
    int tipoDocumento;
    const std::regex expresionRegular("[1-2]");

    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, tipoDocumentoAux);
    while (!std::regex_match(tipoDocumentoAux, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El valor ingresado no es válido. El valor permitido es un número entero entre 1 y 2. Ingrese nuevamente: ";
        getline(std::cin, tipoDocumentoAux);
    }

    tipoDocumento = enteroConvertidoAInt(tipoDocumentoAux);
    return tipoDocumento;
}

int ingresoCategoriaProdConValidacion(){
    std::string nroCategoriaAux;
    int nroCategoria;
    const std::regex expresionRegular("[1-3]");

    getline(std::cin, nroCategoriaAux);
    while(!std::regex_match(nroCategoriaAux, expresionRegular)){
        std::cout << std::endl;
        std::cout << "El valor ingresado no es válido. 1. CELULARES | 2. TABLETS | 3. ACCESORIOS. Ingrese nuevamente: ";
        getline(std::cin, nroCategoriaAux);
    }
    nroCategoria = enteroConvertidoAInt(nroCategoriaAux);
    return nroCategoria;
}

int ingresoStockConValidacion(){
    std::string stockAux;
    int stock;
    const std::regex expresionRegular("^[1-9][0-9]*$");

    getline(std::cin, stockAux);
    while(!std::regex_match(stockAux, expresionRegular)){
        std::cout << std::endl;
        std::cout << "El valor ingresado no es válido. Solo puede ingresar numeros enteros.";
        getline(std::cin, stockAux);
    }
    stock = enteroConvertidoAInt(stockAux);
    return stock;
}

float ingresoPrecioConValidacion() {
    std::string precioAux;
    float precio;
    const std::regex expresionRegular("^[0-9]+(\\.[0-9]+)?$");

    getline(std::cin, precioAux);
    while(!std::regex_match(precioAux, expresionRegular)){
        std::cout << std::endl;
        std::cout << "El precio ingresado no es válido. Solo puede ingresar numeros.";
        getline(std::cin, precioAux);
    }
    precio = stringConvertidoAFloat(precioAux);
    return precio;
}

std::string ingresoDeDocumentoConValidacion() {
    std::string nroDocumento;
    const std::regex expresionRegular("[0-9]{1,11}"); // Desde un millón hasta 99999999999 porque es el límite de números entre un DNI mínimo y un CUIT máximo.

    getline(std::cin, nroDocumento);
    while (!std::regex_match(nroDocumento, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El valor ingresado no es válido. Ingrese nuevamente: ";
        getline(std::cin, nroDocumento);
    }

    return nroDocumento;
}

std::string ingresoDeDNIConValidacion() {
    std::string nroDocumento;
    const std::regex expresionRegular("[0-9]{1,8}");

    getline(std::cin, nroDocumento);
    while (!std::regex_match(nroDocumento, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El valor ingresado no es válido. Ingrese nuevamente: ";
        getline(std::cin, nroDocumento);
    }

    return nroDocumento;
}

std::string ingresoDeNombreApellidoConValidacion() {
    std::string texto;
    std::string textoConvertido;
    const std::regex expresionRegular("[A-Za-zñÑ\\s]{4,24}");

    getline(std::cin, texto);
    while (!std::regex_match(texto, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es válido. Ingrese nuevamente: ";
        getline(std::cin, texto);
    }

    textoConvertido = stringAMayus(texto);
    return textoConvertido;
}

std::string ingresoDeAliasConValidacion() {
    std::string alias;
    std::string textoConvertido;
    const std::regex expresionRegular("[A-Za-z]{4,14}");

    getline(std::cin, alias);
    while (!std::regex_match(alias, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es válido.";
        std::cout << "Reglas de ingreso de alias: " << std::endl;
        std::cout << "- Puede contener entre 4 y 14 caracteres" << std::endl;
        std::cout << "- Permite solo letras (Es indistinto si mayúsculas o minúsculas)" << std::endl;
        std::cout << "Ingrese nuevamente: ";
        getline(std::cin, alias);
    }

    textoConvertido = stringAMayus(alias);
    return textoConvertido;
}

std::string ingresoDeContraseniaConValidacion() {
    std::string contrasenia;
    const std::regex expresionRegular("[A-Za-z0-9!.%$_ -]{8,14}");

    getline(std::cin, contrasenia);
    while (!std::regex_match(contrasenia, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es válido. Ingrese nuevamente: ";
        getline(std::cin, contrasenia);
    }

    return contrasenia;
}

std::string ingresoDeEmailConValidacion() {
    std::string email;
    const std::regex expresionRegular("[a-zA-Z0-9._]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");

    getline(std::cin, email);
    while (!std::regex_match(email, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no corresponde a un formato de email. Ingrese nuevamente: ";
        getline(std::cin, email);
    }

    return email;
}

std::string ingresoDeRazonSocialConValidacion() {
    std::string razonSocial;
    std::string razonSocialConvertida;
    const std::regex expresionRegular("[a-zA-Z0-9._,\\s-]{1,29}");

    getline(std::cin, razonSocial);
    while (!std::regex_match(razonSocial, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es válido." << std::endl;
        std::cout << "Reglas de ingreso de razón social: " << std::endl;
        std::cout << "- Puede contener hasta 29 caracteres" << std::endl;
        std::cout << "- Permite letras, números y caracteres de \".\", \",\", \"-\" y \"_\"." << std::endl;
        std::cout << "Ingrese nuevamente: ";
        getline(std::cin, razonSocial);
    }

    razonSocialConvertida = stringAMayus(razonSocial);

    return razonSocial;
}

std::string ingresoDeLocalidadConValidacion() {
    std::string localidad;
    const std::regex expresionRegular("[a-zA-Z0-9.\\s]+{1,29}");

    getline(std::cin, localidad);
    while (!std::regex_match(localidad, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es válido." << std::endl;
        std::cout << "Reglas de ingreso de localidad: " << std::endl;
        std::cout << "- Puede contener hasta 29 caracteres" << std::endl;
        std::cout << "- Permite letras, números y caracteres de \".\", \",\", \"-\" y \"_\"." << std::endl;
        std::cout << "Ingrese nuevamente: ";
        getline(std::cin, localidad);
    }

    return localidad;
}

std::string ingresoModeloConValidacion() {
    std::string modelo;
    const std::regex expresionRegular("[a-zA-Z0-9.\\s_-]+{1,29}");

    getline(std::cin, modelo);
    while(!std::regex_match(modelo, expresionRegular)){
        std::cout << std::endl;
        std::cout << "El texto ingresado no es válido." << std::endl;
        std::cout << "Reglas de ingreso de nombre de modelo: " << std::endl;
        std::cout << "- Puede contener hasta 14 caracteres" << std::endl;
        std::cout << "- Permite letras, números y caracteres de \".\", \",\", \"-\" y \"_\"." << std::endl;
        std::cout << "Ingrese nuevamente: ";
        getline(std::cin, modelo);
    }
    std::string textoConvertido = stringAMayus(modelo);
    return textoConvertido;

}

std::string ingresoDescripcionConValidacion(){
    std::string descripcion;
    const std::regex expresionRegular("[a-zA-Z0-9.\\s]+{1,49}");

    getline(std::cin, descripcion);
    while(!std::regex_match(descripcion, expresionRegular)){
        std::cout << std::endl;
        std::cout << "El texto ingresado no es válido." << std::endl;
        std::cout << "Reglas de ingreso de nombre de modelo: " << std::endl;
        std::cout << "- Puede contener hasta 14 caracteres" << std::endl;
        std::cout << "- Permite letras, números y caracteres de \".\", \",\", \"-\" y \"_\"." << std::endl;
        std::cout << "Ingrese nuevamente: ";
        getline(std::cin, descripcion);
    }
    std::string textoConvertido = stringAMayus(descripcion);
    return textoConvertido;

}

std::string ingresoDeDomicilioConValidacion() {
    std::string domicilio;
    const std::regex expresionRegular("[a-zA-Z0-9.\\s]+{1,29}");

    getline(std::cin, domicilio);
    while (!std::regex_match(domicilio, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es válido." << std::endl;
        std::cout << "Reglas de ingreso de razón social: " << std::endl;
        std::cout << "- Puede contener hasta 29 caracteres" << std::endl;
        std::cout << "- Permite letras, números y caracteres de \".\", \",\", \"-\" y \"_\"." << std::endl;

        getline(std::cin, domicilio);
    }

    return domicilio;
}

int ingresoDeTipoDeClienteConValidacion() {
    std::string tipoDeClienteAux;
    int tipoDeCliente;
    const std::regex expresionRegular("[1-2]");

    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, tipoDeClienteAux);
    while (!std::regex_match(tipoDeClienteAux, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El valor ingresado no es válido. El valor permitido es un número entero entre 1 y 2. Ingrese nuevamente: ";
        getline(std::cin, tipoDeClienteAux);
    }

    tipoDeCliente = enteroConvertidoAInt(tipoDeClienteAux);
    return tipoDeCliente;
}


int ingresoDeProvinciaConValidacion() {
    std::string provinciaAux;
    int provincia;
    const std::regex expresionRegular("[1-9]|1[0-9]|2[0-4]");

    getline(std::cin, provinciaAux);
    while (!std::regex_match(provinciaAux, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El valor ingresado no es válido. El valor permitido es un número entero entre 1 y 24. Ingrese nuevamente: ";
        getline(std::cin, provinciaAux);
    }

    provincia = enteroConvertidoAInt(provinciaAux);
    return provincia;
}

std::string ingresoDeDecisionConValidacion() {
    std::string texto;
    std::string textoConvertido;
    std::regex expresionRegular("[Ss][Ii]|[Nn][Oo]");

    getline(std::cin, texto);
    while(!std::regex_match(texto, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El valor ingresado no es válido. Ingrese SI o NO: ";
        getline(std::cin, texto);
    }

    textoConvertido = stringAMayus(texto);

    return textoConvertido;
}

std::string ingresoDeMarcaConValidacion()
{
    std::string texto;
    const std::regex expresionRegular("[A-Za-z0-9 ]{1,29}");

    getline(std::cin, texto);
    while (!std::regex_match(texto, expresionRegular))
    {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es válido. Ingrese nuevamente: ";
        getline(std::cin, texto);
    }

    texto = stringAMayus(texto);
    return texto;
}

int ingresoDeRolConValidacion() {
    std::string rolAux;
    int rol;
    const std::regex expresionRegular("[0-2]");

    getline(std::cin, rolAux);
    while (!std::regex_match(rolAux, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El valor ingresado no es válido. El valor permitido es un número entero entre 0 y 2. Ingrese nuevamente: ";
        getline(std::cin, rolAux);
    }

    rol = enteroConvertidoAInt(rolAux);
    return rol;
}

int ingresoOpcSimpleConValidacion()
{
    std::string opcAux;
    int opcion;
    const std::regex expresionRegular("[1-2]");

    getline(std::cin, opcAux);
    while (!std::regex_match(opcAux, expresionRegular))
    {
        std::cout << std::endl;
        std::cout << "El valor ingresado no es válido. El valor permitido es un número entero entre 1 y 2. Ingrese nuevamente: ";
        getline(std::cin, opcAux);
    }

    opcion = enteroConvertidoAInt(opcAux);
    return opcion;
}
