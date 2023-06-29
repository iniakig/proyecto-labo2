#include "ClienteManager.h"
#include "Cliente.h"

#include "../rlutil.h"
#include "../funciones.h"
#include "../mensajes.h"
#include "../validaciones.h"

#include <iostream>
#include <iomanip>
#include <string>

// Métodos privados
int ClienteManager::generarId() {
   return _archivo.getCantidadDeClientes() + 1;
}

void ClienteManager::listarPorNroDeDocumento() {
    rlutil::cls();
    Cliente cliente;
    int tipoDocumento;
    std::string nroDeDocumento;

    std::cout << "LISTAR POR NRO DE DOCUMENTO" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Ingrese el DNI o CUIT del cliente: ";
    nroDeDocumento = ingresoDeDocumentoConValidacion();
    std::cout << std::endl;

    int posicion = _archivo.buscar(nroDeDocumento);

    if (posicion > -1) {
        cliente = _archivo.leer(posicion);
        listar(cliente, 0);
        mensajeFinDelListado();
    }
    else {
        registroNoEncontradoMensaje();
    }

    rlutil::anykey();
}

void ClienteManager::listarActivos() {
    rlutil::cls();
    std::cout << "CLIENTES ACTIVOS" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;

    int cantidadDeRegistros = _archivo.getCantidadDeClientes();
    Cliente *listaDeClientes = new Cliente[cantidadDeRegistros];
    int resultadosEncontrados = 0;

    if(listaDeClientes == nullptr) {
        std::cout << std::endl;
        std::cout << "Ocurrió un error al visualizar el listado" << std::endl;
        return;
    }

    _archivo.leer(listaDeClientes, cantidadDeRegistros);

    for (int i = 0; i < cantidadDeRegistros; i++) {
        if (listaDeClientes[i].getEstado()) {
            resultadosEncontrados++;
        }
    }

    if (resultadosEncontrados > 0) {
        ordenarPorNombre(listaDeClientes, cantidadDeRegistros);
        std::cout << std::endl;
        std::cout << "Registros encontrados: " << resultadosEncontrados << std::endl;
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(6) << "Id";
        std::cout << std::setw(7) << "Tipo";
        std::cout << std::setw(15) << "Nro";
        std::cout << std::setw(38) << "Cliente";
        std::cout << std::setw(13) << "F. Registro";
        std::cout << std::endl;
        std::cout << "-----------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < cantidadDeRegistros; i++) {
            if (listaDeClientes[i].getEstado()) {
                listar(listaDeClientes[i], 1);
                std::cout << std::endl;
            }
        }
        mensajeFinDelListado();
    }
    else {
        mensajeListadoSinDatosEncontrados();
    }

    delete[] listaDeClientes;
    rlutil::anykey();
}

void ClienteManager::listarInactivos() {
    rlutil::cls();
    std::cout << "CLIENTES INACTIVOS" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    int cantidadDeRegistros = _archivo.getCantidadDeClientes();
    Cliente *listaDeClientes = new Cliente[cantidadDeRegistros];
    int resultadosEncontrados = 0;

    if(listaDeClientes == nullptr) {
        std::cout << std::endl;
        std::cout << "Ocurrió un error al visualizar el listado" << std::endl;
        return;
    }

    _archivo.leer(listaDeClientes, cantidadDeRegistros);

    for (int i = 0; i < cantidadDeRegistros; i++) {
        if (!listaDeClientes[i].getEstado()) {
            resultadosEncontrados++;
        }
    }

    if (resultadosEncontrados > 0) {
        ordenarPorNombre(listaDeClientes, cantidadDeRegistros);
        std::cout << std::endl;
        std::cout << "Registros encontrados: " << resultadosEncontrados << std::endl;
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(6) << "Id";
        std::cout << std::setw(7) << "Tipo";
        std::cout << std::setw(15) << "Nro";
        std::cout << std::setw(38) << "Cliente";
        std::cout << std::setw(13) << "F. Registro";
        std::cout << std::endl;
        std::cout << "-----------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < cantidadDeRegistros; i++) {
            if (!listaDeClientes[i].getEstado()) {
                listar(listaDeClientes[i], 1);
                std::cout << std::endl;
            }
        }
        mensajeFinDelListado();
    }
    else {
        mensajeListadoSinDatosEncontrados();
    }

    delete[] listaDeClientes;
    rlutil::anykey();
}

