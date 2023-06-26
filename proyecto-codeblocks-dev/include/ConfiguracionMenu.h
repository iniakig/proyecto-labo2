#ifndef CONFIGURACIONMENU_H
#define CONFIGURACIONMENU_H

#include "UsuarioMenu.h"
#include "EmpresaMenu.h"
#include "RespaldoMenu.h"

class ConfiguracionMenu
{
    private:
        UsuarioMenu _usuarioMenu;
        EmpresaMenu _empresaMenu;
        RespaldoMenu _respaldoMenu;

        bool _permisos[3];

    public:
        void mostrar();
        void setPermisos(bool adm, bool sup, bool ven);
};

#endif // CONFIGURACIONMENU_H
