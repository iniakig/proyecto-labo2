#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <string>

void setSpanish();
std::string cortarCuit(std::string stringParaCortar);
void centrarTexto(std::string texto, int posy);
int enteroConvertidoAInt(std::string stringParaConvertir);
float stringConvertidoAFloat(std::string stringParaConvertir);
std::string stringAMayus(std::string cadena);
void ponerCero(int *vec, int tam);
bool validarRol(const bool *permisos, const int rol);
void listarProvincias();
#endif // FUNCIONES_H_INCLUDED
