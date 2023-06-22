#include "mensajes.h"

#include <iostream>
#include "rlutil.h"
#include "funciones.h"

void okMensajeCreacion() {
    rlutil::setColor(rlutil::LIGHTGREEN);
    std::cout << "El registro se creó correctamente." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void errorMensajeCreacion() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "El registro no se pudo crear." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void okMensajeModificacion() {
    rlutil::setColor(rlutil::LIGHTGREEN);
    std::cout << "El registro se modificó correctamente." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void errorMensajeModificacion() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "El registro no se pudo modificar." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void okMensajeBaja() {
    rlutil::setColor(rlutil::LIGHTGREEN);
    std::cout << "El registro se dio de baja correctamente." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void errorMensajeBaja() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "El registro no se pudo dar de baja." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void okMensajeReactivacion() {
    rlutil::setColor(rlutil::LIGHTGREEN);
    std::cout << "El registro se reactivó correctamente." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void errorMensajeReactivacion() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "El registro no se pudo reactivar." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void registroNoEncontradoMensaje() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "No se encontró el registro buscado para realizar la acción solicitada" << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void registroYaEliminado() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "El registro ingresado ya se encuentra eliminado." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void registroNoEliminado(){
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "El registro no se encuentra eliminado." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void existeRegistroMensaje() {
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "Ya existe un registro creado con ese nro de identificación." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void mensajeSalidaDelPrograma() {
    rlutil::setColor(rlutil::LIGHTRED);
    centrarTexto("Muchas gracias por usar la aplicación.", 15);
    rlutil::setColor(rlutil::WHITE);
}

void mensajeAccesoRestringido() {
    std::cout << std::endl;
    rlutil::setColor(rlutil::LIGHTRED);
    std::cout << "Este menú se encuentra restringido para tu perfil de usuario." << std::endl;
    rlutil::setColor(rlutil::YELLOW);
    std::cout << "Cualquier duda consultá con el administrador de la aplicación." << std::endl;
    rlutil::setColor(rlutil::WHITE);
}

void mensajeListadoSinDatosEncontrados() {
    std::cout << std::endl;
    rlutil::setColor(rlutil::YELLOW);
    std::cout << "No se encontraron registros relacionados a este listado" << std::endl;
    rlutil::setColor(rlutil::WHITE);
}
