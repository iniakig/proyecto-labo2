#ifndef PERMISO_H
#define PERMISO_H


class Permiso
{
private:
    bool _lectura;
    bool _escritura;
    bool _modificacion;
    bool _baja;

public:
    // Constructores
    Permiso(bool lectura = 0, bool escritura = 0, bool modificacion = 0, bool baja = 0);

    // Setters
    void setLectura(bool lectura);
    void setEscritura(bool escritura);
    void setModificacion(bool modificacion);
    void setBaja(bool baja);

    // Getters
    bool getLectura();
    bool getEscritura();
    bool getModificacion();
    bool getBaja();
};

#endif // PERMISO_H
