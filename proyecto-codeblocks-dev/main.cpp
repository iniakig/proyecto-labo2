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
