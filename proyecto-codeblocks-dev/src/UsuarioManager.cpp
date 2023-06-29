#include "UsuarioManager.h"

#include <iostream>
#include <iomanip>
#include <../rlutil.h>
#include "../funciones.h"
#include "../validaciones.h"
#include "../mensajes.h"

#include "Usuario.h"

// Métodos privados

int UsuarioManager::generarId() {
   return _archivo.getCantidadDeUsuarios() + 1;
}

void UsuarioManager::listar(Usuario usuario, int tipoListado) {

    // Tipos de listado
    // --------------------
    // 0. Listado detallado
    // 1. Listado resumido (para tabla)

    switch (tipoListado) {
    case 0:
        std::cout << "Id: " << usuario.getId() << std::endl;
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
        std::cout << std::setw(6) << usuario.getId();
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
    rlutil::cls();
    Usuario usuario;
    std::string alias;

    std::cout << "USUARIO POR ALIAS" << std::endl;
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Ingrese el alias de usuario: ";
    getline(std::cin, alias);
    alias = stringAMayus(alias);
    std::cout << std::endl;

    int posicion = _archivo.buscarPorAlias(alias);

    if (posicion > -1) {
        usuario = _archivo.leer(posicion);
        listar(usuario, 0);
        mensajeFinDelListado();
        rlutil::anykey();
    }
    else {
        registroNoEncontradoMensaje();
        rlutil::anykey();
    }
}

void UsuarioManager::listarPorDNI() {
    rlutil::cls();
    Usuario usuario;
    int tipoDocumento = 1;
    std::string nroDeDocumento;

    std::cout << "USUARIO POR DNI" << std::endl;
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Ingrese el nro de DNI del usuario: ";
    nroDeDocumento = ingresoDeDocumentoConValidacion();
    std::cout << std::endl;

    int posicion = _archivo.buscar(tipoDocumento, nroDeDocumento);

    if (posicion > -1) {
        usuario = _archivo.leer(posicion);
        listar(usuario, 0);
        mensajeFinDelListado();
        rlutil::anykey();
    }
    else {
        std::cout << "No se encontró ningún registro con el DNI ingresado.";
        rlutil::anykey();
    }
}

void UsuarioManager::listarActivos() {
    rlutil::cls();
    std::cout << "USUARIOS ACTIVOS" << std::endl;
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    int cantidadDeRegistros = _archivo.getCantidadDeUsuarios();
    Usuario *listaDeUsuarios = new Usuario[cantidadDeRegistros];
    int resultadosEncontrados = 0;

    if (listaDeUsuarios == nullptr) {
        std::cout << "Ocurrió un error al visualizar el listado" << std::endl;
        return;
    }

    _archivo.leer(listaDeUsuarios, cantidadDeRegistros);

    for (int i = 0; i < cantidadDeRegistros; i++) {
        if (listaDeUsuarios[i].getEstado()) {
            resultadosEncontrados++;
        }
    }

    if (resultadosEncontrados > 0) {
        std::cout << "El listado se listará por defecto ordenado por Alias de la A a la Z" << std::endl;
        std::cout << "¿Desea cambiar el ordenamiento a por fecha de forma descendente? (SI | NO): ";
        std::string decision = ingresoDeDecisionConValidacion();
        std::cout << std::endl;

        if (decision == "SI") {
            ordenarPorFecha(listaDeUsuarios, cantidadDeRegistros);
        }
        else {
            ordenarPorAlias(listaDeUsuarios, cantidadDeRegistros);
        }

        std::cout << "Registros encontrados: " << resultadosEncontrados << std::endl;
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(6) << "Id";
        std::cout << std::setw(7) << "Tipo";
        std::cout << std::setw(15) << "N. Documento";
        std::cout << std::setw(18) << "Alias";
        std::cout << std::setw(16) << "Rol";
        std::cout << std::setw(13) << "F. Registro";
        std::cout << std::endl;
        std::cout << "-------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < cantidadDeRegistros; i++) {
            if (listaDeUsuarios[i].getEstado()) {
                listar(listaDeUsuarios[i], 1);
                std::cout << std::endl;
            }
        }
        mensajeFinDelListado();
    }
    else {
        mensajeListadoSinDatosEncontrados();
    }

    delete[] listaDeUsuarios;
    rlutil::anykey();
}

