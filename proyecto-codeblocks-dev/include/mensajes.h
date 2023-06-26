#ifndef MENSAJES_H_INCLUDED
#define MENSAJES_H_INCLUDED

void okMensajeModificacion();
void errorMensajeModificacion();

void okMensajeCreacion();
void errorMensajeCreacion();

void okMensajeBaja();
void errorMensajeBaja();

void okMensajeReactivacion();
void errorMensajeReactivacion();

void okMensajeCopiaDeSeguridad();
void errorMensajeCopiaDeSeguridad();
void errorMensajeCopiaDeSeguridadSinRegs();

void okMensajeRestauracionCopiaDeSeguridad();
void errorMensajeRestauracionCopiaDeSeguridad();

void mensajeNoSePudoCrearArchivo();
void mensajeNoSePudoLeerArchivo();

void registroNoEncontradoMensaje();
void mensajeListadoSinDatosEncontrados();

void registroYaEliminado();
void registroNoEliminado();

void existeRegistroMensaje();

void mensajeSalidaDelPrograma();
void mensajeAccesoRestringido();
void mensajeFinDelListado();

#endif // MENSAJES_H_INCLUDED
