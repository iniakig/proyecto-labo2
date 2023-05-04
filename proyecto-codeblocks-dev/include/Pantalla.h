#ifndef PANTALLABASE_H
#define PANTALLABASE_H

#include <iostream>
#include <string>
#include <string.h>

#include "../rlutil.h"

class Pantalla
{
private:
    std::string _titulo;
    std::string _mensajeInterno;
    std::string _cuerpo;
    std::string _mensajeExterno;
    std::string _textoOpciones;
    std::string _mensajeUltimo;

    // Ejes Y de referencia  para posicionar bloques en pantalla
    const int posicionYInicial = 5; // Setea posici�n Y del inicio del bloque de t�tulo
    const int posicionYNavegacion = 18; // Setea posiscion Y del inicio del bloque de navegaci�n

public:
    // Constructores
    Pantalla(std::string titulo = "T�tulo de pantalla", std::string mensajeInterno = "Esto es un mensaje en la cabecera", std::string cuerpo = "Este es el cuerpo del mensaje con varias l�neas.\n\t\t\t   Esto nos permite poder visualizar m�s texto de informaci�n.\n\t\t\t   Adem�s, �queda bien!.", std::string mensajeExterno = "Eleg� una opci�n y presion� <Enter>", std::string textoOpciones = "1. CONTINUAR  |  666. SALIR", std::string mensajeUltimo = "OPCI�N SELECCIONADA: ");

    // Interfaces
    void pantalla();
    void desplegarPantallaBase();
    void desplegarLogin();
    void desplegarCrearPrimerAdmin();
    // void pantalla(std::string tipoDePantalla);

    std::string imprimirLineas(int cantidad);
    std::string imprimirDobleLineas(int cantidad);
    std::string imprimirAsteriscos(int cantidad);
    void centrarTexto(std::string texto, int posy);

    // Setters
    void setTitulo(std::string titulo);
    void setMensajeInterno(std::string mensajeInterno);
    void setCuerpo(std::string cuerpo);
    void setMensajeExterno(std::string mensajeExterno);
    void setTextoOpciones(std::string textoOpciones);
    void setMensajeUltimo(std::string mensajeUltimo);

    // Getters
    std::string getTitulo();
    std::string getMensajeInterno();
    std::string getCuerpo();
    std::string getMensajeExterno();
    std::string getTextoOpciones();
    std::string getMensajeUltimo();
};

#endif // PANTALLABASE_H
