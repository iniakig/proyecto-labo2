#include "Programa.h"
#include "../rlutil.h"
#include "../funciones.h"

#include "UsuarioActivo.h"

#include "ClienteMenu.h"

#include <limits>
#include <conio.h>

// Constructores
Programa::Programa(bool estado) {
    setEstadoLogin(estado);
    setEstadoPrograma(estado);
}

// Interfaces

void Programa::login() {
    rlutil::cls();
    std::string usuario;
    std::string contrasenia;
    int limiteIntentos = 3;
    int contadorIntentos = 0;
    bool acceso = false;
    UsuarioActivo usuarioActivo;

    // Usuario y Contrase�a hardcodeado
    std::string us = "admin";
    std::string cs = "admin";

    centrarTexto("SISTEMA DE GESTI�N DE STOCK Y VENTAS", 5 + 3);
    centrarTexto("----------------------------------------------------------", 6 + 3);
    centrarTexto("Ingres� tus credenciales de acceso", 8 + 3);
    rlutil::locate(34, 10 + 3);
    std::cout << "  Usuario: " << std::endl;
    rlutil::locate(34, 12 + 3);
    std::cout << "  Contrase�a: " << std::endl;
    centrarTexto("----------------------------------------------------------", 14 + 3);
    centrarTexto("G3 - Laboratorio de Computaci�n II - UTNFRGP - 1C2023", 15 + 3);

    while (acceso == false && contadorIntentos != limiteIntentos) {
        if (contadorIntentos > 0) {
            rlutil::cls();
            std::string mensajeIngresoIncorrecto = "Ingreso incorrecto. Intento #" + std::to_string(contadorIntentos + 1) + ".";
            centrarTexto("SISTEMA DE GESTI�N DE STOCK Y VENTAS", 5 + 3);
            centrarTexto("----------------------------------------------------------", 6 + 3);
            centrarTexto(mensajeIngresoIncorrecto, 8 + 3);
            rlutil::locate(34, 10 + 3);
            std::cout << "  Usuario: " << std::endl;
            rlutil::locate(34, 12 + 3);
            std::cout << "  Contrase�a: " << std::endl;
            centrarTexto("----------------------------------------------------------", 14 + 3);
            centrarTexto("G3 - Laboratorio de Computaci�n II - UTNFRGP - 1C2023", 15 + 3);
        }
        rlutil::locate(45, 10 + 3);
        getline(std::cin, usuario);

        rlutil::locate(48, 12 + 3);
        /*
        getline(std::cin, contrasenia);
        */

        char caracter;
        contrasenia = "";
        caracter = getch();

        rlutil::locate(48, 12 + 3);
        while (caracter != '\r') { // "13" es el c�digo ASCII de la tecla Enter.
            if (caracter == '\b') { // "127" es Delete.
                if (!contrasenia.empty()) {
                    contrasenia.pop_back(); // Borra �ltimo caracter ingresado
                    std::cout << "\b \b"; // Borra asterisco impreso en consola
                }
            }
            else {
                contrasenia.push_back(caracter);
                std::cout << "*";
            }
            caracter = getch();
        }

        if (usuario == us && contrasenia == cs) {
            acceso = true;
        }
        else {
            contadorIntentos++;
        }
    }

    if (acceso == true) {
        usuarioActivo.setAlias(contrasenia);
        usuarioActivo.crearArchivo(usuarioActivo);
    }
    else {
        centrarTexto("Agot� los 3 intentos. El sistema se cerrar�", 8 + 3);
        setEstadoPrograma(acceso);
    }

    setEstadoLogin(acceso);
}

void Programa::ejecutar() {
    ClienteMenu clienteMenu;
    UsuarioActivo usuarioActivo;

    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "USUARIO ACTIVO: " << usuarioActivo.leerArchivo() << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "MEN� PRINCIPAL" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "1. GESTI�N DE VENTAS" << std::endl;
        std::cout << "2. GESTI�N DE PRODUCTOS" << std::endl;
        std::cout << "3. GESTI�N DE MARCAS" << std::endl;
        std::cout << "4. GESTI�N DE CLIENTES" << std::endl;
        std::cout << "5. INFORMES" << std::endl;
        std::cout << "6. CONFIGURACI�N" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "0. CERRAR SESI�N" << std::endl;
        std::cout << "666. SALIR DEL PROGRAMA" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "OPCI�N SELECCIONADA: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
            case 0:
                setEstadoLogin(false);
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                clienteMenu.mostrar();
                break;
            case 5:
                break;
            case 6:
                break;
            case 666:
                setEstadoPrograma(false);
                setEstadoLogin(false);
                std::cout << std::endl;
                mensajeSalidaDelPrograma();
                rlutil::anykey();
                break;
            default:
                break;
        }
    }

    while (opcion != 0 && opcion != 666);
}


// Setters
void Programa::setEstadoLogin(bool estado) {
    _estadoLogin = estado;
}

void Programa::setEstadoPrograma(bool estado) {
    _estadoPrograma = estado;
}

// Getters
bool Programa::getEstadoLogin() {
    return _estadoLogin;
}

bool Programa::getEstadoPrograma() {
    return _estadoPrograma;
}



