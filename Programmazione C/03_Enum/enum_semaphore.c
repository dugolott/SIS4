#include <stdio.h>

/*
 * Un enum in C:
 *  - introduce una serie di COSTANTI INTERE con un nome (LIGHT_RED, ...)
 *  - Associa in progressione ogni ETICHETTA ad un intero 
 *  - è utile per rendere il codice leggibile (niente "0,1,2" magici in giro)
 *
 * NON è:
 *  - una stringa (non puoi stamparlo direttamente con %s)
 *  - un tipo "chiuso" come in altri linguaggi: sotto sotto è simile a un int
 */
typedef enum {
    LIGHT_RED,      // 0
    LIGHT_YELLOW,   // 1
    LIGHT_GREEN     // 2
} traffic_light_t; // per default LIGHT_RED = 0, LIGHT_YELLOW = 1, LIGHT_GREEN = 2
 

/* Converte il valore enum in una stringa leggibile */
const char *light_to_string(traffic_light_t light)
{
    switch (light) {
    case LIGHT_RED:    return "RED";
    case LIGHT_YELLOW: return "YELLOW";
    case LIGHT_GREEN:  return "GREEN";
    default:           return "UNKNOWN";  // cosa succede se il valore non è valido?
    }
}

/* ritorna l'Azione da fare in base al colore del semaforo */
const char *action_for_light(traffic_light_t light)
{
    switch (light) {
    case LIGHT_RED:    return "STOP";
    case LIGHT_YELLOW: return "GET READY";
    case LIGHT_GREEN:  return "GO";
    default:           return "???";
    }
}

int main(void)
{
    traffic_light_t tl = LIGHT_RED;

    printf("Light:  %s\n", light_to_string(tl));
    printf("Action: %s\n\n", action_for_light(tl));

    /* Cambia stato del semaforo */
    tl = LIGHT_GREEN;

    printf("Light:  %s\n", light_to_string(tl));
    printf("Action: %s\n", action_for_light(tl));

    return 0;
}

/*
 * -----------------------------
 * Per capire
 * -----------------------------
 *
 * 1) Cosa succede se provi a stampare tl con:
 *
 *      printf("%d\n", tl);
 *
 *    - Che valore vedi per LIGHT_RED? E per LIGHT_GREEN?
 *    - Cosa ti dice questo sulla "vera" natura dell'enum in C?
 *
 * 2) Prova ad aggiungere un nuovo stato:
 *
 *      LIGHT_BLINKING
 *
 *    - Cosa succede se NON lo gestisci negli switch delle due funzioni? Perchè?
 *    - Cosa succede se fai:
 *
 *      tl = LIGHT_BLINKING;
 *      printf("%s\n", light_to_string(tl));
 *
 * 3) Modifica le costanti enum così:
 *
 *      typedef enum {
 *          LIGHT_RED    = 10,
 *          LIGHT_YELLOW = 20,
 *          LIGHT_GREEN  = 30
 *      } traffic_light_t;
 *
 *    - Cosa stampa printf("%d\n", tl) ora?
 *    - Cambia qualcosa nel funzionamento di light_to_string() e action_for_light()?
 *
 * 4) Prova a scrivere:
 *
 *      int x = 5;
 *      traffic_light_t t2 = x;
 *
 *    - Il compilatore lo accetta?
 *    - Cosa succede se poi passi t2 a light_to_string()?
 *
 * 5) A cosa serve davvero l'enum, se sotto è "solo" un intero?
 *    
 *
 */