void ClienteManager::listarPorBusquedaLibre() {
    rlutil::cls();
    std::string cadenaDeBusquedaLibre;

    std::cout << "CLIENTES POR BÚSQUEDA LIBRE" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "Ingrese nombre, apellido, razón social o DNI/CUIT: ";
    getline(std::cin, cadenaDeBusquedaLibre);

    cadenaDeBusquedaLibre = stringAMayus(cadenaDeBusquedaLibre);

    int cantidadDeRegistros = _archivo.getCantidadDeClientes();
    Cliente* listaDeClientes = new Cliente[cantidadDeRegistros];

    int resultadosEncontrados = 0;

    if (listaDeClientes == nullptr) {
        std::cout << "Ocurrió un error al visualizar el listado" << std::endl;
        return;
    }

    _archivo.leer(listaDeClientes, cantidadDeRegistros);

    for (int i = 0; i < cantidadDeRegistros; i++) {
        std::string datosConcatenados = "";

        std::string nombre(listaDeClientes[i].getNombre());
        std::string apellido(listaDeClientes[i].getApellido());
        std::string razonSocial(listaDeClientes[i].getRazonSocial());
        std::string nroDocumento(listaDeClientes[i].getNroDocumento());

        if (razonSocial == "null") {
            datosConcatenados += nombre;
            datosConcatenados += " ";
            datosConcatenados += apellido;
            datosConcatenados += nroDocumento;
        }
        else {
            datosConcatenados += razonSocial;
            datosConcatenados += " ";
            datosConcatenados += nroDocumento;
        }

        if (strstr(datosConcatenados.c_str(), cadenaDeBusquedaLibre.c_str()) != nullptr) {
            resultadosEncontrados++;
        }
    }

    if (resultadosEncontrados > 0) {
        std::cout << std::endl;
        std::cout << "Registros encontrados: " << resultadosEncontrados << std::endl;
        std::cout << std::endl;
        std::cout << std::left;
        std::cout << std::setw(6) << "Id";
        std::cout << std::setw(7) << "Tipo";
        std::cout << std::setw(15) << "Nro";
        std::cout << std::setw(38) << "Cliente";
        std::cout << std::setw(13) << "F. Registro";
        std::cout << std::endl;
        std::cout << "-----------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < cantidadDeRegistros; i++) {
            std::string datosConcatenados = "";

            std::string nombre(listaDeClientes[i].getNombre());
            std::string apellido(listaDeClientes[i].getApellido());
            std::string razonSocial(listaDeClientes[i].getRazonSocial());
            std::string nroDocumento(listaDeClientes[i].getNroDocumento());

            if (razonSocial == "null") {
                datosConcatenados += nombre;
                datosConcatenados += " ";
                datosConcatenados += apellido;
                datosConcatenados += nroDocumento;
            }
            else {
                datosConcatenados += razonSocial;
                datosConcatenados += " ";
                datosConcatenados += nroDocumento;
            }

            if (strstr(datosConcatenados.c_str(), cadenaDeBusquedaLibre.c_str()) != nullptr) {
                listar(listaDeClientes[i], 1);
                std::cout << std::endl;
            }
        }
        mensajeFinDelListado();
    }
    else {
        mensajeListadoSinDatosEncontrados();
    }

    delete[] listaDeClientes;
    rlutil::anykey();
}

