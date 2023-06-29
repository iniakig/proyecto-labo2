#include "Programa.h"

#include "rlutil.h"

#include "Usuario.h"
#include "UsuarioArchivo.h"
#include "Fecha.h"
#include "VentaManager.h"
#include "VentaArchivo.h"

int main()
{
    setSpanish();

    Programa programa;

    while (programa.getEstadoPrograma() == true) {
        if (programa.getEstadoUsuarioRegistrado() == true) {
            programa.login();
            if (programa.getEstadoLogin() == true) {
                programa.ejecutar();
            }
        }
        else {
            programa.registro();
            programa.login();
            if (programa.getEstadoLogin() == true) {
                programa.ejecutar();
            }
        }
    }

    rlutil::hidecursor();
    rlutil::setColor(rlutil::BLACK);
    rlutil::locate(12, 26);

    return 0;
}
