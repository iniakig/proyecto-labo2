#include "UsuarioManager.h"
#include "../funciones.h"

#include <iostream>
#include <iomanip>
#include <../rlutil.h>

#include "Usuario.h"

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
    std::string alias;

    std::cout << "Ingrese el alias de usuario: ";
    getline(std::cin, alias);
    std::cout << std::endl;

    int posicion = _archivo.buscar(alias);

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
    int tipoDocumento = 1;
    std::string nroDeDocumento;

    std::cout << "Ingrese el nro de DNI del usuario: ";
    nroDeDocumento = ingresoDeDocumentoConValidacion();
    std::cout << std::endl;

    int posicion = _archivo.buscar(tipoDocumento, nroDeDocumento);

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
    int cantidadDeRegistros = _archivo.getCantidadDeUsuarios();
    Usuario *listaDeUsuarios = new Usuario[cantidadDeRegistros];
    int resultadosEncontrados = 0;

    if (listaDeUsuarios == nullptr) {
        std::cout << "Ocurrió un error al visualizar el listado" << std::endl;
        return;
    }

    _archivo.leer(listaDeUsuarios, cantidadDeRegistros);
    ordenarPorFecha(listaDeUsuarios, cantidadDeRegistros);

    for (int i = 0; i < cantidadDeRegistros; i++) {
        if (listaDeUsuarios[i].getEstado()) {
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
            if (listaDeUsuarios[i].getEstado()) {
                listar(listaDeUsuarios[i], 1);
                std::cout << std::endl;
            }
        }
    }
    else {
        mensajeListadoSinDatosEncontrados();
    }

    delete[] listaDeUsuarios;

    rlutil::anykey();
}

/*
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
*/

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
            if (!usuario.getEstado()) {
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

void UsuarioManager::ordenarPorFecha(Usuario *listaDeUsuarios, int cantidadDeRegistros) {
    Usuario usuarioAux;
    int mayor = 0;

    for (int i = 0; i < cantidadDeRegistros - 1; i++) {
        mayor = i;
        for (int j = i + 1; j < cantidadDeRegistros; j++) {
            if (listaDeUsuarios[j].getFechaRegistro().toString("YYYY/MM/DD") > listaDeUsuarios[mayor].getFechaRegistro().toString("YYYY/MM/DD")) {
                mayor = j;
            }
        }

        if (i != mayor) {
            usuarioAux = listaDeUsuarios[i];
            listaDeUsuarios[i] = listaDeUsuarios[mayor];
            listaDeUsuarios[mayor] = usuarioAux;
        }
    }
}

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
    rol = ingresoDeRolConValidacion();


    Usuario usuario(tipoDocumento, nroDocumento.c_str(), nombre.c_str(), apellido.c_str(), email.c_str(), estado, fechaRegistro, alias.c_str(), contrasenia.c_str(), rol);

    if (_archivo.crear(usuario)) {
        std::cout << std::endl;
        okMensajeCreacion();
    }
    else {
        std::cout << std::endl;
        errorMensajeCreacion();
    }
}

