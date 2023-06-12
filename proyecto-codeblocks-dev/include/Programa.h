#ifndef PROGRAMA_H
#define PROGRAMA_H


class Programa
{
    private:
        bool _estadoLogin;
        bool _estadoPrograma;
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