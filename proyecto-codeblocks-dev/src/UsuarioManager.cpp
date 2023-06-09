#include "UsuarioManager.h"
#include "../funciones.h"

#include <iostream>
#include <iomanip>
#include <../rlutil.h>

void UsuarioManager::cargar() {
    int tipoDocumento;
    std::string nroDocumento;
    std::string nombre;
    std::string apellido;
    std::string email;
    bool estado;
    Fecha fechaRegistro;
    std::string alias;
    std::string contrasenia;
    int rol;

    tipoDocumento = 1;

    std::cout << "Nro de DNI: ";
    nroDocumento = ingresoDeDocumentoConValidacion();
    std::cout << "Nombre: ";
    nombre = ingresoDeNombreApellidoConValidacion();
    std::cout << "Apellido: ";
    apellido = ingresoDeNombreApellidoConValidacion();
    std::cout << "Email: ";
    email = ingresoDeEmailConValidacion();

    estado = true;
    fechaRegistro = Fecha().fechaActual();

    std::cout << "Alias (Solo letras minúsculas o mayúsculas entre 4 y 14 caracteres): ";
    alias = ingresoDeAliasConValidacion();
    std::cout << "Contraseña: ";
    contrasenia = ingresoDeContraseniaConValidacion();
    std::cout << "Rol (0. Administrador | 1. Supervisor | 2. Vendedor): ";
    std::cin >> rol;


    Usuario usuario(tipoDocumento, nroDocumento.c_str(), nombre.c_str(), apellido.c_str(), email.c_str(), estado, fechaRegistro, alias.c_str(), contrasenia.c_str(), rol);

    if (_archivo.crear(usuario)) {
        std::cout << "El usuario se cargó correctamente.";
    }
    else {
        std::cout << "No se pudo crear el usuario.";
    }
}

void UsuarioManager::listar(Usuario usuario, int tipoListado) {

    // Tipos de listado
    // --------------------
    // 0. Listado detallado
    // 1. Listado resumido (para tabla)

    switch (tipoListado) {
    case 0:
        std::cout << "Tipo de documento: " << usuario.getTipoDocumentoDescripcion() << std::endl;
        std::cout << "Nro de documento: " << usuario.getNroDocumento() << std::endl;
        std::cout << "Alias: " << usuario.getAlias() << std::endl;
        std::cout << "Nombre: " << usuario.getNombre() << std::endl;
        std::cout << "Apellido: " << usuario.getApellido() << std::endl;
        std::cout << "Email: " << usuario.getEmail() << std::endl;
        std::cout << "Fecha de registro: " << usuario.getFechaRegistro().toString() << std::endl;
        std::cout << "Rol: " << usuario.getRolDescripcion() << std::endl;
        break;
    case 1:
        std::cout << std::left;
        std::cout << std::setw(7) << usuario.getTipoDocumentoDescripcion();
        std::cout << std::setw(15) << usuario.getNroDocumento();
        std::cout << std::setw(18) << usuario.getAlias();
        std::cout << std::setw(16) << usuario.getRolDescripcion();
        std::cout << std::setw(13) << usuario.getFechaRegistro().toString();
        break;
    default:
        break;
    }
}

void UsuarioManager::listarPorAlias() {
    // rlutil::cls();
    Usuario usuario;
    int cantidadDeRegistros = _archivo.getCantidadDeUsuarios();
    int posicion;
    std::string alias;

    std::cout << "Ingrese el alias de usuario: ";
    getline(std::cin, alias);
    std::cout << std::endl;

    posicion = _archivo.buscar(alias);

    if (posicion > -1) {
        usuario = _archivo.leer(posicion);
        listar(usuario, 0);
        rlutil::anykey();
    }
    else {
        std::cout << "No se encontró ningún registro con el alias ingresado.";
        rlutil::anykey();
    }
}

void UsuarioManager::listarPorDNI() {
    // rlutil::cls();
    Usuario usuario;
    int cantidadDeRegistros = _archivo.getCantidadDeUsuarios();
    int posicion;
    int tipoDocumento = 1;
    std::string nroDeDocumento;

    std::cout << "Ingrese el nro de DNI del usuario: ";
    nroDeDocumento = ingresoDeDocumentoConValidacion();
    std::cout << std::endl;

    posicion = _archivo.buscar(1, nroDeDocumento);

    if (posicion > -1) {
        usuario = _archivo.leer(posicion);
        listar(usuario, 0);
        rlutil::anykey();
    }
    else {
        std::cout << "No se encontró ningún registro con el DNI ingresado.";
        rlutil::anykey();
    }
}

