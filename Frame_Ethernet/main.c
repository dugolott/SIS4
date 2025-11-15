#include <stdio.h>
#include <stdint.h>
#include "eth_frame.h"

#define MAX_FRAME_BYTES 1518 //MTU + Ethernet header
//...

int main()
{
    payload_t frame;
    eth_frame_t eth;
    FILE *fp = stdin;
    uint8_t buf[MAX_FRAME_BYTES];
    int len;

    // apro il file di test o leggo da stdin
    //...

    while (1) {
        len = read_frame_from_text_file(fp, buf, sizeof(buf));

        if (len == 0) {
            /* EOF raggiunto */
            break;
        }

        if (len < 0) {
            fprintf(stderr, "Errore: frame non valido o troppo lungo, riga ignorata.\n");
            continue;
        }

        /* Prepara la vista sul buffer (payload_t) */
        frame.data = buf;
        frame.len  = (size_t)len;

        if (parse_ethernet(&frame, &eth) < 0) {
            fprintf(stderr, "Errore: frame troppo corto per un header Ethernet.\n");
            continue;
        }

        /* Stampa il riepilogo dell'header Ethernet */
        print_eth_summary(&eth);

        putchar('\n');
    }



    return 0;
}