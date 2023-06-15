#ifndef USUARIOACTIVO_H
#define USUARIOACTIVO_H

#include <string>

class UsuarioActivo
{
    private:
        char _alias[15];
        int _rol;

        std::string getAlias();
        int getRol();

    public:
        UsuarioActivo();

        void setAlias(std::string alias);
        void setRol(int rol);
        bool crearArchivo(UsuarioActivo usuarioActivo);
        std::string getAliasUsuarioActivo(); // Estos getters traen directamente del archivo
        int getRolUsuarioActivo(); // Estos getters traen directamente del archivo
};

#endif // USUARIOACTIVO_H
