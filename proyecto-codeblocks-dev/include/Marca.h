#ifndef MARCA_H_INCLUDED
#define MARCA_H_INCLUDED

#include <cstring>

class Marca{
private:
int _ID;
char _nombre[30];
bool _activo;

public:
//Constructor
Marca(int ID = 0, const char* nombre = "null", bool activo = false);
//Setters
void setID(int ID);
void setNombre(const char* nombre);
void setActivo (bool activo);

//Getters
int getID();
const char* getNombre();
bool getActivo();

};




#endif // MARCA_H_INCLUDED
