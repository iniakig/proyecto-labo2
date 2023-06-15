#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

void setSpanish();
void setTamanioConsola(int columnas, int filas);
void listarProvincias();
std::string cortarCuit(std::string stringParaCortar);
void centrarTexto(std::string texto, int posy);
int enteroConvertidoAInt(std::string stringParaConvertir);
std::string stringAMayus(std::string cadena);


// Validación de entradas
std::string ingresoDeDocumentoConValidacion();
std::string ingresoDeAliasConValidacion();
std::string ingresoDeContraseniaConValidacion();
std::string ingresoDeNombreApellidoConValidacion();
std::string ingresoDeEmailConValidacion();
int ingresoDeRolConValidacion();
std::string ingresoDeMarcaConValidacion();
int ingresoDeTipoDeClienteConValidacion();
int ingresoTipoDeDocumentoConValidacion();
int ingresoOpcSimpleConValidacion();
std::string ingresoDeRazonSocialConValidacion();
std::string ingresoDeLocalidadConValidacion();
std::string ingresoDeDomicilioConValidacion();
int ingresoDeProvinciaConValidacion();
std::string ingresoDeDecisionConValidacion();


// Mensajes
void okMensajeModificacion();
void errorMensajeModificacion();
void okMensajeCreacion();
void errorMensajeCreacion();
void okMensajeBaja();
void errorMensajeBaja();
void okMensajeReactivacion();
void errorMensajeReactivacion();
void registroNoEncontradoMensaje();
void existeRegistroMensaje();
void mensajeSalidaDelPrograma();
void mensajeAccesoRestringido();
void mensajeListadoSinDatosEncontrados();


#endif // FUNCIONES_H_INCLUDED
