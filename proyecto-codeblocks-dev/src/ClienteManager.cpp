#include "ClienteManager.h"

// TODO NAHUEL

void ClienteManager::cargar() {
    int tipoDocumento;
    std::string nroDocumento;
    std::string nombre;
    std::string apellido;
    std::string razonSocial; // Agregar en clase persona
    std::string email;
    bool estado;
    Fecha fechaRegistro;
    std::string alias;
    std::string contrasenia;
    int rol;

    std::cout << "Tipo de documento (1. DNI | 2. CUIT): ";
    tipoDocumento = ingresoTipoDeDocumentoConValidacion();
    std::cout << "Nro de documento: ";
    nroDocumento = ingresoDeDocumentoConValidacion(); // Sirve para DNI y CUIT

    switch(tipoDeCliente) { // Hacer algo para que sea persona física o jurídica
    case 1:
        std::cout << "Nombre: ";
        nombre = ingresoDeTextoConValidacion();
        std::cout << "Apellido: ";
        apellido = ingresoDeTextoConValidacion();
        break;
    case 2:
        std::cout << "Razón social: ";
        razonSocial = ingresoDeRazonSocialConValidacion();
        break;
    }

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

    _archivo.crear(usuario);
}
