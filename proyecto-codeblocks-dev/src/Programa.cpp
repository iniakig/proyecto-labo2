#include "Programa.h"
#include "../rlutil.h"
#include "../funciones.h"

#include "ClienteMenu.h"

// Constructores
Programa::Programa(bool estado) {
    setEstado(estado);
}

// Interfaces

void Programa::login() {
    rlutil::cls();
    std::string usuario;
    std::string contrasenia;
    int limiteIntentos = 3;
    int contadorIntentos = 0;
    bool acceso = false;

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

    while (acceso == false && contadorIntentos != 3) {
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
        getline(std::cin, contrasenia);

        if (usuario == us && contrasenia == cs) {
            acceso = true;
        }
        else {
            contadorIntentos++;
        }
    }

    if (_estado == false) {
        centrarTexto("Agot� los 3 intentos. El sistema se cerrar�", 8 + 3);
    }

    _estado = acceso;
}

void Programa::ejecutar() {
    ClienteMenu clienteMenu;

    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "MEN� PRINCIPAL" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "1. GESTI�N DE VENTAS" << std::endl;
        std::cout << "2. GESTI�N DE PRODUCTOS" << std::endl;
        std::cout << "3. GESTI�N DE MARCAS" << std::endl;
        std::cout << "4. GESTI�N DE CLIENTES" << std::endl;
        std::cout << "5. INFORMES" << std::endl;
        std::cout << "6. CONFIGURACI�N" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "0. SALIR DEL PROGRAMA" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "OPCI�N SELECCIONADA: ";
        std::cin >> opcion;

        switch(opcion) {
            case 0:
                std::cout << std::endl;
                mensajeSalidaDelPrograma();
                rlutil::anykey();
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
            default:
                break;
        }
    }

    while (opcion != 0);
}


// Setters
void Programa::setEstado(bool estado) {
    _estado = estado;
}

// Getters
bool Programa::getEstado() {
    return _estado;
}



