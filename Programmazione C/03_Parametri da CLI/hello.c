#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int times = 1;
    int shout = 0;

    if (argc < 2) {
        printf("Uso: %s <nome> [--times N] [--shout]\n", argv[0]);
        return 1;
    }

    const char *nome = argv[1]; //parametro obbligatorio
    

    /* Parsing semplificato degli argomenti */
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--times") == 0 && i + 1 < argc) {
            times = atoi(argv[++i]);   // preleva il numero dopo --times
            //Attenzione! nessun controllo sull'input
        }
        else if (strcmp(argv[i], "--shout") == 0) {
            shout = 1;
        }
        else {
            printf("Opzione sconosciuta: %s\n", argv[i]);
        }
    }

    /* Stampa finale */
    for (int k = 0; k < times; k++) {
        if (shout)
            printf("CIAO %s!!!\n", nome);
        else
            printf("Ciao %s\n", nome);
    }

    return 0;
}
