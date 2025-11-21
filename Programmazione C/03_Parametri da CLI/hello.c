#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int times = 1;
    char buf[100];
    
    if (argc < 2) {
        printf("Uso: %s <nome> [--times N] [--shout]\n", argv[0]);
        return 1;
    }

    
    sprintf(buf, "Ciao %s",argv[1]);

    /* Parsing semplificato degli argomenti */
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--times") == 0 && i + 1 < argc) {
            //printf("--> argv[i+1]: %s\n", argv[i+1]);
            times = atoi(argv[++i]);   // preleva il numero dopo --times
            //Attenzione! nessun controllo sull'input
        }
        else if (strcmp(argv[i], "--shout") == 0) {
            char *str = buf;
            while(*str++) *str = toupper(*str);
            strncpy(str-1,"!!!",4);
        }
        else {
            printf("Opzione sconosciuta: %s\n", argv[i]);
        }
    }
    /* Stampa finale */
    for (int k = 0; k < times; k++) 
        puts(buf);
    
    return 0;
}
