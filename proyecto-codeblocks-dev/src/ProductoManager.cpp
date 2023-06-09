#include "ProductoManager.h"
#include "../funciones.h"
#include "string.h"
#include <iostream>
#include <iomanip>
#include <../rlutil.h>
using namespace std;
#include "Marca.h"
#include "MarcaManager.h"
#include "Producto.h"

int ProductoManager::GenerarId()
{
    return _archivo.getCantidadDeRegistros()+1;
}

void ProductoManager::Listar(Producto producto)
{
    cout<<"ID: "<<producto.getID()<<endl;
    cout<<"CATEGORIA: "<<producto.getCategoria()<<endl;
    cout<<"ID MARCA: "<<producto.getIdMarca()<<endl;
    cout<<"MODELO: "<<producto.getModelo()<<endl;
    cout<<"DESCRIPCION: "<<producto.getDescripcion()<<endl;
    cout<<"PRECIO: "<<producto.getPrecio()<<endl;
    cout<<"STOCK: "<<producto.getStock()<<endl;

}

void ProductoManager::ListarTodos()
{
	int cantidadRegistros = _archivo.getCantidadDeRegistros ();

	for (int i = 0; i<cantidadRegistros; i++)
	{
		Producto reg = _archivo.leer(i);
        if (reg.getActivo()==true)
        {
            Listar(reg);
            cout << endl;
        }
	}
}

void ProductoManager::ListarXId(){
	int id;

	cout << "Ingrese el ID: ";
	cin >> id;

	int posicion = _archivo.buscar(id);
	if (posicion >= 0)
	{
		Producto reg = _archivo.leer(posicion);
		Listar(reg);
	}
	else
	{
		cout << "No existe el registro con ID: " << id << endl;
	}
}

void ProductoManager::ListarPorMarca(){
std::string nombre;
    int idMarca;
    MarcaArchivo archivoMarca;
	cout << "Ingrese nombre de la marca: ";
	std::cin>>nombre;

	int posicion = archivoMarca.buscar(nombre);
	if (posicion >= 0)
	{
		Marca marca = archivoMarca.leer(posicion);
		idMarca=marca.getID();
	}
	else
	{
		cout << "MARCA NO EXISTENTE "<< endl;
	}

}
void ProductoManager::HacerCopiaDeSeguridad()
{

    int cantidadRegs = _archivo.getCantidadDeRegistros();

    Producto *vec = new Producto[cantidadRegs];

    if (vec == nullptr)
    {
        cout << "ERROR AL REALIZAR LA COPIA DE SEGURIDAD" << endl;
        return;
    }

    _archivo.leer(vec, cantidadRegs);
    _archivoBkp.vaciar();

    if(_archivoBkp.guardar(vec, cantidadRegs))
    {
        cout << "COPIA DE SEGURIDAD REALIZADA CON EXITO" << endl;
    }
    else
    {
        cout << "ERROR AL REALIZAR LA COPIA DE SEGURIDAD" << endl;
    }

    delete []vec;
}


void ProductoManager::Cargar(){
    int ID;
    int categoria;
    int  idMarca;
    std::string modelo;
    std::string descripcion;
    float precioVenta;
    int stock;
    bool activo=true;
    std::string nombreMarca;
    MarcaManager managerMarca;

    ID=GenerarId();
	std::cout<<"INGRESE CATEGORIA DEL PRODUCTO"<<std::endl;
	std::cin>>categoria;
	cout<<categoria;
	std::cout<<"INGRESE NOMBRE DE LA MARCA DEL PRODUCTO"<<std::endl;
	do{
    nombreMarca=ingresoDeMarcaConValidacion();
	idMarca=managerMarca.cargarDesdeProducto(nombreMarca);
	}while(idMarca<=0);
    std::cout<<"INGRESE MODELO DEL PRODUCTO"<<std::endl;// Convertir a mayuscula pendiente
    std::cin.ignore();
	getline(std::cin, modelo);
	std::cout<<"INGRESE DESCRIPCION DEL PRODUCTO"<<std::endl;// Convertir a mayuscula pendiente
    std::cin.ignore();
	getline(cin, descripcion);
	std::cout<<"INGRESE PRECIO DE VENTA"<<std::endl;
	std::cin>>precioVenta;
	std::cout<<"INGRESE STOCK"<<std::endl;
	std::cin>>stock;

Producto reg(ID, categoria, idMarca,modelo, descripcion, precioVenta, stock, activo);
Listar(reg);
 cout<<"CARGO EL SIGUIENTE PRODUCTO: "<<endl;
        Listar(reg);
        cout<<"GUARDAR? 1--SI // 2--NO: ";
        int opc = ingresoOpcSimpleConValidacion();
        if(opc == 1)
        {
            if(_archivo.guardar(reg))
            {
                cout<<"PRODUCTO AGREGADO CORRECTAMENTE"<<endl;
            }
            else
            {
                cout<<"ERROR AL AGREGAR EL PRODUCTO, INTENTELO NUEVAMENTE"<<endl;
            }
        }

}


void ProductoManager::Editar()
{
    Producto producto;
    int id, posicion;
    std::cout << "INGRESE ID DE PRODUCTO A MODIFICAR" << std::endl;
    std::cin>>id;
    posicion=_archivo.buscar(id);
    if(posicion<0){
    std::cout<<"EL ID NO EXISTE"<<std::endl;
    }else{
    producto=_archivo.leer(posicion);
    int opcion = -1;

    do {
        rlutil::cls();
        std::cout << "ELIJA EL CAMPO QUE DESEA MODIFICAR" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "1. CATEGORIA" << std::endl;
        std::cout << "2. NOMBRE DE MARCA" << std::endl;
        std::cout << "3. MODELO" << std::endl;
        std::cout << "4. DESCRIPCION" << std::endl;
        std::cout << "5. PRECIO DE VENTA" << std::endl;
        std::cout << "6. STOCK" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "0. VOLVER AL MENÚ DE GESTIÓN DE USUARIOS" << std::endl;
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << "OPCIÓN SELECCIONADA: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
        case 0:
            break;
        case 1:
            int categoria;
            std::cout <<"INGRESE CATEGORIA: "<< std::endl;
            std::cin>>categoria;
            producto.setCategoria(categoria);
            _archivo.guardar(producto, posicion);
            break;
        case 2:
            std::cout << std::endl;
            break;
        case 3:
            std::cout << std::endl;
            break;
        case 4:
            std::cout << std::endl;
            break;
        case 5:

            break;
        case 6:

            break;
        default:
            std::cout << "La opción seleccionada es invalida. Ingrese nuevamente." << std::endl;
            break;
        }
    }

    while(opcion != 0);
    }


}
