#ifndef PROGRAMA_H
#define PROGRAMA_H

#include "UsuarioActivo.h"
#include "ProductoMenu.h"
#include "MarcaMenu.h"
#include "ClienteMenu.h"
#include "ConfiguracionMenu.h"


class Programa
{
    private:
        bool _estadoLogin;
        bool _estadoPrograma;

        UsuarioActivo _usuarioActivo;
        ProductoMenu _productoMenu;
        MarcaMenu _marcaMenu;
        ClienteMenu _clienteMenu;
        ConfiguracionMenu _configuracionMenu;

    public:
        // Constructores
        Programa(bool estado = false);

        // Interfaces
        //void login(bool& estadoPrograma, bool& estadoLogin);
        //void ejecutar(bool& estadoPrograma, bool& estadoLogin);
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
