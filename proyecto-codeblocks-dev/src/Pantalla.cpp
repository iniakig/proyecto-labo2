#include "Pantalla.h"
#include <algorithm>

// Constructores
Pantalla::Pantalla(std::string titulo, std::string mensajeInterno, std::string cuerpo, std::string mensajeExterno, std::string textoOpciones, std::string mensajeUltimo) {
    setTitulo(titulo);
    setMensajeInterno(mensajeInterno);
    setCuerpo(cuerpo);
    setMensajeExterno(mensajeExterno);
    setTextoOpciones(textoOpciones);
    setMensajeUltimo(mensajeUltimo);
}

// Interfaces
std::string Pantalla::imprimirLineas(int cantidad) {
    std::string lineas;

    for (int i = 0; i < cantidad; i++) {
        lineas += "-";
    }

    return lineas;
}

std::string Pantalla::imprimirDobleLineas(int cantidad) {
    std::string lineas;

    for (int i = 0; i < cantidad; i++) {
        lineas += "=";
    }

    return lineas;
}

std::string Pantalla::imprimirAsteriscos(int cantidad) {
    std::string asteriscos;

    for (int i = 0; i < cantidad; i++) {
        asteriscos += "*";
    }

    return asteriscos;
}

void Pantalla::centrarTexto(std::string texto, int posy) {
	int posx;
	posx = rlutil::tcols() / 2 - texto.size() / 2;
	rlutil::locate(posx, posy);
	std::cout << texto;
}

void Pantalla::desplegarPantallaBase() {
    // Título
    centrarTexto(imprimirLineas(100), posicionYInicial);
    std::string titulo = getTitulo(); // string auxiliar para transformar el título a mayúsculas
    std::transform(titulo.begin(), titulo.end(), titulo.begin(), ::toupper);
    centrarTexto(" " + titulo + " ", posicionYInicial);
    centrarTexto(getMensajeInterno(), posicionYInicial + 2);

    // Cuerpo
    centrarTexto(imprimirAsteriscos(76), posicionYInicial + 4);
    rlutil::locate(28, posicionYInicial + 6);
    std::cout << getCuerpo();
    centrarTexto(imprimirAsteriscos(76), posicionYInicial + 11);

    // Navegación
    centrarTexto(imprimirLineas(100), posicionYNavegacion + 1);
    centrarTexto(getMensajeExterno(), posicionYNavegacion + 2);
    centrarTexto(getTextoOpciones(), posicionYNavegacion + 4);
    centrarTexto(imprimirLineas(100), posicionYNavegacion + 5);
    centrarTexto(getMensajeUltimo(), posicionYNavegacion + 6);
    centrarTexto(imprimirDobleLineas(100), posicionYNavegacion + 7);
}

void Pantalla::desplegarLogin() {
    char usuario[30];
    char contrasenia[30];

    setTitulo("Inicio de sesión");
    setMensajeInterno("Ingresá tus credenciales para ingresar a la aplicación");
    setCuerpo("USUARIO: \n\n\n\t\t\t   CONTRASEÑA: \n\t\t\t ");

    /* Título */
    centrarTexto(imprimirLineas(100), posicionYInicial);
    std::string titulo = getTitulo(); // string auxiliar para transformar el título a mayúsculas
    std::transform(titulo.begin(), titulo.end(), titulo.begin(), ::toupper);
    centrarTexto(" " + titulo + " ", posicionYInicial);

    /* Mensaje */
    rlutil::setColor(rlutil::YELLOW);
    centrarTexto(getMensajeInterno(), posicionYInicial + 2);
    rlutil::setColor(rlutil::WHITE);

    /* Cuerpo */
    centrarTexto(imprimirAsteriscos(76), posicionYInicial + 4);
    rlutil::locate(28, posicionYInicial + 6);
    std::cout << getCuerpo();
    centrarTexto(imprimirAsteriscos(76), posicionYInicial + 11);

    centrarTexto(imprimirLineas(100), posicionYNavegacion + 1);

    rlutil::setColor(rlutil::YELLOW);
    setMensajeExterno("Atención. A los tres intentos de ingresos incorrectos se cerrará la aplicación.");
    centrarTexto(getMensajeExterno(), posicionYNavegacion + 2);
    rlutil::setColor(rlutil::WHITE);


    rlutil::setColor(rlutil::LIGHTMAGENTA);
    rlutil::locate(37, 11);
    std::cin.ignore();
    std::cin.getline(usuario, 30);
    rlutil::locate(40, 14);
    std::cin.getline(contrasenia, 30);
    rlutil::setColor(rlutil::WHITE);

    /* Navegación */
    centrarTexto(imprimirLineas(100), posicionYNavegacion + 5);
    rlutil::setColor(rlutil::YELLOW);
    setMensajeUltimo("<Ingrese cualquier tecla para continuar>");
    centrarTexto(getMensajeUltimo(), posicionYNavegacion + 6);
    rlutil::setColor(rlutil::WHITE);

    centrarTexto(imprimirDobleLineas(100), posicionYNavegacion + 7);
}

