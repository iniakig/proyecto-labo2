#include "Marca.h"

//Constructor
Marca::Marca(int ID, const char* nombre, bool activo){
setID(ID);
setNombre(nombre);
setActivo(activo);
}

//Setters
void Marca::setID(int ID){
_ID=ID;
}

void Marca::setNombre(const char *nombre){
strcpy(_nombre, nombre);
}

void Marca::setActivo(bool activo){
    _activo = activo;
}

//Getters
int Marca::getID(){
return _ID;
}
const char* Marca::getNombre(){
return _nombre;
}

bool Marca::getActivo(){
    return _activo;
}
