#ifndef PROGRAMA_H
#define PROGRAMA_H

#include "UsuarioActivo.h"
#include "VentaMenu.h"
#include "ProductoMenu.h"
#include "MarcaMenu.h"
#include "ConfiguracionMenu.h"
#include "ClienteMenu.h"


class Programa
{
    private:
        bool _estadoLogin;
        bool _estadoPrograma;
        bool _estadoUsuarioRegistrado; // Sirve para saber si existe algún usuario registrado

        UsuarioActivo _usuarioActivo;
        VentaMenu _ventaMenu;
        ProductoMenu _productoMenu;
        MarcaMenu _marcaMenu;
        ClienteMenu _clienteMenu;
        ConfiguracionMenu _configuracionMenu;

    public:
        // Constructores
        Programa();

        // Interfaces
        void registro();
        void login();
        void ejecutar();

        // Setters
        void setEstadoLogin(bool estado);
        void setEstadoPrograma(bool estado);
        void setEstadoUsuarioRegistrado(bool estado);

        // Getters
        bool getEstadoLogin();
        bool getEstadoPrograma();
        bool getEstadoUsuarioRegistrado();
};

#endif // PROGRAMA_H
