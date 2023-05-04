#include <iostream>

#include "rlutil.h"

#include "funciones.h"
#include "Fecha.h"
#include "Persona.h"
#include "Usuario.h"
#include "Encabezado.h"
#include "PieDePagina.h"
#include "Pantalla.h"


using namespace std;

int main()
{
    const int ANCHO = 120;
    // Persona reg;
    // Persona reg(1, "33781477", "Nahuel", "Alvez", "nahue.alvez@gmail.com", true, Fecha().fechaActual());

    // reg.Mostrar();

    setSpanish();

    Encabezado encabezado("SISTEMA DE GESTIÓN DE STOCK Y VENTAS", ANCHO);
    PieDePagina pieDePagina("Proyecto de Laboratorio II - 1er cuatrimestre 2023 - UTNFRGP", ANCHO);


    encabezado.imprimirEncabezado();
    pieDePagina.imprimirPieDePagina();


    // PantallaBase inicio("Título de pantalla", "Esto es un mensaje en la cabecera", "Este es el cuerpo del mensaje con varias líneas.\n\t\t\t   Esto nos permite poder visualizar más texto de información.\n\t\t\t   Además, ¡queda bien!.", "Elegí una opción y presioná <Enter>", "1. CONTINUAR  |  666. SALIR", "OPCIÓN SELECCIONADA: ");

    Pantalla pantalla;

    pantalla.desplegarLogin();
    rlutil::anykey();
    rlutil::cls();
    pantalla.desplegarCrearPrimerAdmin();


    rlutil::anykey();




    // **************** SISTEMA DE GESTIÓN DE STOCK Y VENTAS ****************            ----> Encabezado



    //                              ¡Bienvenido/a!                                       ----> Título de pantalla | titulo
    //             -----------------------------------------------
    //                  Este es tu primer ingreso al sistema.                            ----> Campo de mensaje #1 | mensajeInterno
    //
    //               Te vamos a pedir que ingreses algunos datos                         ----> Cuerpo | cuerpo
    //               para realizar la configuración inicial.
    //             -----------------------------------------------
    //                     Elija una opción y presione Enter                             ----> Campo de mensaje #2 | mensajeExterno
    //             -----------------------------------------------
    //               1. CONTINUAR                     666. SALIR                         ----> Opciones | opciones
    //
    //               OPCIÓN SELECCIONADA:                                                ----> Ingreso de opción
    //


    // **** Proyecto de Laboratorio II - 1er cuatrimestre 2023 - UTNFRGP ****            ----> Pié de página

 //---------------------------------------------------------------------------- //

    // **************** SISTEMA DE GESTIÓN DE STOCK Y VENTAS ****************


    //                          Configuración inicial
    //             -----------------------------------------------
    //                      Ingresá los siguientes datos:
    //
    //               * RAZÓN SOCIAL:
    //               * CUIT:
    //               * DIRECCIÓN:
    //               * PISO:            DTO/OF:
    //               * LOCALIDAD:
    //               * CP:
    //             -----------------------------------------------
    //                   ¿Los datos ingresados son correctos?
    //             -----------------------------------------------
    //             1. NO, REINGRESAR  2. SÍ, CONTINUAR  666. SALIR
    //
    //               OPCIÓN SELECCIONADA:


    // **** Proyecto de Laboratorio II - 1er cuatrimestre 2023 - UTNFRGP ****

 //---------------------------------------------------------------------------- //

    // **************** SISTEMA DE GESTIÓN DE STOCK Y VENTAS ****************



    //                   ¡Tu perfil de empresa ya fue creado!
    //             -----------------------------------------------
    //                 Ingresá los datos para el administrador:
    //
    //               USUARIO:
    //               CONTRASEÑA:
    //
    //             -----------------------------------------------
    //                   ¿Los datos ingresados son correctos?
    //             -----------------------------------------------
    //             1. NO, REINGRESAR              2. SÍ, CONTINUAR
    //
    //               OPCIÓN SELECCIONADA:



    // **** Proyecto de Laboratorio II - 1er cuatrimestre 2023 - UTNFRGP ****

 //---------------------------------------------------------------------------- //

    // **************** SISTEMA DE GESTIÓN DE STOCK Y VENTAS ****************



    //                                  Login
    //             -----------------------------------------------
    //                         Ingresá tus credenciales
    //
    //               USUARIO:
    //               CONTRASEÑA:
    //
    //             -----------------------------------------------
    //             A los 3 intentos fallidos el sistema se cerrará
    //             -----------------------------------------------
    //
    //
    //                <Presione cualquier tecla para continuar>



    // **** Proyecto de Laboratorio II - 1er cuatrimestre 2023 - UTNFRGP ****

 //---------------------------------------------------------------------------- //

    // **************** SISTEMA DE GESTIÓN DE STOCK Y VENTAS ****************



    //                           GESTIÓN DE USUARIOS
    //             -----------------------------------------------
    //
    //               1. CREAR USUARIO
    //               2. MODIFICAR USUARIO
    //               3. ELIMINAR USUARIO
    //               4. LISTAR USUARIOS ACTIVOS
    //               5. RECUPERAR REGISTROS
    //
    //             -----------------------------------------------
    //                     Elija una opción y presione Enter
    //             -----------------------------------------------
    //               0. PANTALLA ANTERIOR             666. SALIR
    //
    //               OPCIÓN SELECCIONADA:



    // **** Proyecto de Laboratorio II - 1er cuatrimestre 2023 - UTNFRGP ****

 //---------------------------------------------------------------------------- //

    // **************** SISTEMA DE GESTIÓN DE STOCK Y VENTAS ****************



    //                              MENÚ PRINCIPAL
    //             -----------------------------------------------
    //
    //               1. GESTIÓN DE STOCK
    //               2. GESTIÓN DE VENTAS
    //               3. GESTIÓN DE CLIENTES
    //               5. REPORTERÍA
    //               6. GESTIÓN DE USUARIOS
    //               7. CONFIGURACIONES
    //
    //             -----------------------------------------------
    //                     Elija una opción y presione Enter
    //             -----------------------------------------------
    //               0. PANTALLA ANTERIOR             666. SALIR
    //
    //               OPCIÓN SELECCIONADA:



    // **** Proyecto de Laboratorio II - 1er cuatrimestre 2023 - UTNFRGP ****

    rlutil::setColor(rlutil::LIGHTRED);
    rlutil::locate(12, 26);
    return 0;
}
