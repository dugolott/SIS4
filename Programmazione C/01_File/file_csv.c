#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void scrivi_csv(const char *filename, char delim) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Errore apertura file in scrittura");
        return;
    }

    fprintf(f, "nome%ceta%csalary\n", delim, delim);
    fprintf(f, "Mario%c30%c1800.50\n", delim, delim);
    fprintf(f, "Luca%c25%c1500.00\n",  delim, delim);
    fprintf(f, "Anna%c40%c2200.00\n",  delim, delim);

    fclose(f);
}

void parse_line(char *line, char delim) {
    char sep[2] = { delim, '\0' };

    char *token = strtok(line, sep);
    if (!token) return;
    char nome[64];
    strncpy(nome, token, sizeof(nome));
    nome[sizeof(nome)-1] = '\0';

    token = strtok(NULL, sep);
    if (!token) return;
    int eta = atoi(token);

    token = strtok(NULL, sep);
    if (!token) return;
    float stipendio = (float)strtod(token, NULL);

    printf("%-6s  eta=%2d  stipendio=%.2f\n",
           nome, eta, stipendio);
}

void leggi_csv(const char *filename, char delim) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Errore apertura file in lettura");
        return;
    }

    char buf[256];

    /* salta eventuale intestazione */
    if (!fgets(buf, sizeof(buf), f)) {
        if (ferror(f)) perror("Errore lettura");
        fclose(f);
        return;
    }

    while (fgets(buf, sizeof(buf), f)) {
        buf[strcspn(buf, "\r\n")] = '\0';
        parse_line(buf, delim);
    }

    if (ferror(f))
        perror("Errore di lettura");

    fclose(f);
}

int main(void) {
    const char *file = "dati.csv";
    char delim = ';';

    scrivi_csv(file, delim);
    leggi_csv(file, delim);

    return 0;
}
