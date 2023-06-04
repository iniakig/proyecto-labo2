#ifndef MARCA_H_INCLUDED
#define MARCA_H_INCLUDED


class Marca{
private:
int _ID;
char _nombre[30];

public:
//Constructor
Marca(int ID = 0, const char* nombre = "null");
//Setters
void setID(int ID);
void setNombre(const char* nombre);
//Getters
int getID();
const char* getNombre();

};




#endif // MARCA_H_INCLUDED