void UsuarioManager::listarActivos() {
    // rlutil::cls();
    Usuario usuario;
    int cantidadDeRegistros = _archivo.getCantidadDeUsuarios();
    int resultadosEncontrados = 0;

    for (int i = 0; i < cantidadDeRegistros; i++) {
        usuario = _archivo.leer(i);
        if (usuario.getEstado()) {
            resultadosEncontrados++;
        }
    }

    if (resultadosEncontrados > 0) {
        std::cout << "Registros encontrados: " << resultadosEncontrados << std::endl;
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(7) << "Tipo";
        std::cout << std::setw(15) << "N. Documento";
        std::cout << std::setw(18) << "Alias";
        std::cout << std::setw(16) << "Rol";
        std::cout << std::setw(13) << "F. Registro";
        std::cout << std::endl;
        std::cout << "-------------------------------------------------------------------" << std::endl;
        for (int i = 0; i < cantidadDeRegistros; i++) {
            usuario = _archivo.leer(i);
            if (usuario.getEstado()) {
                listar(usuario, 1);
                std::cout << std::endl;
            }
        }
    }
    else {
        std::cout << "No se encontraron registros con estado activo";
    }

    std::cout << std::endl;
    rlutil::anykey();
}

void UsuarioManager::listarInactivos() {
    // rlutil::cls();
    Usuario usuario;
    int cantidadDeRegistros = _archivo.getCantidadDeUsuarios();
    int resultadosEncontrados = 0;

    for (int i = 0; i < cantidadDeRegistros; i++) {
        usuario = _archivo.leer(i);
        if (!usuario.getEstado()) {
            resultadosEncontrados++;
        }
    }

    if (resultadosEncontrados > 0) {
        std::cout << "Registros encontrados: " << resultadosEncontrados << std::endl;
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(7) << "Tipo";
        std::cout << std::setw(15) << "N. Documento";
        std::cout << std::setw(18) << "Alias";
        std::cout << std::setw(16) << "Rol";
        std::cout << std::setw(13) << "F. Registro";
        std::cout << std::endl;
        std::cout << "-------------------------------------------------------------------" << std::endl;
        for (int i = 0; i < cantidadDeRegistros; i++) {
            usuario = _archivo.leer(i);
            if (usuario.getEstado()) {
                listar(usuario, 1);
                std::cout << std::endl;
            }
        }
    }
    else {
        std::cout << "No se encontraron registros con estado inactivo";
    }

    std::cout << std::endl;
    rlutil::anykey();
}

void UsuarioManager::listarUsuarios() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "ELIJA EL TIPO DE LISTADO" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. USUARIO POR ALIAS" << std::endl;
        std::cout << "2. USUARIO POR NRO DE DOCUMENTO" << std::endl;
        std::cout << "3. USUARIOS ACTIVOS" << std::endl;
        std::cout << "4. USUARIOS INACTIVOS" << std::endl;
        std::cout << "5. BÚSQUEDA LIBRE" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "0. VOLVER AL MENÚ DE GESTIÓN DE USUARIOS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "OPCIÓN SELECCIONADA: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
        case 0:
            break;
        case 1:
            std::cout << std::endl;
            listarPorAlias();
            break;
        case 2:
            std::cout << std::endl;
            listarPorDNI();
            break;
        case 3:
            std::cout << std::endl;
            listarActivos();
            break;
        case 4:
            std::cout << std::endl;
            listarInactivos();
            break;
        case 5:

            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}

void UsuarioManager::modificar() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "ELIJA EL CAMPO QUE DESEA MODIFICAR" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. TIPO DE DOCUMENTO" << std::endl;
        std::cout << "2. NRO DE DOCUMENTO" << std::endl;
        std::cout << "3. NOMBRE" << std::endl;
        std::cout << "4. APELLIDO" << std::endl;
        std::cout << "5. ROL" << std::endl;
        std::cout << "6. CONTRASEÑA" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "0. VOLVER AL MENÚ DE GESTIÓN DE USUARIOS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "OPCIÓN SELECCIONADA: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
        case 0:
            break;
        case 1:
            std::cout << std::endl;
            break;
        case 2:
            std::cout << std::endl;
            break;
        case 3:
            std::cout << std::endl;
            break;
        case 4:
            std::cout << std::endl;
            break;
        case 5:

            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}

void UsuarioManager::setPermisos(bool adm, bool sup, bool ven) {
    _permisos[0] = adm;
    _permisos[1] = sup;
    _permisos[2] = ven;
}
