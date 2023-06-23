#include "EmpresaManager.h"

#include "../funciones.h"
#include "../validaciones.h"
#include "../mensajes.h"
#include "../rlutil.h"

void EmpresaManager::cargar() {
    rlutil::cls();
    int tipoDocumento;
    std::string nroDocumento;
    std::string razonSocial;
    std::string email;
    bool estado;
    std::string domicilio;
    std::string localidad;
    int provincia;
    Fecha fechaRegistro;

    std::cout << "CARGAR PERFIL EMPRESA" << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;


    std::cout << "Nro de CUIT: ";
    nroDocumento = ingresoDeDocumentoConValidacion();

    std::cout << "Razón social: ";
    razonSocial = ingresoDeRazonSocialConValidacion();

    std::cout << "Email: ";
    email = ingresoDeEmailConValidacion();
    estado = true;
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

    fechaRegistro = Fecha().fechaActual();

    Empresa empresa(2, nroDocumento.c_str(), "null", "null", razonSocial.c_str(), email.c_str(), domicilio.c_str(), localidad.c_str(), provincia, estado, fechaRegistro);

    if(_archivo.crear(empresa)) {
        okMensajeCreacion();
    }
    else {
        errorMensajeCreacion();
    }
    rlutil::anykey();
}

void EmpresaManager::listar() {
    Empresa empresa;
    empresa = _archivo.leer();
    std::string nroDocumento = "null";
    if (strcmp(empresa.getNroDocumento(), nroDocumento.c_str()) != 0) {
        rlutil::cls();

        std::cout << "DATOS DE LA EMPRESA" << std::endl;
        std::cout << "-------------------------------------------------------------" << std::endl;
        std::cout << "Nro de CUIT: " << empresa.getNroDocumento() << std::endl;
        std::cout << "Razón Social: " << empresa.getRazonSocial() << std::endl;
        std::cout << "Email: " << empresa.getEmail() << std::endl;
        std::cout << "Domicilio: " << empresa.getDomicilio() << std::endl;
        std::cout << "Localidad: " << empresa.getLocalidad() << std::endl;
        std::cout << "Provincia: " << empresa.getProvinciaDescripcion() << std::endl;
        std::cout << "Fecha de registro: " << empresa.getFechaRegistro().toString() << std::endl;
    }
    else {
        mensajeListadoSinDatosEncontrados();
    }
    rlutil::anykey();
}
