#ifndef FECHA_H
#define FECHA_H

#include <iostream>
#include <string>
#include <windows.h>

class Fecha {
private:
	int _dia;
	int _mes;
	int _anio;

	void AgregarDia();
	void RestarDia();

	// Reemplazar las comprobaciones de bisiesto con esta interfaz
	bool esBisiesto(int anio) {
	    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
			return true;
		}
    return false;}

public:
	// Constructores
	Fecha(int dia = 1, int mes = 1, int anio = 2023);

	// Interfaces
	void Mostrar();
	void AgregarDias(int dias);
	//std::string toString();
	std::string toString(std::string formatoFecha = "DD/MM/YYYY");
	Fecha fechaActual();

	// Setters
	void setDia(int dia);
	void setMes(int mes);
	void setAnio(int anio);

	// Getters
	int getDia();
	int getMes();
	int getAnio();
};

#endif // FECHA_H
