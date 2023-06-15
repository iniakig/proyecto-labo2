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
#include "Producto.h"
#include "MarcaManager.h"
#include "MarcaArchivo.h"
#include "MarcaMenu.h"
#include "ClienteMenu.h"
#include "Programa.h"


using namespace std;

int main()
{
    setSpanish();

    // UsuarioArchivo usuarioArchivo;

    // Usuario usuario(1, "33781477", "NAHUEL", "ALVEZ", "nalvez@gmail.com", true, Fecha(13, 6, 2023), "NALVEZ", "$nalvez1234", 0);

    // usuarioArchivo.modificar(usuario, 0);

    // UsuarioArchivo usuarioArchivo;

    // usuarioArchivo.crear(usuario);


    Programa programa;

    programa.setEstadoPrograma(true);

    while (programa.getEstadoPrograma() == true) {
        programa.login();
        while(programa.getEstadoLogin() == true) {
            programa.ejecutar();
        }
    }



    //ClienteMenu clienteMenu;

    //clienteMenu.mostrar();

    //MarcaMenu menu;
    //MarcaManager manager;

    //menu.mostrar();

    //manager.hacerCopiaSeguridad();
    //manager.restaurarCopiaSeguridad();
    //manager.listarTodos();
    //manager.modificar();
    //manager.listarXID();
    //manager.listarXNombre();
    /// POSIBLE SOLUCION PARA CARGAR MARCA DESDE PRODUCTO ///
    /*int id;
    do
    {
        std::string nombre = ingresoDeMarcaConValidacion();
        Marca reg;
        reg = manager.cargarDesdeProducto(nombre);
        id = reg.getID();
        cout<<id;
    }
    while(id==0);*/
    //---------------------------------------------------------------//

    //archivo.vaciar();
    //manager.cargar();

    /*int ID, stock;
    Marca marca;
    std::string modelo, descrip;
    float precio;
    bool activo = true;

    cin>>ID;
    cin.ignore();
    getline(cin, modelo);
    getline(cin, descrip);
    cin>>precio;
    cin>>stock;
    Producto produ(ID,marca,modelo,descrip,precio,stock,activo);
    cout<<"--------------------------------------------------------"<<endl;
    cout<<"ID: "<<produ.getID()<<endl;
    cout<<"Marca: "<<produ.getMarca().getNombre()<<endl;
    cout<<"Modelo: "<<produ.getModelo()<<endl;
    cout<<"Descripcion: "<<produ.getDescripcion()<<endl;
    cout<<"Precio $: "<<produ.getPrecio()<<endl;
    cout<<"Stock: "<< produ.getStock()<<endl;
    cout<<"Esctado: "<<produ.getActivo()<<endl;*/

    //Producto(int ID, Marca marca, std::string modelo, std::string descripcion, float precioVenta, int stock, bool activo);
    // Usuario usuario;
    // UsuarioArchivo usuarioArchivo;
    //UsuarioManager usuarioManager;

    // usuario = usuarioArchivo.leer(0);

    //usuarioManager.listarActivos();
    //usuarioManager.listarPorAlias();

    // Usuario usuario(1, "33781477", "Nahuel", "Alvez", "nahue.alvez@gmail.com", true, Fecha().fechaActual(), "nalvez", "asdf1234", 0);

    // usuarioArchivo.crear(usuario);

    //usuarioManager.listarUsuarios();




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

    rlutil::setColor(rlutil::LIGHTRED);
    rlutil::locate(12, 26);
    return 0;
}