void UsuarioManager::listarInactivos() {
    rlutil::cls();
    std::cout << "USUARIOS INACTIVOS" << std::endl;
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    int cantidadDeRegistros = _archivo.getCantidadDeUsuarios();
    Usuario *listaDeUsuarios = new Usuario[cantidadDeRegistros];
    int resultadosEncontrados = 0;

    if (listaDeUsuarios == nullptr) {
        std::cout << "Ocurrió un error al visualizar el listado" << std::endl;
        return;
    }

    _archivo.leer(listaDeUsuarios, cantidadDeRegistros);


    for (int i = 0; i < cantidadDeRegistros; i++) {
        if (!listaDeUsuarios[i].getEstado()) {
            resultadosEncontrados++;
        }
    }

    if (resultadosEncontrados > 0) {
        std::cout << "El listado se listará por defecto ordenado por Alias de la A a la Z" << std::endl;
        std::cout << "¿Desea cambiar el ordenamiento a por fecha de forma descendente? (SI | NO): ";
        std::string decision = ingresoDeDecisionConValidacion();
        std::cout << std::endl;

        if (decision == "SI") {
            ordenarPorFecha(listaDeUsuarios, cantidadDeRegistros);
        }
        else {
            ordenarPorAlias(listaDeUsuarios, cantidadDeRegistros);
        }

        std::cout << "Registros encontrados: " << resultadosEncontrados << std::endl;
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(6) << "Id";
        std::cout << std::setw(7) << "Tipo";
        std::cout << std::setw(15) << "N. Documento";
        std::cout << std::setw(18) << "Alias";
        std::cout << std::setw(16) << "Rol";
        std::cout << std::setw(13) << "F. Registro";
        std::cout << std::endl;
        std::cout << "-------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < cantidadDeRegistros; i++) {
            if (!listaDeUsuarios[i].getEstado()) {
                listar(listaDeUsuarios[i], 1);
                std::cout << std::endl;
            }
        }

        mensajeFinDelListado();
    }
    else {
        mensajeListadoSinDatosEncontrados();
    }

    delete[] listaDeUsuarios;
    rlutil::anykey();
}

