#ifndef USUARIOACTIVO_H
#define USUARIOACTIVO_H

#include <string>

class UsuarioActivo
{
    private:
        int _id;
        int _rol;

        int getId();
        int getRol();

    public:
        UsuarioActivo();

        void setId(int id);
        void setRol(int rol);
        bool crearArchivo(UsuarioActivo usuarioActivo);
        int getIdUsuarioActivo(); // Estos getters traen directamente del archivo
        int getRolUsuarioActivo(); // Estos getters traen directamente del archivo
};

#endif // USUARIOACTIVO_H
