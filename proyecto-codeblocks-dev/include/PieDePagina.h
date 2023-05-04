#ifndef PIEDEPAGINA_H
#define PIEDEPAGINA_H

class PieDePagina
{
private:
    std::string _titulo;
    int _ancho;

public:
    // Constructores
    PieDePagina(std::string titulo, int ancho);

    // Interfaces
    void imprimirPieDePagina();

    // Setters
    void setTitulo(std::string titulo);
    void setAncho(int ancho);

    // Getters
    std::string getTitulo();
    int getAncho();
};

#endif // PIEDEPAGINA_H
