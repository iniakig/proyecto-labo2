#include <iostream>
#include <string.h>
#include <windows.h>

using namespace std;

/*
    - Validar que solo pueda ingresar tipos de documento existentes
    - Validar que el DNI no se repita
*/

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

class Persona {
private:
    int _tipoDocumento; // Puede ser: ( 1. DNI | 2. CUIL | 3. CUIT )
    char _nroDocumento[12];
    char _nombre[30];
    char _apellido[30];
    char _email[320];
    bool _estado;
    Fecha _fechaRegistro;

public:
    // Constructores
    Persona(int tipoDocumento = 0, const char* nroDocumento = "null", const char* nombre = "null", const char* apellido = "null", const char* email = "null", bool estado = "false", Fecha fechaRegistro = Fecha());

    // Interfaces
    void Mostrar();

    // Setters
    void setTipoDocumento(int tipoDocumento) {_tipoDocumento = tipoDocumento;}
    void setNroDocumento(const char* nroDocumento) {strcpy(_nroDocumento, nroDocumento);}
    void setNombre(const char* nombre) {strcpy(_nombre, nombre);}
    void setApellido(const char* apellido) {strcpy(_apellido, apellido);}
    void setEmail(const char* email) {strcpy(_email, email);}
    void setEstado(bool estado) {_estado = estado;}
    void setFechaRegistro(Fecha fechaRegistro) {
        _fechaRegistro = fechaRegistro;
    }

    // Getters
    int getTipoDocumento();
    const char* getNroDocumento();
    const char* getNombre();
    const char* getApellido();
    const char* getEmail();
    bool getEstado();
    Fecha getFechaRegistro();
};

// Constructores
Persona::Persona(int tipoDocumento, const char* nroDocumento, const char* nombre, const char* apellido, const char* email, bool estado, Fecha fechaRegistro) {
    setTipoDocumento(tipoDocumento);
    setNroDocumento(nroDocumento);
    setNombre(nombre);
    setApellido(apellido);
    setEmail(email);
    setEstado(estado);
    setFechaRegistro(fechaRegistro);
}

// Interfaces
void Persona::Mostrar() {
    cout << "Tipo de documento: " << getTipoDocumento() << endl;
    cout << "Nro de documento: " << getNroDocumento() << endl;
    cout << "Nombre: " << getNombre() << endl;
    cout << "Apellido: " << getApellido() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Estado: " << getEstado() << endl;
    cout << "Fecha registro: " << getFechaRegistro().toString() << endl;
}

// Getters
int Persona::getTipoDocumento() {
    return _tipoDocumento;
}

const char* Persona::getNroDocumento() {
    return _nroDocumento;
}

const char* Persona::getNombre() {
    return _nombre;
}

const char* Persona::getApellido() {
    return _apellido;
}

const char* Persona::getEmail() {
    return _email;
}

bool Persona::getEstado() {
    return _estado;
}

Fecha Persona::getFechaRegistro() {
    return _fechaRegistro;
}


class Usuario: private Persona {
private:
    char _usuario[30];
    char _contrasenia[30];
    int _tipoPerfil; // Puede ser: ( 1. SUPERADMINISTRADOR | 2. ADMINISTRADOR | 3. SUPERVISOR | 4. USUARIO )

public:
    // Constructores
    Usuario(int tipoDocumento = 0, const char* nroDocumento = "null", const char* nombre = "null", const char* apellido = "null", const char* email = "null", bool estado = "false", Fecha fechaRegistro = Fecha(), const char* usuario = "null", const char* contrasenia = "null", int tipoPerfil = 0);

    // Interfaces

    // Setters
    void setUsuario(const char* usuario);
    void setContrasenia(const char* contrasenia);
    void setTipoPerfil(int tipoPerfil);

    // Getters
    const char* getUsuario();
    const char* getContrasenia();
    int getTipoPerfil();

};

// Constructores
Usuario::Usuario(int tipoDocumento, const char* nroDocumento, const char* nombre, const char* apellido, const char* email, bool estado, Fecha fechaRegistro, const char* usuario, const char* contrasenia, int tipoPerfil) {
    setTipoDocumento(tipoDocumento);
    setNroDocumento(nroDocumento);
    setNombre(nombre);
    setApellido(apellido);
    setEmail(email);
    setEstado(estado);
    setFechaRegistro(fechaRegistro);
    setUsuario(usuario);
    setContrasenia(contrasenia);
    setTipoPerfil(tipoPerfil);
}

// Interfaces

void Mostrar();

// Setters
void Usuario::setUsuario(const char* usuario) {
    strcpy(_usuario, usuario);
}

void Usuario::setContrasenia(const char* contrasenia) {
    strcpy(_contrasenia, contrasenia);
}

void Usuario::setTipoPerfil(int tipoPerfil) {
    _tipoPerfil = tipoPerfil;
}

// Getters

const char* Usuario::getUsuario() {
    return _usuario;
}

const char* Usuario::getContrasenia() {
    return _contrasenia;
}

int Usuario::getTipoPerfil() {
    return _tipoPerfil;
}

int main() {

    const char SUPERUSUARIO[30] = "admin";

    Persona reg(1, "33781477", "Nahuel", "Alvez", "nahue.alvez@gmail.com", true, Fecha().fechaActual());

    // --------------------------------------------------------------
    //   EMPRESA S.A. - CUIT                             26/04/2023
    // --------------------------------------------------------------








    // --------------------------------------------------------------
    //   Desarrollado por Grupo - 2023
    // --------------------------------------------------------------

    reg.Mostrar();

    return 0;
}
