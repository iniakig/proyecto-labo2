#include "Programa.h"

#include "rlutil.h"

int main()
{
    setSpanish();

    Programa programa;

    while (programa.getEstadoPrograma() == true) {
        programa.login();
        while(programa.getEstadoLogin() == true) {
            programa.ejecutar();
        }
    }

    rlutil::hidecursor();
    rlutil::setColor(rlutil::BLACK);
    rlutil::locate(12, 26);



    return 0;
}
