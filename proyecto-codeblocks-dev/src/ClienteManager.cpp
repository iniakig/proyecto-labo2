#include "ClienteManager.h"
#include "Cliente.h"

#include "../funciones.h"

void ClienteManager::cargar() {
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

    std::cout << "Tipo de Cliente (1. Persona física | 2. Persona jurídica): ";
    tipoDeCliente = ingresoDeTipoDeClienteConValidacion();

    std::cout << "Tipo de documento (1. DNI | 2. CUIT): ";
    tipoDocumento = ingresoTipoDeDocumentoConValidacion();
    std::cout << "Nro de documento: ";
    nroDocumento = ingresoDeDocumentoConValidacion();

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
    listarProvincias();
    std::cout << "Nro de provincia: ";
    provincia = ingresoDeProvinciaConValidacion();

    Cliente cliente(tipoDocumento, nroDocumento.c_str(), nombre.c_str(), apellido.c_str() , razonSocial.c_str(), email.c_str(), domicilio.c_str(), localidad.c_str(), provincia, estado, fechaRegistro);

    if (_archivo.crear(cliente)) {
        std::cout << "El cliente se cargó correctamente.";
    }
    else {
        std::cout << "No se pudo crear el cliente.";
    }
}

void listar(Cliente cliente) {

}

void ClienteManager::modificar() {
    Cliente cliente;

    int tipoDeCliente;
    int tipoDeDocumento;
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

    std::cout << "Ingrese nro de documento del cliente a modificar (Si es CUIT ingrese el número que se ubica entre iones): ";
    nroDocumento = ingresoDeDocumentoConValidacion();

    int posicion = _archivo.buscar(nroDocumento);
    if (posicion > -1) {
        cliente = _archivo.leer(posicion);
        std::cout << "Datos del cliente: "
        listar(cliente);
        std::cout << std::endl;
        std::cout << "¿Desea modificar datos de este cliente? (SI | NO): ";
        std::string decision = ingresoDeDecisionConValidacion();

        if (decision == "SI") {
            do {
                std::cout << std::endl;
                std::cout << "ELIJA EL CAMPO QUE DESEA MODIFICAR" << std::endl;
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "1. TIPO DE DOCUMENTO" << std::endl;
                std::cout << "2. NRO DE DOCUMENTO" << std::endl;
                std::cout << "3. NOMBRE" << std::endl;
                std::cout << "4. APELLIDO" << std::endl;
                std::cout << "5. ROL" << std::endl;
                std::cout << "6. CONTRASEÑA" << std::endl;
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
                    cliente.setTipoDocumento(tipoDeDocumento);
                    if (_archivo.modificar(cliente, posicion)) {
                        std::cout << std::endl;
                        okMensajeModificacion();
                    }
                    else {
                        std::cout << std::endl;
                        errorMensajeModificacion();
                    }
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
    }
}



