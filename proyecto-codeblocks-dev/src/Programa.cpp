#include "Programa.h"
#include "../rlutil.h"
#include "../funciones.h"
#include "../mensajes.h"
#include "../validaciones.h"

#include <limits>
#include <conio.h>

#include "Usuario.h"
#include "UsuarioArchivo.h"
#include "UsuarioManager.h"
#include "Empresa.h"
#include "EmpresaManager.h"

// Constructores
Programa::Programa() {
    setEstadoPrograma(true);
    setEstadoLogin(false);

    // Checkeo si existe un usuario registrado y seteo el estado de existencia de registros de usuarios
    Usuario Usuario;
    UsuarioArchivo usuarioArchivo;

    if (usuarioArchivo.getCantidadDeUsuarios() > 0) {
        setEstadoUsuarioRegistrado(true);
    }
    else {
        setEstadoUsuarioRegistrado(false);
    }
}

// Interfaces
void Programa::registro() {
    // Registro de usuario
    rlutil::cls();
    centrarTexto("BIENVENIDO AL SISTEMA DE GESTI�N", 1);
    centrarTexto("A CONTINUACI�N PODR� GENERAR EL PRIMER USUARIO DE ACCESO AL SISTEMA", 2);
    std::cout << std::endl;
    UsuarioManager usuarioManager;
    usuarioManager.cargar();


    // Registro de perfil empresa
    rlutil::cls();
    centrarTexto("PARA FINALIZAR EL REGISTRO ES NECESARIO DAR DE ALTA LOS DATOS DE LA EMPRESA", 1);
    std::cout << std::endl;
    EmpresaManager empresaManager;
    empresaManager.cargar();

    setEstadoUsuarioRegistrado(true);
}

void Programa::login() {
    rlutil::cls();
    rlutil::hidecursor();
    std::string usuario;
    std::string contrasenia;
    int id;
    int rol;
    int limiteIntentos = 3;
    int contadorIntentos = 0;
    bool acceso = false;

    Usuario usuarioReg;
    UsuarioArchivo usuarioArchivoReg;

    centrarTexto("SISTEMA DE GESTI�N DE STOCK Y VENTAS", 5 + 3);
    centrarTexto("----------------------------------------------------------", 6 + 3);
    centrarTexto("Ingres� tus credenciales de acceso", 8 + 3);
    rlutil::locate(34, 10 + 3);
    rlutil::showcursor();
    std::cout << "  Usuario: " << std::endl;
    rlutil::locate(34, 12 + 3);
    std::cout << "  Contrase�a: " << std::endl;
    centrarTexto("----------------------------------------------------------", 14 + 3);
    centrarTexto("G3 * Laboratorio de Computaci�n II * UTNFRGP * 1C2023", 15 + 3);

    while (acceso == false && contadorIntentos != limiteIntentos) {
        if (contadorIntentos > 0) {
            rlutil::cls();


            std::string mensajeIngresoIncorrecto = "Ingreso incorrecto. Intento #" + std::to_string(contadorIntentos + 1) + ".";


            centrarTexto("SISTEMA DE GESTI�N DE STOCK Y VENTAS", 5 + 3);
            centrarTexto("----------------------------------------------------------", 6 + 3);
            rlutil::setColor(rlutil::LIGHTRED);
            centrarTexto(mensajeIngresoIncorrecto, 8 + 3);
            rlutil::setColor(rlutil::WHITE);
            rlutil::locate(34, 10 + 3);
            std::cout << "  Usuario: " << std::endl;
            rlutil::locate(34, 12 + 3);
            std::cout << "  Contrase�a: " << std::endl;
            centrarTexto("----------------------------------------------------------", 14 + 3);
            centrarTexto("G3 - Laboratorio de Computaci�n II - UTNFRGP - 1C2023", 15 + 3);
        }

        rlutil::locate(45, 10 + 3);
        rlutil::locate(45, 10 + 3);
        getline(std::cin, usuario);

        rlutil::locate(48, 12 + 3);

        char caracter;
        contrasenia = "";
        caracter = getch();

        rlutil::locate(48, 12 + 3);
        while (caracter != '\r') { // "\r" refiere a Enter.
            if (caracter == '\b') { // "\b" refiere a Delete.
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
        centrarTexto("Agot� los 3 intentos. El sistema se cerrar�.", 8 + 3);
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
        std::cout << "MEN� PRINCIPAL" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "1. GESTI�N DE VENTAS" << std::endl;
        std::cout << "2. GESTI�N DE PRODUCTOS" << std::endl;
        std::cout << "3. GESTI�N DE MARCAS" << std::endl;
        std::cout << "4. GESTI�N DE CLIENTES" << std::endl;
        std::cout << "5. INFORMES" << std::endl;
        std::cout << "6. CONFIGURACI�N" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "0. CERRAR SESI�N  |  666. SALIR DEL PROGRAMA" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "OPCI�N SELECCIONADA: ";
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
                _informesMenu.mostrar();
                break;
            case 6:
                _configuracionMenu.mostrar();
                break;
            case 666:
                setEstadoPrograma(false);
                setEstadoLogin(false);

                rlutil::cls();
                rlutil::hidecursor();
                mensajeSalidaDelPrograma();
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

void Programa::setEstadoUsuarioRegistrado(bool estado) {
    _estadoUsuarioRegistrado = estado;
}

// Getters
bool Programa::getEstadoLogin() {
    return _estadoLogin;
}

bool Programa::getEstadoPrograma() {
    return _estadoPrograma;
}

bool Programa::getEstadoUsuarioRegistrado() {
    return _estadoUsuarioRegistrado;
}


