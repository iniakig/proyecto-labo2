#ifndef USUARIOACTIVO_H
#define USUARIOACTIVO_H

#include <string>

class UsuarioActivo
{
    private:
        char _alias[15];

    public:
        UsuarioActivo();

        bool crearArchivo(UsuarioActivo usuarioActivo);
        std::string leerArchivo();

        void setAlias(std::string alias);
        std::string getAlias();


};

#endif // USUARIOACTIVO_H
