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
        void login();
        void ejecutar();

        // Setters
        void setEstadoLogin(bool estado);
        void setEstadoPrograma(bool estado);

        // Getters
        bool getEstadoLogin();
        bool getEstadoPrograma();
};

#endif // PROGRAMA_H