void ClienteManager::ordenarPorNombre(Cliente *listaDeClientes, int cantidadDeRegistros) {
    Cliente clienteAux;
    int menor = 0;

    for (int i = 0; i < cantidadDeRegistros - 1; i++) {
        menor = i;

        // Procesamiento de nombres de posicion i para concatenarlos y unificarlos
        std::string nombreCliente = "";
        std::string razonSocial(listaDeClientes[i].getRazonSocial());
        std::string apellido(listaDeClientes[i].getApellido());
        std::string nombre(listaDeClientes[i].getNombre());

        if (razonSocial == "null") {
            // Concateno en nombreCliente el Apellido y el nombre
            nombreCliente += apellido;
            nombreCliente += " ";
            nombreCliente += nombre;
        }
        else {
            nombreCliente += razonSocial;
        }

        for (int j = i + 1; j < cantidadDeRegistros; j++) {
            // Procesamiento de nombres de posicion j para concatenarlos y unificarlos
            std::string nombreClienteActual = "";
            std::string razonSocialActual(listaDeClientes[j].getRazonSocial());
            std::string apellidoActual(listaDeClientes[j].getApellido());
            std::string nombreActual(listaDeClientes[j].getNombre());

            if (razonSocialActual == "null") {
                // Concateno en nombreClienteActual el Apellido y el nombre
                nombreClienteActual += apellidoActual;
                nombreClienteActual += " ";
                nombreClienteActual += nombreActual;
            }
            else {
                nombreClienteActual += razonSocialActual;
            }

            // Ahora comparamos
            if (nombreClienteActual < nombreCliente) {
                menor = j;
                nombreCliente = nombreClienteActual;  // Actualizamos el nombreCliente
            }
        }

        if (i != menor) {
            clienteAux = listaDeClientes[i];
            listaDeClientes[i] = listaDeClientes[menor];
            listaDeClientes[menor] = clienteAux;
        }
    }
}

