#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "dati.txt"

/* Scrive alcune righe di esempio */
void scrivi_file(void) {
    FILE *f = fopen(FILE_NAME, "w");
    if (!f) {
        perror("Errore apertura in scrittura");
        return;
    }

    fprintf(f, "Mario\t30\t1800.50\n");
    fprintf(f, "Luca\t25\t1500.00\n");
    fprintf(f, "Anna\t40\t2200.00\n");

    if (fclose(f) != 0)
        perror("Errore chiusura file");
}

/* Legge ogni riga, prima grezza con fgets, poi con fscanf */
void leggi_file(void) {
    FILE *f = fopen(FILE_NAME, "r");
    if (!f) {
        perror("Errore apertura in lettura");
        return;
    }
    int i=0;
    char buf[128];
    while (fgets(buf, sizeof(buf), f)) { //fgets legge una riga completa: ritorna NULL in caso di errore o EOF
        char nome[32];
        int eta;
        float stipendio;

        /* Parsing della riga tabulata:    nome \t eta \t stipendio */
        if (fscanf(f, "%31s\t%d\t%f\n", nome, &eta, &stipendio) == 3) {  //il 31 limita la lunghezza della stringa per evitare overflow
            printf("Letto: %s, %d anni, %.2f euro\n", nome, eta, stipendio);
        } else {
            /* fscanf non trova 3 dati */
            if (ferror(f))
                perror("Errore durante fscanf");
            else
                printf("Riga %d non valida: %s", i, buf);
        }
        i++;
    }

    if (ferror(f))
        perror("Errore di lettura (ferror)");

    fclose(f);
}

int main(void) {
    scrivi_file();
    leggi_file();
    return 0;
}
