#include "Marca.h"

//Constructor
Marca::Marca(int ID, const char* nombre){
setID(ID);
setNombre(nombre);
}

//Setters
void Marca::setID(int ID){
_ID=ID;
}

void Marca::setNombre(const char *nombre){
strcpy(_nombre, nombre);
}

//Getters
int Marca::getID(){
return _ID;
}
const char* Marca::getNombre(){
return _nombre;
}