void UsuarioManager::modificar() {
    rlutil::cls();
    Usuario usuario;

    std::string nroDocumento;
    std::string nombre;
    std::string apellido;
    std::string email;
    Fecha fechaRegistro;
    std::string alias;
    std::string contrasenia;
    int rol;

    std::cout << "MODIFICACIÓN DE DATOS DE USUARIO" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "Ingrese nro de documento del usuario a modificar: ";
    nroDocumento = ingresoDeDocumentoConValidacion();
    std::cout << std::endl;

    int posicion = _archivo.buscar(nroDocumento);
    if (posicion > -1) {
        usuario = _archivo.leer(posicion);
        std::cout << "Datos del usuario: " << std::endl;
        listar(usuario, 0);
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "¿Desea modificar datos de este usuario? (SI | NO): ";
        std::string decision = ingresoDeDecisionConValidacion();

        if (decision == "SI") {
            int opcion = -1;
            std::string decision;

            do {
                std::cout << std::endl;
                std::cout << "ELIJA EL CAMPO QUE DESEA MODIFICAR" << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "1. NRO DE DOCUMENTO" << std::endl;
                std::cout << "2. NOMBRE Y APELLIDO" << std::endl;
                std::cout << "3. EMAIL" << std::endl;
                std::cout << "4. ALIAS" << std::endl;
                std::cout << "5. CONTRASEÑA" << std::endl;
                std::cout << "6. ROL" << std::endl;
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
                    std::cout << "Ingrese el nuevo nro de Documento: ";
                    nroDocumento = ingresoDeDocumentoConValidacion();
                    std::cout << std::endl;

                    usuario.setNroDocumento(nroDocumento.c_str());

                    if (_archivo.modificar(usuario, posicion)) {
                        std::cout << std::endl;
                        okMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    else {
                        std::cout << std::endl;
                        errorMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    break;
                case 2:
                    std::cout << std::endl;
                    std::cout << "Ingrese el nuevo nombre: ";
                    nombre = ingresoDeNombreApellidoConValidacion();
                    std::cout << "Ingrese el nuevo apellido: ";
                    apellido = ingresoDeNombreApellidoConValidacion();
                    std::cout << std::endl;

                    usuario.setNombre(nombre.c_str());
                    usuario.setApellido(apellido.c_str());

                    if (_archivo.modificar(usuario, posicion)) {
                        std::cout << std::endl;
                        okMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    else {
                        std::cout << std::endl;
                        errorMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                case 3:
                    std::cout << std::endl;
                    std::cout << "Ingrese el nuevo email: ";
                    email = ingresoDeEmailConValidacion();
                    std::cout << std::endl;

                    usuario.setEmail(email.c_str());

                    if (_archivo.modificar(usuario, posicion)) {
                        std::cout << std::endl;
                        okMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    else {
                        std::cout << std::endl;
                        errorMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    std::cout << std::endl;
                    break;
                case 4:
                    std::cout << std::endl;
                    std::cout << "Ingrese el nuevo alias: ";
                    alias = ingresoDeAliasConValidacion();
                    std::cout << std::endl;

                    usuario.setAlias(alias.c_str());

                    if (_archivo.modificar(usuario, posicion)) {
                        std::cout << std::endl;
                        okMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    else {
                        std::cout << std::endl;
                        errorMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    break;
                case 5:
                    std::cout << std::endl;
                    std::cout << "Ingrese la nueva contraseña: ";
                    contrasenia = ingresoDeContraseniaConValidacion();
                    std::cout << std::endl;

                    usuario.setContrasenia(contrasenia.c_str());

                    if (_archivo.modificar(usuario, posicion)) {
                        std::cout << std::endl;
                        okMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    else {
                        std::cout << std::endl;
                        errorMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                case 6:
                    std::cout << std::endl;
                    std::cout << "Ingrese el nuevo rol (0. Administrador | 1. Supervisor | 2. Vendedor): ";
                    rol = ingresoDeRolConValidacion();
                    std::cout << std::endl;

                    usuario.setRol(rol);

                    if (_archivo.modificar(usuario, posicion)) {
                        std::cout << std::endl;
                        okMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    else {
                        std::cout << std::endl;
                        errorMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                default:
                    std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
                    break;
                }
            }

            while(opcion != 0);
        }
    }
    else {
        registroNoEncontradoMensaje();
        rlutil::anykey();
    }
}

void UsuarioManager::darDeBaja() {
    rlutil::cls();
    Usuario usuario;
    std::string nroDocumento;

    std::cout << "Ingrese nro de documento del usuario a dar de baja: ";
    nroDocumento = ingresoDeDocumentoConValidacion();
    std::cout << std::endl;

    int posicion = _archivo.buscar(nroDocumento);
    if (posicion > -1) {
        usuario = _archivo.leer(posicion);
        if (usuario.getEstado()) {
            std::cout << "Datos del usuario: ";
            listar(usuario, 0);
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "¿Desea dar de baja a este usuario? (SI | NO): ";
            std::string decision = ingresoDeDecisionConValidacion();

            if (decision == "SI") {
                usuario.setEstado(false);
            }

            _archivo.modificar(usuario, posicion);

            if (_archivo.modificar(usuario, posicion)) {
                std::cout << std::endl;
                okMensajeBaja();
                rlutil::anykey();
            }
            else {
                std::cout << std::endl;
                errorMensajeBaja();
                rlutil::anykey();
            }
        }
        else {
            std::cout << std::endl;
            registroNoEncontradoMensaje();
            rlutil::anykey();
        }
    }
    else {
        std::cout << std::endl;
        registroNoEncontradoMensaje();
        rlutil::anykey();
    }
}

void UsuarioManager::reactivar() {
    rlutil::cls();
    Usuario usuario;
    std::string nroDocumento;

    std::cout << "Ingrese nro de documento del usuario a dar de baja: ";
    nroDocumento = ingresoDeDocumentoConValidacion();
    std::cout << std::endl;

    int posicion = _archivo.buscar(nroDocumento);
    if (posicion > -1) {
        usuario = _archivo.leer(posicion);
        if (!usuario.getEstado()) {
            std::cout << "Datos del usuario: ";
            listar(usuario, 0);
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "¿Desea reactivar este usuario? (SI | NO): ";
            std::string decision = ingresoDeDecisionConValidacion();

            if (decision == "SI") {
                usuario.setEstado(true);
            }

            _archivo.modificar(usuario, posicion);

            if (_archivo.modificar(usuario, posicion)) {
                std::cout << std::endl;
                okMensajeReactivacion();
                rlutil::anykey();
            }
            else {
                std::cout << std::endl;
                errorMensajeReactivacion();
                rlutil::anykey();
            }
        }
        else {
            std::cout << std::endl;
            registroNoEncontradoMensaje();
            rlutil::anykey();
        }
    }
    else {
        std::cout << std::endl;
        registroNoEncontradoMensaje();
        rlutil::anykey();
    }
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

void UsuarioManager::setPermisos(bool adm, bool sup, bool ven) {
    _permisos[0] = adm;
    _permisos[1] = sup;
    _permisos[2] = ven;
}
