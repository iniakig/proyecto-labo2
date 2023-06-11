#include <iostream>

#include <locale.h>
#include <regex>
#include <windows.h>
#include <string>

#include "funciones.h"
#include "rlutil.h"

void setSpanish()
{
    setlocale(LC_ALL, "Spanish");
}

int enteroConvertidoAInt(std::string stringParaConvertir)
{
    int numero = 0;

    numero = std::stoi(stringParaConvertir);

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

std::string ingresoDeNombreApellidoConValidacion() {
    std::string texto;
    std::string textoConvertido;
    const std::regex expresionRegular("[A-Za-z\\s]{4,24}");

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
    const std::regex expresionRegular("[A-Za-z]{4, 14}");

    getline(std::cin, alias);
    while (!std::regex_match(alias, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es válido. Ingrese nuevamente: ";
        getline(std::cin, alias);
    }

    textoConvertido = stringAMayus(alias);
    return textoConvertido;
}

std::string ingresoDeContraseniaConValidacion() {
    std::string contrasenia;
    const std::regex expresionRegular("[A-Za-z0-9!.%$_-]{8, 14}");

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
    const std::regex expresionRegular("[a-zA-Z0-9._,\\s-]{1,29}");

    getline(std::cin, razonSocial);
    while (!std::regex_match(razonSocial, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es válido." << std::endl;
        std::cout << "Reglas de ingreso de razón social: " << std::endl;
        std::cout << "- Puede contener hasta 29 caracteres" << std::endl;
        std::cout << "- Permite letras, números y caracteres de \".\", \",\", \"-\" y \"_\"." << std::endl;

        getline(std::cin, razonSocial);
    }

    return razonSocial;
}

std::string ingresoDeLocalidadConValidacion() {
    std::string localidad;
    const std::regex expresionRegular("[a-zA-Z0-9.\\s]+{1,29}");

    getline(std::cin, localidad);
    while (!std::regex_match(localidad, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es válido." << std::endl;
        std::cout << "Reglas de ingreso de razón social: " << std::endl;
        std::cout << "- Puede contener hasta 29 caracteres" << std::endl;
        std::cout << "- Permite letras, números y caracteres de \".\", \",\", \"-\" y \"_\"." << std::endl;

        getline(std::cin, localidad);
    }

    return localidad;
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
    const std::regex expresionRegular("[1-24]");

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

void listarProvincias() {
    const int cantidadProvincias = 24;
    std::string provincias[cantidadProvincias] = {
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

    for (int i = 0; i < cantidadProvincias; i++) {
        std::cout << "\t" << i + 1 << ": " << provincias[i];
        std::cout << std::endl;
    }
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

// Mensajes

void okMensajeCreacion() {
    std::cout << "El registro se creó correctamente." << std::endl;
}

void errorMensajeCreacion() {
    std::cout << "El registro no se pudo crear." << std::endl;
}

void okMensajeModificacion() {
    std::cout << "El registro se modificó correctamente." << std::endl;
}

void errorMensajeModificacion() {
    std::cout << "El registro no se pudo modificar." << std::endl;
}

void okMensajeBaja() {
    std::cout << "El registro se dio de baja correctamente." << std::endl;
}

void errorMensajeBaja() {
    std::cout << "El registro no se pudo dar de baja." << std::endl;
}

void okMensajeReactivacion() {
    std::cout << "El registro se reactivó correctamente." << std::endl;
}

void errorMensajeReactivacion() {
    std::cout << "El registro no se pudo reactivar." << std::endl;
}

void registroNoEncontradoMensaje() {
    std::cout << "No se encontró el registro buscado para realizar la acción solicitada" << std::endl;
}

void existeRegistroMensaje() {
    std::cout << "Ya existe un registro creado con ese nro de identificación." << std::endl;
}

void mensajeSalidaDelPrograma() {
    std::cout << "Muchas gracias por usar la aplicación." << std::endl;
}