// Métodos públicos
void ClienteManager::cargar() {
    rlutil::cls();
    int id;
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
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;

    id = generarId();

    std::cout << "Tipo de Cliente (1. Persona física | 2. Persona jurídica): ";
    tipoDeCliente = ingresoDeTipoDeClienteConValidacion();

    std::cout << "Tipo de documento (1. DNI | 2. CUIT): ";
    tipoDocumento = ingresoTipoDeDocumentoConValidacion();
    std::cout << "Nro de documento: ";
    nroDocumento = ingresoDeDocumentoConValidacion();

    Cliente clienteBuscado;
    int posicionBusqueda = _archivo.buscar(nroDocumento);

    if (posicionBusqueda == -1)
    {
        switch(tipoDeCliente)
        {
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

        Cliente cliente(id, tipoDocumento, nroDocumento.c_str(), nombre.c_str(), apellido.c_str(), razonSocial.c_str(), email.c_str(), domicilio.c_str(), localidad.c_str(), provincia, estado, fechaRegistro);

        if (_archivo.crear(cliente) == true)
        {
            okMensajeCreacion();
            rlutil::anykey();
        }
        else
        {
            errorMensajeCreacion();
            rlutil::anykey();
        }
    }
    else
    {
        existeRegistroMensaje();
        rlutil::anykey();
    }
}

bool ClienteManager::cargar(std::string nroDocumento) {
    rlutil::cls();
    int id;
    int tipoDeCliente;
    int tipoDocumento;
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

    id = generarId();

    std::cout << "Tipo de Cliente (1. Persona física | 2. Persona jurídica): ";
    tipoDeCliente = ingresoDeTipoDeClienteConValidacion();

    std::cout << "Tipo de documento (1. DNI | 2. CUIT): ";
    tipoDocumento = ingresoTipoDeDocumentoConValidacion();

    switch(tipoDeCliente)
    {
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

    Cliente cliente(id, tipoDocumento, nroDocumento.c_str(), nombre.c_str(), apellido.c_str(), razonSocial.c_str(), email.c_str(), domicilio.c_str(), localidad.c_str(), provincia, estado, fechaRegistro);
        if (_archivo.crear(cliente) == true)
        {
            okMensajeCreacion();
            return true;
        }
        else
        {
            errorMensajeCreacion();
            return false;
        }
}

void ClienteManager::listar(Cliente cliente, int tipoListado) {
    // Tipos de listado
    // --------------------
    // 0. Listado detallado
    // 1. Listado resumido (para tabla)

    switch (tipoListado)
    {
    case 0:
        std::cout << "Id: " << cliente.getId() << std::endl;
        std::cout << "Tipo de documento: " << cliente.getTipoDocumentoDescripcion() << std::endl;
        std::cout << "Nro de documento: " << cliente.getNroDocumento() << std::endl;
        // Si getRazonSocial es "Null" significa que es una persona física
        if (strcmp(cliente.getRazonSocial(),"null") == 0)
        {
            std::cout << "Apellido: " << cliente.getApellido() << std::endl;
            std::cout << "Nombre: " << cliente.getNombre() << std::endl;
        }
        else
        {
            std::cout << "Razón Social: " << cliente.getRazonSocial() << std::endl;
        }
        std::cout << "Email: " << cliente.getEmail() << std::endl;
        std::cout << "Domicilio: " << cliente.getDomicilio() << std::endl;
        std::cout << "Fecha de registro: " << cliente.getFechaRegistro().toString() << std::endl;
        std::cout << "Estado: " << cliente.getEstadoDescripcion() << std::endl;
        break;
    case 1:
        std::cout << std::left;
        std::cout << std::setw(6) << cliente.getId();
        std::cout << std::setw(7) << cliente.getTipoDocumentoDescripcion();
        std::cout << std::setw(15) << cliente.getNroDocumento();
        std::string null = "null";
        if (strcmp(cliente.getRazonSocial(), null.c_str()) == 0)
        {
            // std::cout << std::setw(18) << cliente.getNombre();
            // std::cout << std::setw(18) << cliente.getApellido();
            // Concatenamos apellido y nombre. Usamos constructores de String para convertir Char en String.
            std::string apellidoNombre = std::string(cliente.getApellido()) + " " + std::string(cliente.getNombre());
            std::cout << std::setw(38) << apellidoNombre;
        }
        else
        {
            std::cout << std::setw(38) << cliente.getRazonSocial();
        }
        std::cout << std::setw(13) << cliente.getFechaRegistro().toString();
        break;
    }
}

void ClienteManager::listarClientes() {
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "ELIJA EL TIPO DE LISTADO" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. CLIENTE POR NRO DE DOCUMENTO" << std::endl;
        std::cout << "2. CLIENTES ACTIVOS" << std::endl;
        std::cout << "3. CLIENTES INACTIVOS" << std::endl;
        std::cout << "4. BÚSQUEDA LIBRE" << std::endl;
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
            listarPorNroDeDocumento();
            break;
        case 2:
            listarActivos();
            break;
        case 3:
            listarInactivos();
            break;
        case 4:
            listarPorBusquedaLibre();
            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
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

    int posicion = _archivo.buscar(nroDocumento);
    if (posicion > -1)
    {
        cliente = _archivo.leer(posicion);
        std::cout << std::endl;
        std::cout << "Datos del cliente: " << std::endl;
        listar(cliente, 0);
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "¿Desea modificar datos de este cliente? (SI | NO): ";
        std::string decision = ingresoDeDecisionConValidacion();

        if (decision == "SI")
        {
            int opcion = -1;
            std::string decision;

            do
            {
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

                switch(opcion)
                {
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

                    if (_archivo.modificar(cliente, posicion))
                    {
                        okMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    else
                    {
                        errorMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    break;
                case 2:
                    std::cout << std::endl;
                    char null[5];
                    strcpy(null, "null"); // Cargo un vector de char como null para poder comparar
                    if (strcmp(cliente.getRazonSocial(), null) != 0)   // Si tiene razón social significa que es una persona jurídica
                    {
                        std::cout << "El cliente está registrado como una persona jurídica" << std::endl;
                        std::cout << "¿Desea modificar el registro como persona física? (SI | NO): ";
                        decision = ingresoDeDecisionConValidacion();
                        std::cout << std::endl;

                        if (decision == "SI")
                        {
                            std::cout << "Ingrese el nuevo nombre: ";
                            nombre = ingresoDeNombreApellidoConValidacion();
                            std::cout << "Ingrese el nuevo apellido: ";
                            apellido = ingresoDeNombreApellidoConValidacion();
                            std::cout << std::endl;
                            razonSocial = "null";

                            cliente.setNombre(nombre.c_str());
                            cliente.setApellido(apellido.c_str());
                            cliente.setRazonSocial(razonSocial.c_str());

                            if (_archivo.modificar(cliente, posicion))
                            {
                                okMensajeModificacion();
                                rlutil::anykey();
                                opcion = 0;
                            }
                            else
                            {
                                errorMensajeModificacion();
                                rlutil::anykey();
                                opcion = 0;
                            }
                        }
                        else
                        {
                            std::cout << "Ingrese la nueva razón social: ";
                            razonSocial = ingresoDeRazonSocialConValidacion();
                            std::cout << std::endl;

                            cliente.setRazonSocial(razonSocial.c_str());

                            if (_archivo.modificar(cliente, posicion))
                            {
                                okMensajeModificacion();
                                rlutil::anykey();
                                opcion = 0;
                            }
                            else
                            {
                                errorMensajeModificacion();
                                rlutil::anykey();
                                opcion = 0;
                            }
                        }
                    }
                    else
                    {
                        std::cout << "El cliente está registrado como una persona física" << std::endl;
                        std::cout << "¿Desea modificar el registro como persona jurídica? (SI | NO): ";
                        decision = ingresoDeDecisionConValidacion();
                        std::cout << std::endl;

                        if (decision == "SI")
                        {
                            std::cout << "Ingrese la nueva razón social: ";
                            razonSocial = ingresoDeRazonSocialConValidacion();
                            std::cout << std::endl;
                            nombre = "null";
                            apellido = "null";

                            cliente.setRazonSocial(razonSocial.c_str());
                            cliente.setNombre(nombre.c_str());
                            cliente.setApellido(apellido.c_str());

                            if (_archivo.modificar(cliente, posicion))
                            {
                                okMensajeModificacion();
                                rlutil::anykey();
                                opcion = 0;
                            }
                            else
                            {
                                errorMensajeModificacion();
                                rlutil::anykey();
                                opcion = 0;
                            }
                        }
                        else
                        {
                            std::cout << "Ingrese el nuevo nombre: ";
                            nombre = ingresoDeNombreApellidoConValidacion();
                            std::cout << "Ingrese el nuevo apellido: ";
                            apellido = ingresoDeNombreApellidoConValidacion();
                            std::cout << std::endl;
                            razonSocial = "null";

                            cliente.setNombre(nombre.c_str());
                            cliente.setApellido(apellido.c_str());
                            cliente.setRazonSocial(razonSocial.c_str());

                            if (_archivo.modificar(cliente, posicion))
                            {
                                okMensajeModificacion();
                                rlutil::anykey();
                                opcion = 0;
                            }
                            else
                            {
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
                    std::cout << "Ingrese el nuevo domicilio: ";
                    domicilio = ingresoDeDomicilioConValidacion();
                    std::cout << "Ingrese localidad: ";
                    localidad = ingresoDeLocalidadConValidacion();
                    std::cout << "Seleccionar provincia: " << std::endl;
                    std::cout << std::endl;
                    listarProvincias();
                    std::cout << std::endl;
                    std::cout << "Nro de provincia: ";
                    provincia = ingresoDeProvinciaConValidacion();
                    std::cout << std::endl;

                    cliente.setDomicilio(domicilio);
                    cliente.setLocalidad(localidad);
                    cliente.setProvincia(provincia);

                    if (_archivo.modificar(cliente, posicion))
                    {
                        okMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    else
                    {
                        errorMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    std::cout << std::endl;
                    break;
                case 4:
                    std::cout << std::endl;
                    std::cout << "Ingrese el nuevo email: ";
                    email = ingresoDeEmailConValidacion();
                    std::cout << std::endl;

                    cliente.setEmail(email.c_str());

                    if (_archivo.modificar(cliente, posicion))
                    {
                        okMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
                    else
                    {
                        errorMensajeModificacion();
                        rlutil::anykey();
                        opcion = 0;
                    }
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
    else
    {
        registroNoEncontradoMensaje();
        rlutil::anykey();
    }
}

void ClienteManager::darDeBaja() {
    rlutil::cls();
    Cliente cliente;
    std::string nroDocumento;

    std::cout << "BAJA DE CLIENTE" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Ingrese nro de documento del cliente a dar de baja (Si es CUIT ingrese el número que se ubica entre iones): ";
    nroDocumento = ingresoDeDocumentoConValidacion();

    int posicion = _archivo.buscar(nroDocumento);
    if (posicion > -1)
    {
        cliente = _archivo.leer(posicion);
        if (cliente.getEstado())
        {
            std::cout << std::endl;
            std::cout << "Datos del cliente: " << std::endl;
            listar(cliente, 0);
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "¿Desea dar de baja a este cliente? (SI | NO): ";
            std::string decision = ingresoDeDecisionConValidacion();

            if (decision == "SI")
            {
                cliente.setEstado(false);
                _archivo.modificar(cliente, posicion);
                okMensajeBaja();
            }
            else {
                errorMensajeBaja();
            }
        }
        else
        {
            registroNoEncontradoMensaje();
        }
    }
    else
    {
        registroNoEncontradoMensaje();
    }
    rlutil::anykey();
}

void ClienteManager::reactivar() {
    rlutil::cls();
    Cliente cliente;
    std::string nroDocumento;

    std::cout << "REACTIVACIÓN DE CLIENTE" << std::endl;
    std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Ingrese nro de documento del cliente a reactivar (Si es CUIT ingrese el número que se ubica entre iones): ";
    nroDocumento = ingresoDeDocumentoConValidacion();

    int posicion = _archivo.buscar(nroDocumento);
    if (posicion > -1)
    {
        cliente = _archivo.leer(posicion);
        if (!cliente.getEstado())
        {
            std::cout << std::endl;
            std::cout << "Datos del cliente: " << std::endl;
            listar(cliente, 0);
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "¿Desea reactivar este cliente? (SI | NO): ";
            std::string decision = ingresoDeDecisionConValidacion();

            if (decision == "SI")
            {
                cliente.setEstado(true);
                _archivo.modificar(cliente, posicion);
                okMensajeModificacion();
            }
            else {
                errorMensajeModificacion();
            }
        }
        else
        {
            registroNoEncontradoMensaje();
        }
    }
    else
    {
        registroNoEncontradoMensaje();
    }
    rlutil::anykey();
}

bool ClienteManager::reactivar(std::string nroDocumento) {
    Cliente cliente;

    int posicion = _archivo.buscar(nroDocumento);
    if (posicion > -1)
    {
        cliente = _archivo.leer(posicion);
        listar(cliente, 0);
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "¿Desea reactivar este cliente? (SI | NO): ";
        std::string decision = ingresoDeDecisionConValidacion();

        if (decision == "SI")
        {
            cliente.setEstado(true);
            if(_archivo.modificar(cliente, posicion))
            {
                okMensajeReactivacion();
                return true;
            }
            else
            {
                errorMensajeReactivacion();
                return false;
            }
        }
        else
        {
            return false;
        }

    }
}

void ClienteManager::hacerCopiaDeSeguridad() {
    int cantidadDeClientes = _archivo.getCantidadDeClientes();
    if(cantidadDeClientes <= 0)
    {
        errorMensajeCopiaDeSeguridadSinRegs();
        rlutil::anykey();
        return;
    }

    Cliente* listaDeClientes = new Cliente[cantidadDeClientes];

    if (listaDeClientes == nullptr)
    {
        errorMensajeCopiaDeSeguridad();
        return;
    }

    _archivo.leer(listaDeClientes, cantidadDeClientes);
    _archivoBkp.vaciar();

    if(_archivoBkp.crear(listaDeClientes, cantidadDeClientes))
    {
        okMensajeCopiaDeSeguridad();
    }
    else
    {
        errorMensajeCopiaDeSeguridad();
    }

    delete[] listaDeClientes;
    rlutil::anykey();
}

void ClienteManager::restaurarCopiaDeSeguridad() {
    int cantidadDeClientes = _archivoBkp.getCantidadDeClientes();
    if(cantidadDeClientes <= 0)
    {
        errorMensajeCopiaDeSeguridadSinRegs();
        rlutil::anykey();
        return;
    }

    Cliente *listaDeClientes = new Cliente[cantidadDeClientes];

    if (listaDeClientes == nullptr)
    {
        errorMensajeRestauracionCopiaDeSeguridad();
        return;
    }

    _archivoBkp.leer(listaDeClientes, cantidadDeClientes);
    _archivo.vaciar();

    if(_archivo.crear(listaDeClientes, cantidadDeClientes))
    {
        okMensajeRestauracionCopiaDeSeguridad();
    }
    else
    {
        errorMensajeRestauracionCopiaDeSeguridad();
    }

    delete[] listaDeClientes;
    rlutil::anykey();
}
