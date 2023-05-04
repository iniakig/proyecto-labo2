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
    const int posicionYInicial = 5; // Setea posición Y del inicio del bloque de título
    const int posicionYNavegacion = 18; // Setea posiscion Y del inicio del bloque de navegación

public:
    // Constructores
    Pantalla(std::string titulo = "Título de pantalla", std::string mensajeInterno = "Esto es un mensaje en la cabecera", std::string cuerpo = "Este es el cuerpo del mensaje con varias líneas.\n\t\t\t   Esto nos permite poder visualizar más texto de información.\n\t\t\t   Además, ¡queda bien!.", std::string mensajeExterno = "Elegí una opción y presioná <Enter>", std::string textoOpciones = "1. CONTINUAR  |  666. SALIR", std::string mensajeUltimo = "OPCIÓN SELECCIONADA: ");

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
