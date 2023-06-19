#include <iostream>

#include <locale.h>
#include <regex>
#include <windows.h>
#include <string>

#include "funciones.h"
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
        std::cout << "El valor ingresado no es v�lido. El valor permitido es un n�mero entero entre 1 y 2. Ingrese nuevamente: ";
        getline(std::cin, tipoDocumentoAux);
    }

    tipoDocumento = enteroConvertidoAInt(tipoDocumentoAux);
    return tipoDocumento;
}

std::string ingresoDeDocumentoConValidacion() {
    std::string nroDocumento;
    const std::regex expresionRegular("[0-9]{1,11}"); // Desde un mill�n hasta 99999999999 porque es el l�mite de n�meros entre un DNI m�nimo y un CUIT m�ximo.

    getline(std::cin, nroDocumento);
    while (!std::regex_match(nroDocumento, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El valor ingresado no es v�lido. Ingrese nuevamente: ";
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
        std::cout << "El valor ingresado no es v�lido. Ingrese nuevamente: ";
        getline(std::cin, nroDocumento);
    }

    return nroDocumento;
}

std::string ingresoDeNombreApellidoConValidacion() {
    std::string texto;
    std::string textoConvertido;
    const std::regex expresionRegular("[A-Za-z��\\s]{4,24}");

    getline(std::cin, texto);
    while (!std::regex_match(texto, expresionRegular)) {
        std::cout << std::endl;
        std::cout << "El texto ingresado no es v�lido. Ingrese nuevamente: ";
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
        std::cout << "El texto ingresado no es v�lido.";
        std::cout << "Reglas de ingreso de alias: " << std::endl;
        std::cout << "- Puede contener entre 4 y 14 caracteres" << std::endl;
        std::cout << "- Permite solo letras (Es indistinto si may�sculas o min�sculas)" << std::endl;
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
        std::cout << "El texto ingresado no es v�lido. Ingrese nuevamente: ";
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
        std::cout << "El texto ingresado no es v�lido." << std::endl;
        std::cout << "Reglas de ingreso de raz�n social: " << std::endl;
        std::cout << "- Puede contener hasta 29 caracteres" << std::endl;
        std::cout << "- Permite letras, n�meros y caracteres de \".\", \",\", \"-\" y \"_\"." << std::endl;
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
        std::cout << "El texto ingresado no es v�lido." << std::endl;
        std::cout << "Reglas de ingreso de localidad: " << std::endl;
        std::cout << "- Puede contener hasta 29 caracteres" << std::endl;
        std::cout << "- Permite letras, n�meros y caracteres de \".\", \",\", \"-\" y \"_\"." << std::endl;
        std::cout << "Ingrese nuevamente: ";
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
        std::cout << "El texto ingresado no es v�lido." << std::endl;
        std::cout << "Reglas de ingreso de raz�n social: " << std::endl;
        std::cout << "- Puede contener hasta 29 caracteres" << std::endl;
        std::cout << "- Permite letras, n�meros y caracteres de \".\", \",\", \"-\" y \"_\"." << std::endl;

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
        std::cout << "El valor ingresado no es v�lido. El valor permitido es un n�mero entero entre 1 y 2. Ingrese nuevamente: ";
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
        std::cout << "El valor ingresado no es v�lido. El valor permitido es un n�mero entero entre 1 y 24. Ingrese nuevamente: ";
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
        std::cout << "El valor ingresado no es v�lido. Ingrese SI o NO: ";
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
        std::cout << "El texto ingresado no es v�lido. Ingrese nuevamente: ";
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
        std::cout << "El valor ingresado no es v�lido. El valor permitido es un n�mero entero entre 0 y 2. Ingrese nuevamente: ";
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
        std::cout << "El valor ingresado no es v�lido. El valor permitido es un n�mero entero entre 1 y 2. Ingrese nuevamente: ";
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
        "C�rdoba",
        "Corrientes",
        "Entre R�os",
        "Formosa",
        "Jujuy",
        "La Pampa",
        "La Rioja",
        "Mendoza",
        "Misiones",
        "Neuqu�n",
        "R�o Negro",
        "Salta",
        "San Juan",
        "San Luis",
        "Santa Cruz",
        "Santa Fe",
        "Santiago del Estero",
        "Tierra del Fuego",
        "Tucum�n"
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
    rlutil::setColor(rlutil::LIGHTGREEN);
    std::cout << "El registro se cre� correctamente." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void errorMensajeCreacion() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "El registro no se pudo crear." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void okMensajeModificacion() {
    rlutil::setColor(rlutil::LIGHTGREEN);
    std::cout << "El registro se modific� correctamente." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void errorMensajeModificacion() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "El registro no se pudo modificar." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void okMensajeBaja() {
    rlutil::setColor(rlutil::LIGHTGREEN);
    std::cout << "El registro se dio de baja correctamente." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void errorMensajeBaja() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "El registro no se pudo dar de baja." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void okMensajeReactivacion() {
    rlutil::setColor(rlutil::LIGHTGREEN);
    std::cout << "El registro se reactiv� correctamente." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void errorMensajeReactivacion() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "El registro no se pudo reactivar." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void registroNoEncontradoMensaje() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "No se encontr� el registro buscado para realizar la acci�n solicitada" << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void registroYaEliminado() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "El registro ingresado ya se encuentra eliminado." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void registroNoEliminado(){
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "El registro no se encuentra eliminado." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void existeRegistroMensaje() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "Ya existe un registro creado con ese nro de identificaci�n." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void mensajeSalidaDelPrograma() {
    rlutil::setColor(rlutil::LIGHTRED);
    centrarTexto("Muchas gracias por usar la aplicaci�n.", 15);
    rlutil::setColor(rlutil::WHITE);
}

void mensajeAccesoRestringido() {
    std::cout << std::endl;
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "Este men� se encuentra restringido para tu perfil de usuario." << std::endl;
    rlutil::setColor(rlutil::YELLOW);
    std::cout << "Cualquier duda consult� con el administrador de la aplicaci�n." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void mensajeListadoSinDatosEncontrados() {
    std::cout << std::endl;
    rlutil::setColor(rlutil::YELLOW);
    std::cout << "No se encontraron registros relacionados a este listado" << std::endl;
    rlutil::setColor(rlutil::WHITE);
}
