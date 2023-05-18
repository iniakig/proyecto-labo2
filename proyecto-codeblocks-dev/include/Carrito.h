#ifndef CARRITO_H
#define CARRITO_H


class Carrito
{
    public:
        Carrito();

        //setters
        void setCantProductos(int cantidad);

        //void setCliente(Cliente cliente);

        //getters
        int getCantProductos();
        //Cliente getCliente();
    protected:
        int _cantProductos;
        //Producto _productos[];
        //Cliente _cliente;

    private:
};

#endif // CARRITO_H
