#include "ClienteManager.h"
#include "Cliente.h"

#include "../funciones.h"
#include <../rlutil.h>

#include <iostream>
#include <iomanip>

void ClienteManager::cargar() {
    rlutil::cls();
    int tipoDeCliente;
    int tipoDocumento;
    std::string nroDocumento;
    std::string nombre;
    std::string apellido;
    std::string razonSocial;
    std::string email;
    bool estado;
    Fecha fechaRegistro;
    std::string domicilio;
    std::string localidad;
    int provincia;

    std::cout << "CARGAR NUEVO CLIENTE" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;

    std::cout << "Tipo de Cliente (1. Persona física | 2. Persona jurídica): ";
    tipoDeCliente = ingresoDeTipoDeClienteConValidacion();

    std::cout << "Tipo de documento (1. DNI | 2. CUIT): ";
    tipoDocumento = ingresoTipoDeDocumentoConValidacion();
    std::cout << "Nro de documento: ";
    nroDocumento = ingresoDeDocumentoConValidacion();

    Cliente clienteBuscado;
    int posicionBusqueda = _archivo.buscar(nroDocumento);

    if (posicionBusqueda == -1) {
        switch(tipoDeCliente) {
            case 1:
                std::cout << "Nombre: ";
                nombre = ingresoDeNombreApellidoConValidacion();
                std::cout << "Apellido: ";
                apellido = ingresoDeNombreApellidoConValidacion();
                razonSocial = "null";
                break;
            case 2:
                std::cout << "Razón social: ";
                razonSocial = ingresoDeRazonSocialConValidacion();
                nombre = "null";
                apellido = "null";
                break;
        }

        std::cout << "Email: ";
        email = ingresoDeEmailConValidacion();
        estado = true;
        fechaRegistro = Fecha().fechaActual();
        std::cout << "Domicilio: ";
        domicilio = ingresoDeDomicilioConValidacion();
        std::cout << "Localidad: ";
        localidad = ingresoDeLocalidadConValidacion();
        std::cout << "Seleccionar provincia: " << std::endl;
        std::cout << std::endl;
        listarProvincias();
        std::cout << std::endl;
        std::cout << "Nro de provincia: ";
        provincia = ingresoDeProvinciaConValidacion();

        Cliente cliente(tipoDocumento, nroDocumento.c_str(), nombre.c_str(), apellido.c_str(), razonSocial.c_str(), email.c_str(), domicilio.c_str(), localidad.c_str(), provincia, estado, fechaRegistro);

        if (_archivo.crear(cliente) == true) {
            std::cout << std::endl;
            okMensajeCreacion();
            rlutil::anykey();
        }
        else {
            std::cout << std::endl;
            errorMensajeCreacion();
            rlutil::anykey();
        }
    }
    else {
        std::cout << std::endl;
        existeRegistroMensaje();
        rlutil::anykey();
    }
}

void ClienteManager::listar(Cliente cliente, int tipoListado) {
    // Tipos de listado
    // --------------------
    // 0. Listado detallado
    // 1. Listado resumido (para tabla)

    switch (tipoListado) {
    case 0:
        std::cout << "Tipo de documento: " << cliente.getTipoDocumentoDescripcion() << std::endl;
        std::cout << "Nro de documento: " << cliente.getNroDocumento() << std::endl;
        // Si getRazonSocial es "Null" significa que es una persona física
        if (strcmp(cliente.getRazonSocial(),"null") == 0) {
            std::cout << "Nombre: " << cliente.getApellido() << std::endl;
            std::cout << "Apellido: " << cliente.getNombre() << std::endl;
        }
        else {
            std::cout << "Razón Social: " << cliente.getRazonSocial() << std::endl;
        }
        std::cout << "Email: " << cliente.getEmail() << std::endl;
        std::cout << "Domicilio: " << cliente.getDomicilio() << std::endl;
        std::cout << "Fecha de registro: " << cliente.getFechaRegistro().toString() << std::endl;
        std::cout << "Estado: " << cliente.getEstadoDescripcion();
        break;
    case 1:
        std::cout << std::left;
        std::cout << std::setw(7) << cliente.getTipoDocumentoDescripcion();
        std::cout << std::setw(15) << cliente.getNroDocumento();
        std::string null = "null";
        if (strcmp(cliente.getRazonSocial(), null.c_str()) == 0) {
            //std::cout << std::setw(18) << cliente.getNombre();
            //std::cout << std::setw(18) << cliente.getApellido();
            std::string apellidoNombre = std::string(cliente.getApellido()) + " " + std::string(cliente.getNombre());
            std::cout << std::setw(38) << apellidoNombre;
        }
        else {
            std::cout << std::setw(33) << cliente.getRazonSocial();
        }
        std::cout << std::setw(13) << cliente.getFechaRegistro().toString();
        break;
    }
}

