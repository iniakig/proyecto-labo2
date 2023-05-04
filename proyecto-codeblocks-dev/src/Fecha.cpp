#include "Fecha.h"

Fecha::Fecha(int dia, int mes, int anio)
{
    const int meses = 12;
    int limiteDiasDeMeses[meses] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0) {
        limiteDiasDeMeses[1] = 29;
    }

    if (dia > 0 && dia <= limiteDiasDeMeses[mes - 1]) {
        if (mes > 0 && mes <= meses) {
            if (anio > 0) {
                _dia = dia;
                _mes = mes;
                _anio = anio;
            }
        }
    }
    else {
        _dia = 1;
        _mes = 1;
        _anio = 2023;
    }
}

void Fecha::Mostrar()
{
    std::cout << _dia << "/" << _mes << "/" << _anio;
}

void Fecha::AgregarDia()
{
    const int meses = 12;
    int limiteDiasDeMeses[meses] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((_anio % 4 == 0 && _anio % 100 != 0) || _anio % 400 == 0) {
        limiteDiasDeMeses[1] = 29;
    }

    if (_dia == limiteDiasDeMeses[_mes - 1]) {
        _dia = 1;
        _mes++;
        if (_mes > meses) {
            _mes = 1;
            _anio++;
        }
    }
    else {
        _dia++;
    }
}

void Fecha::RestarDia()
{
    const int meses = 12;
    int limiteDiasDeMeses[meses] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ((_anio % 4 == 0 && _anio % 100 != 0) || _anio % 400 == 0) {
        limiteDiasDeMeses[1] = 29;
    }

    if(_dia == 1) {
        if (_mes == 1) {
            _mes = 12;
            _dia = limiteDiasDeMeses[_mes - 1]--;
            _anio--;
        }
        else {
            _mes--;
            _dia = limiteDiasDeMeses[_mes - 1];
        }
    }
    else {
        _dia--;
    }
}

void Fecha::AgregarDias(int dias) {
    if (dias > 0) {
        for (int i = 0; i < dias; i++) {
            AgregarDia();
        }
    }
    else if (dias < 0) {
        for (int i = 0; i > dias; i--) {
            RestarDia();
        }
    }
}

std::string Fecha::toString(std::string formatoFecha)
{
    std::string fechaString = "null";

    if (formatoFecha == "DD/MM/YYYY") {
        if (_dia < 10 && _mes < 10) {
            fechaString = "0" + std::to_string(_dia) + "/" + "0" + std::to_string(_mes) + "/" + std::to_string(_anio);
        }
        else if (_dia < 10 && _mes > 9) {
            fechaString = "0" + std::to_string(_dia) + "/" + std::to_string(_mes) + "/" + std::to_string(_anio);
        }
        else if (_dia > 9 && _mes < 10) {
            fechaString = std::to_string(_dia) + "/" + "0" + std::to_string(_mes) + "/" + std::to_string(_anio);
        }
        else {
            fechaString = std::to_string(_dia) + "/" + std::to_string(_mes) + "/" + std::to_string(_anio);
        }
    }
    else if (formatoFecha == "YYYY/MM/DD") {
        if (_dia < 10 && _mes < 10) {
            fechaString = std::to_string(_anio) + "/" + "0" + std::to_string(_mes) + "/" + "0" + std::to_string(_dia);
        }
        else if (_dia < 10 && _mes > 9) {
            fechaString = std::to_string(_anio) + "/" + std::to_string(_mes) + "/" + "0" + std::to_string(_dia);
        }
        else if (_dia > 9 && _mes < 10) {
            fechaString = std::to_string(_anio) + "/" + "0" + std::to_string(_mes) + "/" + std::to_string(_dia);
        }
        else {
            fechaString = std::to_string(_anio) + "/" + std::to_string(_mes) + "/" + std::to_string(_dia);
        }
    }


    return fechaString;
}

Fecha Fecha::fechaActual() {
    SYSTEMTIME st;
    GetSystemTime(&st);

    return Fecha(st.wDay, st.wMonth, st.wYear);
}

void Fecha::setDia(int dia) {
    _dia = dia;
}

void Fecha::setMes(int mes) {
    _mes = mes;
}

void Fecha::setAnio(int anio) {
    _anio = anio;
}

int Fecha::getDia()
{
    return _dia;
}

int Fecha::getMes()
{
    return _mes;
}

int Fecha::getAnio()
{
    return _anio;
}
