#ifndef PROGRAMA_H
#define PROGRAMA_H


class Programa
{
    private:
        bool _estado;
    public:
        // Constructores
        Programa(bool estado = false);

        // Interfaces
        void login();
        void ejecutar();

        // Setters
        void setEstado(bool estado);

        // Getters
        bool getEstado();
};

#endif // PROGRAMA_H
