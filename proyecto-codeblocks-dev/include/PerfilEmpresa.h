#ifndef PERFILEMPRESA_H
#define PERFILEMPRESA_H


class PerfilEmpresa
{
private:
    char _CUIT[12];
    char _razonSocial[30];
    char _direccion[30];
    int _piso;
    char _oficina[3];
    char _localidad[30];
    char _CP[8];

public:
    // Constructores
    PerfilEmpresa();

    // Interfaces

    // Setters
    void setCUIT(const char* CUIT);
    void setRazonSocial(const char* razonSocial);
    void setDirecion(const char* direccion);
    void setPiso(int piso);
    void setOficina(const char* oficina);
    void setLocalidad(const char* localidad);
    void setCP(const char* CP);

    // Getters
    const char* getCUIT();
    const char* getRazonSocial();
    const char* getDireccion();
    int getPiso();
    const char* getOficina();
    const char* getLocalidad();
    const char* getCP();


};

#endif // PERFILEMPRESA_H