void UsuarioManager::listarPorBusquedaLibre() {
    rlutil::cls();
    std::string cadenaDeBusquedaLibre;


    std::cout << "USUARIOS POR BÚSQUEDA LIBRE" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Ingrese nombre, apellido, alias o DNI: ";
    getline(std::cin, cadenaDeBusquedaLibre);

    cadenaDeBusquedaLibre = stringAMayus(cadenaDeBusquedaLibre);

    int cantidadDeRegistros = _archivo.getCantidadDeUsuarios();
    Usuario *listaDeUsuarios = new Usuario[cantidadDeRegistros];
    int resultadosEncontrados = 0;

    if (listaDeUsuarios == nullptr) {
        std::cout << "Ocurrió un error al visualizar el listado" << std::endl;
        return;
    }

    _archivo.leer(listaDeUsuarios, cantidadDeRegistros);

    for (int i = 0; i < cantidadDeRegistros; i++) {
        std::string datosConcatenados = "";
        std::string nombre(listaDeUsuarios[i].getNombre());
        std::string apellido(listaDeUsuarios[i].getApellido());
        std::string alias(listaDeUsuarios[i].getAlias());
        std::string dni(listaDeUsuarios[i].getNroDocumento());

        datosConcatenados += nombre;
        datosConcatenados += " ";
        datosConcatenados += apellido;
        datosConcatenados += " ";
        datosConcatenados += alias;
        datosConcatenados += " ";
        datosConcatenados += dni;


        // Implementación con método de cstring strstr()
        if (strstr(datosConcatenados.c_str(), cadenaDeBusquedaLibre.c_str()) != nullptr) {
            resultadosEncontrados++;
        }

        // Implementación con método de string find()
        /*
        if (datosConcatenados.find(cadenaDeBusquedaLibre) > -1) {
            resultadosEncontrados++;
        }
        */
    }

    if (resultadosEncontrados > 0) {
        std::cout << std::endl;
        std::cout << "Registros encontrados: " << resultadosEncontrados << std::endl;
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(6) << "Id";
        std::cout << std::setw(7) << "Tipo";
        std::cout << std::setw(15) << "N. Documento";
        std::cout << std::setw(18) << "Alias";
        std::cout << std::setw(16) << "Rol";
        std::cout << std::setw(13) << "F. Registro";
        std::cout << std::endl;
        std::cout << "-------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < cantidadDeRegistros; i++) {
            std::string datosConcatenados = "";
            std::string nombre(listaDeUsuarios[i].getNombre());
            std::string apellido(listaDeUsuarios[i].getApellido());
            std::string alias(listaDeUsuarios[i].getAlias());
            std::string dni(listaDeUsuarios[i].getNroDocumento());

            datosConcatenados += nombre;
            datosConcatenados += " ";
            datosConcatenados += apellido;
            datosConcatenados += " ";
            datosConcatenados += alias;
            datosConcatenados += " ";
            datosConcatenados += dni;

            // Implementación con método de cstring strstr()
            if (strstr(datosConcatenados.c_str(), cadenaDeBusquedaLibre.c_str()) != nullptr) {
                listar(listaDeUsuarios[i], 1);
                std::cout << std::endl;
            }

            // Implementación con método de string find()
            /*
            if (datosConcatenados.find(cadenaDeBusquedaLibre) > -1) {
                listar(listaDeUsuarios[i], 1);
                std::cout << std::endl;
            }
            */
        }

        mensajeFinDelListado();
    }
    else {
        mensajeListadoSinDatosEncontrados();
    }

    delete[] listaDeUsuarios;
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

void UsuarioManager::ordenarPorAlias(Usuario *listaDeUsuarios, int cantidadDeRegistros) {
    Usuario usuarioAux;
    int menor = 0; // Menor porque es de la A a la Z

    for (int i = 0; i < cantidadDeRegistros - 1; i++) {
        menor = i;
        for (int j = i + 1; j < cantidadDeRegistros; j++) {
            if (strcmp(listaDeUsuarios[j].getAlias(), listaDeUsuarios[menor].getAlias()) < 0) {
                menor = j;
            }
        }

        if (i != menor) {
            usuarioAux = listaDeUsuarios[i];
            listaDeUsuarios[i] = listaDeUsuarios[menor];
            listaDeUsuarios[menor] = usuarioAux;
        }
    }
}

// Métodos públicos