void Pantalla::desplegarCrearPrimerAdmin() {
    char usuario[30];
    char contrasenia[30];
    int opcion = -1;

    setTitulo("¡Tu perfil de empresa ya fue creado!");
    setMensajeInterno("Ingresá las credenciales para el perfil administrador");
    setCuerpo("USUARIO: \n\n\n\t\t\t   CONTRASEÑA: \n\t\t\t ");

    /* Título */
    centrarTexto(imprimirLineas(100), posicionYInicial);
    std::string titulo = getTitulo(); // string auxiliar para transformar el título a mayúsculas
    std::transform(titulo.begin(), titulo.end(), titulo.begin(), ::toupper);
    centrarTexto(" " + titulo + " ", posicionYInicial);

    /* Mensaje */
    rlutil::setColor(rlutil::YELLOW);
    centrarTexto(getMensajeInterno(), posicionYInicial + 2);
    rlutil::setColor(rlutil::WHITE);

    /* Cuerpo */
    centrarTexto(imprimirAsteriscos(76), posicionYInicial + 4);
    rlutil::locate(28, posicionYInicial + 6);
    std::cout << getCuerpo();
    centrarTexto(imprimirAsteriscos(76), posicionYInicial + 11);

    rlutil::setColor(rlutil::LIGHTMAGENTA);
    rlutil::locate(37, 11);
    std::cin.ignore();
    std::cin.getline(usuario, 30);
    rlutil::locate(40, 14);
    std::cin.getline(contrasenia, 30);
    rlutil::setColor(rlutil::WHITE);

    /* Navegación */
    centrarTexto(imprimirLineas(100), posicionYNavegacion + 1);

    rlutil::setColor(rlutil::YELLOW);
    setMensajeExterno("¿Los datos ingresados son correctos?");
    centrarTexto(getMensajeExterno(), posicionYNavegacion + 2);
    rlutil::setColor(rlutil::WHITE);

    setTextoOpciones("1. NO, REINGRESAR              2. SÍ, CONTINUAR");
    centrarTexto(getTextoOpciones(), posicionYNavegacion + 4);

    centrarTexto(imprimirLineas(100), posicionYNavegacion + 5);

    setMensajeUltimo("OPCIÓN SELECCIONADA:  ");
    centrarTexto(getMensajeUltimo(), posicionYNavegacion + 6);

    centrarTexto(imprimirDobleLineas(100), posicionYNavegacion + 7);

    rlutil::setColor(rlutil::LIGHTMAGENTA);
    rlutil::locate(70, 24);
    std::cin >> opcion;
    rlutil::setColor(rlutil::WHITE);
}

// Setters
void Pantalla::setTitulo(std::string titulo) {
    _titulo = titulo;
}

void Pantalla::setMensajeInterno(std::string mensajeInterno) {
    _mensajeInterno = mensajeInterno;
}

void Pantalla::setCuerpo(std::string cuerpo) {
    _cuerpo = cuerpo;
}

void Pantalla::setMensajeExterno(std::string mensajeExterno) {
    _mensajeExterno = mensajeExterno;
}

void Pantalla::setTextoOpciones(std::string textoOpciones) {
    _textoOpciones = textoOpciones;
}

void Pantalla::setMensajeUltimo(std::string mensajeUltimo) {
    _mensajeUltimo = mensajeUltimo;
}

// Getters
std::string Pantalla::getTitulo() {
    return _titulo;
}

std::string Pantalla::getMensajeInterno() {
    return _mensajeInterno;
}

std::string Pantalla::getCuerpo() {
    return _cuerpo;
}

std::string Pantalla::getMensajeExterno() {
    return _mensajeExterno;
}

std::string Pantalla::getTextoOpciones() {
    return _textoOpciones;
}

std::string Pantalla::getMensajeUltimo() {
    return _mensajeUltimo;
}

