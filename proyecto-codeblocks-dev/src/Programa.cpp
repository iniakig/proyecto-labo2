#include "Programa.h"
#include "../rlutil.h"
#include "../funciones.h"

#include <limits>
#include <conio.h>

#include "Usuario.h"
#include "UsuarioArchivo.h"

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
    int id;
    int rol;
    int limiteIntentos = 3;
    int contadorIntentos = 0;
    bool acceso = false;

    Usuario usuarioReg;
    UsuarioArchivo usuarioArchivoReg;


    // Usuario y Contraseña hardcodeado
    // std::string us = "admin";
    // std::string cs = "admin";

    centrarTexto("SISTEMA DE GESTIÓN DE STOCK Y VENTAS", 5 + 3);
    centrarTexto("----------------------------------------------------------", 6 + 3);
    centrarTexto("Ingresá tus credenciales de acceso", 8 + 3);
    rlutil::locate(34, 10 + 3);
    std::cout << "  Usuario: " << std::endl;
    rlutil::locate(34, 12 + 3);
    std::cout << "  Contraseña: " << std::endl;
    centrarTexto("----------------------------------------------------------", 14 + 3);
    centrarTexto("G3 * Laboratorio de Computación II * UTNFRGP * 1C2023", 15 + 3);

    while (acceso == false && contadorIntentos != limiteIntentos) {
        if (contadorIntentos > 0) {
            rlutil::cls();


            std::string mensajeIngresoIncorrecto = "Ingreso incorrecto. Intento #" + std::to_string(contadorIntentos + 1) + ".";


            centrarTexto("SISTEMA DE GESTIÓN DE STOCK Y VENTAS", 5 + 3);
            centrarTexto("----------------------------------------------------------", 6 + 3);
            rlutil::setColor(rlutil::LIGHTRED);
            centrarTexto(mensajeIngresoIncorrecto, 8 + 3);
            rlutil::setColor(rlutil::WHITE);
            rlutil::locate(34, 10 + 3);
            std::cout << "  Usuario: " << std::endl;
            rlutil::locate(34, 12 + 3);
            std::cout << "  Contraseña: " << std::endl;
            centrarTexto("----------------------------------------------------------", 14 + 3);
            centrarTexto("G3 - Laboratorio de Computación II - UTNFRGP - 1C2023", 15 + 3);
        }

        rlutil::locate(45, 10 + 3);
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
        while (caracter != '\r') { // "\r" refiere a Enter.
            if (caracter == '\b') { // "\b" refiere a Delete.
                if (!contrasenia.empty()) {
                    contrasenia.pop_back(); // Borra último caracter ingresado
                    std::cout << "\b \b"; // Borra asterisco impreso en consola
                }
            }
            else {
                contrasenia.push_back(caracter);
                std::cout << "*";
            }
            caracter = getch();
        }

        usuario = stringAMayus(usuario);

        int cantidadDeUsuarios = usuarioArchivoReg.getCantidadDeUsuarios();

        for (int i = 0; i < cantidadDeUsuarios; i++) {
            usuarioReg = usuarioArchivoReg.leer(i);
            if (strcmp(usuarioReg.getAlias(), usuario.c_str()) == 0 && strcmp(usuarioReg.getContrasenia(), contrasenia.c_str()) == 0) {
                acceso = true;
                id = usuarioReg.getId();
                rol = usuarioReg.getRol(); // Le asigno a la variable rol el rol del usuario encontrado
            }
        }

        if (acceso == false) {
            contadorIntentos++;
        }
    }

    if (acceso == true) {
        _usuarioActivo.setId(id); // Seteo en usuarioActivo el id del usuario logueado
        _usuarioActivo.setRol(rol); // Seteo en usaurioActivo el rol del usuario logueado
        _usuarioActivo.crearArchivo(_usuarioActivo);
    }
    else {
        rlutil::setColor(rlutil::LIGHTRED);
        centrarTexto("Agotó los 3 intentos. El sistema se cerrará", 8 + 3);
        rlutil::setColor(rlutil::WHITE);
        setEstadoPrograma(acceso);
    }

    setEstadoLogin(acceso);
}

void Programa::ejecutar() {
    UsuarioArchivo usuarioArchivo;
    Usuario usuario;
    int posicion;

    posicion = usuarioArchivo.buscar(_usuarioActivo.getIdUsuarioActivo());
    usuario = usuarioArchivo.leer(posicion);

    std::string aliasUsuarioActivo(usuario.getAlias());

    int opcion = -1;

    do {
        rlutil::cls();
        rlutil::setColor(rlutil::LIGHTGREEN);
        std::cout << "USUARIO ACTIVO: " << aliasUsuarioActivo << std::endl;
        rlutil::setColor(rlutil::WHITE);
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "MENÚ PRINCIPAL" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "1. GESTIÓN DE VENTAS" << std::endl;
        std::cout << "2. GESTIÓN DE PRODUCTOS" << std::endl;
        std::cout << "3. GESTIÓN DE MARCAS" << std::endl;
        std::cout << "4. GESTIÓN DE CLIENTES" << std::endl;
        std::cout << "5. INFORMES" << std::endl;
        std::cout << "6. CONFIGURACIÓN" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "0. CERRAR SESIÓN  |  666. SALIR DEL PROGRAMA" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "OPCIÓN SELECCIONADA: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
            case 0:
                setEstadoLogin(false);
                break;
            case 1:
                _ventaMenu.Mostrar();
                break;
            case 2:
                _productoMenu.mostrar();
                break;
            case 3:
                _marcaMenu.mostrar();
                break;
            case 4:
                _clienteMenu.mostrar();
                break;
            case 5:
                break;
            case 6:
                _configuracionMenu.mostrar();
                break;
            case 666:
                setEstadoPrograma(false);
                setEstadoLogin(false);

                rlutil::cls();
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



