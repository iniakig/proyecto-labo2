#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

void setSpanish();
void setTamanioConsola(int columnas, int filas);

int enteroConvertidoAInt(std::string stringParaConvertir);
std::string stringAMayus(std::string cadena);
std::string ingresoDeDocumentoConValidacion();
std::string ingresoDeAliasConValidacion();
std::string ingresoDeContraseniaConValidacion();
std::string ingresoDeNombreApellidoConValidacion();
std::string ingresoDeEmailConValidacion();
std::string ingresoDeMarcaConValidacion();
int ingresoDeTipoDeClienteConValidacion();
int ingresoTipoDeDocumentoConValidacion();
int ingresoOpcSimpleConValidacion();
std::string ingresoDeRazonSocialConValidacion();
std::string ingresoDeLocalidadConValidacion();
std::string ingresoDeDomicilioConValidacion();
int ingresoDeProvinciaConValidacion();
std::string ingresoDeDecisionConValidacion();
void listarProvincias();
std::string cortarCuit(std::string stringParaCortar);

// Mensajes
void okMensajeModificacion();
void errorMensajeModificacion();
void okMensajeCreacion();
void errorMensajeCreacion();
void registroNoEncontradoMensaje();
void existeRegistroMensaje();


#endif // FUNCIONES_H_INCLUDED