void ClienteManager::listarClientes() {
    std::cout << std::endl;
    std::cout << std::endl;
    Cliente cliente;
    int cantidadRegistrosClientes = _archivo.getCantidadDeClientes();

    for (int i = 0; i < cantidadRegistrosClientes; i++) {
        cliente = _archivo.leer(i);
        listar(cliente, 1);
        std::cout << std::endl;
    }
    rlutil::anykey();
}

void ClienteManager::modificar() {
    rlutil::cls();
    Cliente cliente;

    int tipoDeCliente;
    int tipoDeDocumento;
    std::string nroDocumento;
    std::string nombre;
    std::string apellido;
    std::string razonSocial;
    std::string email;
    Fecha fechaRegistro;
    std::string domicilio;
    std::string localidad;
    int provincia;

    std::cout << "MODIFICACIÓN DE DATOS DE CLIENTE" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;

    std::cout << "Ingrese nro de documento del cliente a modificar (Si es CUIT ingrese el número que se ubica entre iones): ";
    nroDocumento = ingresoDeDocumentoConValidacion();
    std::cout << std::endl;

    int posicion = _archivo.buscar(nroDocumento);
    if (posicion > -1) {
        cliente = _archivo.leer(posicion);
        std::cout << "Datos del cliente: " << std::endl;
        listar(cliente, 0);
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "¿Desea modificar datos de este cliente? (SI | NO): ";
        std::string decision = ingresoDeDecisionConValidacion();

        if (decision == "SI") {
            int opcion = -1;
            std::string decision;

            do {
                std::cout << std::endl;
                std::cout << "ELIJA EL CAMPO QUE DESEA MODIFICAR" << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "1. TIPO DE DOCUMENTO Y NRO DE DOCUMENTO" << std::endl;
                std::cout << "2. NOMBRE Y APELLIDO / RAZÓN SOCIAL" << std::endl;
                std::cout << "3. DOMICILIO, LOCALIDAD Y PROVINCIA" << std::endl;
                std::cout << "4. EMAIL" << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "0. VOLVER AL MENÚ DE GESTIÓN DE CLIENTES" << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "OPCIÓN SELECCIONADA: ";
                std::cin >> opcion;
                std::cin.ignore();

                switch(opcion) {
                case 0:
                    break;
                case 1:
                    std::cout << std::endl;
                    std::cout << "Ingrese el nuevo tipo de documento (1. DNI | 2. CUIT): ";
                    tipoDeDocumento = ingresoTipoDeDocumentoConValidacion();
                    std::cout << "Ingrese el nuevo nro de Documento (Debe corresponder con el tipo de Documento registrado): ";
                    nroDocumento = ingresoDeDocumentoConValidacion();
                    std::cout << std::endl;
                    cliente.setTipoDocumento(tipoDeDocumento);
                    cliente.setNroDocumento(nroDocumento.c_str());
                    if (_archivo.modificar(cliente, posicion)) {
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
                    if (cliente.getRazonSocial() != "null") {
                        std::cout << "El cliente está registrado como una persona jurídica" << std::endl;
                        std::cout << "¿Desea modificar el registro como persona física? (SI | NO): ";
                        decision = ingresoDeDecisionConValidacion();

                        if (decision == "SI") {
                            std::cout << "Ingrese el nuevo nombre: ";
                            nombre = ingresoDeNombreApellidoConValidacion();
                            std::cout << "Ingrese el nuevo apellido: ";
                            apellido = ingresoDeNombreApellidoConValidacion();
                            std::cout << std::endl;
                            razonSocial = "null";

                            cliente.setNombre(nombre.c_str());
                            cliente.setApellido(apellido.c_str());
                            cliente.setRazonSocial(razonSocial.c_str());

                            if (_archivo.modificar(cliente, posicion)) {
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
                        }
                        else {
                            std::cout << "Ingrese la nueva razón social: ";
                            razonSocial = ingresoDeRazonSocialConValidacion();
                            std::cout << std::endl;

                            cliente.setRazonSocial(razonSocial.c_str());

                            if (_archivo.modificar(cliente, posicion)) {
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
                        }
                    }
                    else {
                        std::cout << "El cliente está registrado como una persona física" << std::endl;
                        std::cout << "¿Desea modificar el registro como persona jurídica? (SI | NO): ";
                        decision = ingresoDeDecisionConValidacion();

                        if (decision == "SI") {
                            std::cout << "Ingrese la nueva razón social: ";
                            razonSocial = ingresoDeRazonSocialConValidacion();
                            std::cout << std::endl;
                            nombre = "null";
                            apellido = "null";

                            cliente.setRazonSocial(razonSocial.c_str());
                            cliente.setNombre(nombre.c_str());
                            cliente.setApellido(apellido.c_str());

                            if (_archivo.modificar(cliente, posicion)) {
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
                        }
                        else {
                            std::cout << "Ingrese el nuevo nombre: ";
                            nombre = ingresoDeNombreApellidoConValidacion();
                            std::cout << "Ingrese el nuevo apellido: ";
                            apellido = ingresoDeNombreApellidoConValidacion();
                            std::cout << std::endl;
                            razonSocial = "null";

                            cliente.setNombre(nombre.c_str());
                            cliente.setApellido(apellido.c_str());
                            cliente.setRazonSocial(razonSocial.c_str());

                            if (_archivo.modificar(cliente, posicion)) {
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
                        }
                    }
                    std::cout << std::endl;
                    break;
                case 3:
                    std::cout << std::endl;
                    break;
                case 4:
                    std::cout << std::endl;
                    break;
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

void ClienteManager::darDeBaja() {
    rlutil::cls();
    Cliente cliente;
    std::string nroDocumento;

    std::cout << "Ingrese nro de documento del cliente a dar de baja (Si es CUIT ingrese el número que se ubica entre iones): ";
    nroDocumento = ingresoDeDocumentoConValidacion();
    std::cout << std::endl;

    int posicion = _archivo.buscar(nroDocumento);
    if (posicion > -1) {
        cliente = _archivo.leer(posicion);
        if (cliente.getEstado()) {
            std::cout << "Datos del cliente: ";
            listar(cliente, 0);
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "¿Desea dar de baja a este cliente? (SI | NO): ";
            std::string decision = ingresoDeDecisionConValidacion();

            if (decision == "SI") {
                cliente.setEstado(false);
            }

            _archivo.modificar(cliente, posicion);
        }
        else {
            std::cout << std::endl;
            registroNoEncontradoMensaje();
        }
    }
    else {
        std::cout << std::endl;
        registroNoEncontradoMensaje();
    }
}

void ClienteManager::reactivar() {
    rlutil::cls();
    Cliente cliente;
    std::string nroDocumento;

    std::cout << "Ingrese nro de documento del cliente a reactivar (Si es CUIT ingrese el número que se ubica entre iones): ";
    nroDocumento = ingresoDeDocumentoConValidacion();
    std::cout << std::endl;

    int posicion = _archivo.buscar(nroDocumento);
    if (posicion > -1) {
        cliente = _archivo.leer(posicion);
        if (!cliente.getEstado()) {
            std::cout << "Datos del cliente: ";
            listar(cliente, 0);
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "¿Desea reactivar este cliente? (SI | NO): ";
            std::string decision = ingresoDeDecisionConValidacion();

            if (decision == "SI") {
                cliente.setEstado(true);
            }

            _archivo.modificar(cliente, posicion);
        }
        else {
            std::cout << std::endl;
            registroNoEncontradoMensaje();
        }
    }
    else {
        std::cout << std::endl;
        registroNoEncontradoMensaje();
    }
}
