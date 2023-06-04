#include <iostream>

#include "rlutil.h"

#include "funciones.h"
#include "Fecha.h"
#include "Persona.h"
#include "Usuario.h"
#include "Encabezado.h"
#include "PieDePagina.h"
#include "Pantalla.h"
#include "UsuarioArchivo.h"
#include "UsuarioManager.h"


using namespace std;

int main()
{
    setSpanish();

    // Usuario usuario;
    // UsuarioArchivo usuarioArchivo;
    UsuarioManager usuarioManager;

    // usuario = usuarioArchivo.leer(0);

    //usuarioManager.listarActivos();
    //usuarioManager.listarPorAlias();

    // Usuario usuario(1, "33781477", "Nahuel", "Alvez", "nahue.alvez@gmail.com", true, Fecha().fechaActual(), "nalvez", "asdf1234", 0);

    // usuarioArchivo.crear(usuario);

    usuarioManager.listarUsuarios();

    rlutil::anykey();




    // **************** SISTEMA DE GESTI�N DE STOCK Y VENTAS ****************            ----> Encabezado



    //                              �Bienvenido/a!                                       ----> T�tulo de pantalla | titulo
    //             -----------------------------------------------
    //                  Este es tu primer ingreso al sistema.                            ----> Campo de mensaje #1 | mensajeInterno
    //
    //               Te vamos a pedir que ingreses algunos datos                         ----> Cuerpo | cuerpo
    //               para realizar la configuraci�n inicial.
    //             -----------------------------------------------
    //                     Elija una opci�n y presione Enter                             ----> Campo de mensaje #2 | mensajeExterno
    //             -----------------------------------------------
    //               1. CONTINUAR                     666. SALIR                         ----> Opciones | opciones
    //
    //               OPCI�N SELECCIONADA:                                                ----> Ingreso de opci�n
    //


    // **** Proyecto de Laboratorio II - 1er cuatrimestre 2023 - UTNFRGP ****            ----> Pi� de p�gina

 //---------------------------------------------------------------------------- //

    // **************** SISTEMA DE GESTI�N DE STOCK Y VENTAS ****************


    //                          Configuraci�n inicial
    //             -----------------------------------------------
    //                      Ingres� los siguientes datos:
    //
    //               * RAZ�N SOCIAL:
    //               * CUIT:
    //               * DIRECCI�N:
    //               * PISO:            DTO/OF:
    //               * LOCALIDAD:
    //               * CP:
    //             -----------------------------------------------
    //                   �Los datos ingresados son correctos?
    //             -----------------------------------------------
    //             1. NO, REINGRESAR  2. S�, CONTINUAR  666. SALIR
    //
    //               OPCI�N SELECCIONADA:


    // **** Proyecto de Laboratorio II - 1er cuatrimestre 2023 - UTNFRGP ****

 //---------------------------------------------------------------------------- //

    // **************** SISTEMA DE GESTI�N DE STOCK Y VENTAS ****************



    //                   �Tu perfil de empresa ya fue creado!
    //             -----------------------------------------------
    //                 Ingres� los datos para el administrador:
    //
    //               USUARIO:
    //               CONTRASE�A:
    //
    //             -----------------------------------------------
    //                   �Los datos ingresados son correctos?
    //             -----------------------------------------------
    //             1. NO, REINGRESAR              2. S�, CONTINUAR
    //
    //               OPCI�N SELECCIONADA:



    // **** Proyecto de Laboratorio II - 1er cuatrimestre 2023 - UTNFRGP ****

 //---------------------------------------------------------------------------- //

    // **************** SISTEMA DE GESTI�N DE STOCK Y VENTAS ****************



    //                                  Login
    //             -----------------------------------------------
    //                         Ingres� tus credenciales
    //
    //               USUARIO:
    //               CONTRASE�A:
    //
    //             -----------------------------------------------
    //             A los 3 intentos fallidos el sistema se cerrar�
    //             -----------------------------------------------
    //
    //
    //                <Presione cualquier tecla para continuar>



    // **** Proyecto de Laboratorio II - 1er cuatrimestre 2023 - UTNFRGP ****

 //---------------------------------------------------------------------------- //

    // **************** SISTEMA DE GESTI�N DE STOCK Y VENTAS ****************



    //                           GESTI�N DE USUARIOS
    //             -----------------------------------------------
    //
    //               1. CREAR USUARIO
    //               2. MODIFICAR USUARIO
    //               3. ELIMINAR USUARIO
    //               4. LISTAR USUARIOS ACTIVOS
    //               5. RECUPERAR REGISTROS
    //
    //             -----------------------------------------------
    //                     Elija una opci�n y presione Enter
    //             -----------------------------------------------
    //               0. PANTALLA ANTERIOR             666. SALIR
    //
    //               OPCI�N SELECCIONADA:



    // **** Proyecto de Laboratorio II - 1er cuatrimestre 2023 - UTNFRGP ****

    rlutil::setColor(rlutil::LIGHTRED);
    rlutil::locate(12, 26);
    return 0;
}