void UsuarioManager::cargar() {
    int id;
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

    std::cout << "CARGAR USUARIO" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;

    tipoDocumento = 1;

    id = generarId();
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


    Usuario usuario(id,tipoDocumento, nroDocumento.c_str(), nombre.c_str(), apellido.c_str(), email.c_str(), estado, fechaRegistro, alias.c_str(), contrasenia.c_str(), rol);

    if (_archivo.crear(usuario)) {
        okMensajeCreacion();
    }
    else {
        errorMensajeCreacion();
    }
    rlutil::anykey();
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
                        okMensajeModificacion();
                        opcion = 0;
                    }
                    else {
                        errorMensajeModificacion();
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
                        okMensajeModificacion();
                        opcion = 0;
                    }
                    else {
                        errorMensajeModificacion();
                        opcion = 0;
                    }
                case 3:
                    std::cout << std::endl;
                    std::cout << "Ingrese el nuevo email: ";
                    email = ingresoDeEmailConValidacion();
                    std::cout << std::endl;

                    usuario.setEmail(email.c_str());

                    if (_archivo.modificar(usuario, posicion)) {
                        okMensajeModificacion();
                        opcion = 0;
                    }
                    else {
                        errorMensajeModificacion();
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
                        okMensajeModificacion();
                        opcion = 0;
                    }
                    else {
                        errorMensajeModificacion();
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
                        okMensajeModificacion();
                        opcion = 0;
                    }
                    else {
                        errorMensajeModificacion();
                        opcion = 0;
                    }
                case 6:
                    std::cout << std::endl;
                    std::cout << "Ingrese el nuevo rol (0. Administrador | 1. Supervisor | 2. Vendedor): ";
                    rol = ingresoDeRolConValidacion();
                    std::cout << std::endl;

                    usuario.setRol(rol);

                    if (_archivo.modificar(usuario, posicion)) {
                        okMensajeModificacion();
                        opcion = 0;
                    }
                    else {
                        errorMensajeModificacion();
                        opcion = 0;
                    }
                default:
                    std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
                    break;
                }
            }

            while(opcion != 0);
        }
        else {
            errorMensajeModificacion();
        }
    }
    else {
        registroNoEncontradoMensaje();
    }
    rlutil::anykey();
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
                okMensajeBaja();
            }
            else {
                errorMensajeBaja();
            }
        }
        else {
            registroNoEncontradoMensaje();
        }
    }
    else {
        registroNoEncontradoMensaje();
    }
    rlutil::anykey();
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
                okMensajeReactivacion();
            }
            else {
                errorMensajeReactivacion();
            }
        }
        else {
            registroNoEncontradoMensaje();
        }
    }
    else {
        registroNoEncontradoMensaje();
    }
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
            listarPorAlias();
            break;
        case 2:
            listarPorDNI();
            break;
        case 3:
            listarActivos();
            break;
        case 4:
            listarInactivos();
            break;
        case 5:
            listarPorBusquedaLibre();
            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
}

void UsuarioManager::hacerCopiaDeSeguridad() {
    int cantidadDeUsuarios = _archivo.getCantidadDeUsuarios();
    if(cantidadDeUsuarios <= 0)
    {
        errorMensajeCopiaDeSeguridadSinRegs();
        rlutil::anykey();
        return;
    }

    Usuario* listaDeUsuarios = new Usuario[cantidadDeUsuarios];

    if (listaDeUsuarios == nullptr)
    {
        errorMensajeCopiaDeSeguridad();
        return;
    }

    _archivo.leer(listaDeUsuarios, cantidadDeUsuarios);
    _archivoBkp.vaciar();

    if(_archivoBkp.crear(listaDeUsuarios, cantidadDeUsuarios))
    {
        okMensajeCopiaDeSeguridad();
    }
    else
    {
        errorMensajeCopiaDeSeguridad();
    }

    delete[] listaDeUsuarios;
    rlutil::anykey();
}

void UsuarioManager::restaurarCopiaDeSeguridad() {
    int cantidadDeUsuarios = _archivoBkp.getCantidadDeUsuarios();
    if(cantidadDeUsuarios <= 0)
    {
        errorMensajeCopiaDeSeguridadSinRegs();
        rlutil::anykey();
        return;
    }

    Usuario *listaDeUsuarios = new Usuario[cantidadDeUsuarios];

    if (listaDeUsuarios == nullptr)
    {
        errorMensajeRestauracionCopiaDeSeguridad();
        return;
    }

    _archivoBkp.leer(listaDeUsuarios, cantidadDeUsuarios);
    _archivo.vaciar();

    if(_archivo.crear(listaDeUsuarios, cantidadDeUsuarios))
    {
        okMensajeRestauracionCopiaDeSeguridad();
    }
    else
    {
        errorMensajeRestauracionCopiaDeSeguridad();
    }

    delete[] listaDeUsuarios;
    rlutil::anykey();
}

void UsuarioManager::setPermisos(bool adm, bool sup, bool ven) {
    _permisos[0] = adm;
    _permisos[1] = sup;
    _permisos[2] = ven;
}
