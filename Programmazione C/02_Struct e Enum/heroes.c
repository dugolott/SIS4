#include <stdio.h>
#include <string.h>

/* ========================================================
 *   Introduzione a struct + typedef (stile professionale)
 *   Convenzione: tipi definiti dall’utente finiscono con _t
 * ======================================================== */

/* Struttura dati per rappresentare un personaggio RPG */
typedef struct {
    char name[16];
    char battlecry[32];
    char* role;
    int  level;
} hero_t;

/* Crea un nuovo eroe */
hero_t hero_create(const char *name, const char *battlecry, const char *role, int level)
{
    hero_t h;

    strncpy(h.name,  name, sizeof(h.name));
    h.name[sizeof(h.name)-1] = '\0';    //Garantisco che sia terminata

    snprintf(h.battlecry, sizeof(h.battlecry), "%s", battlecry);   //Alternativa sicura
    //strncpy(h.battlecry,  battlecry, sizeof(h.battlecry));
    // h.battlecry[sizeof(h.battlecry)-1] = '\0';
    h.role = (char*)role;
    h.level = level;
    return h;       //Ritorno per valore (copia)
}

/* Stampa i dettagli dell’eroe */
void hero_print(const hero_t *h) //Uso del puntatore per efficienza
{
    printf("     Eroe: %s\n", h->name); //pei ipuntatori a struct si usa la freccia ->, non il punto .
    printf("   Classe: %s\n", h->role);
    printf("Battlecry: %s\n", h->battlecry);
    printf("  Livello: %d\n\n", h->level);
}

/* Aumenta il livello dell’eroe */
void hero_level_up(hero_t *h) //Uso del puntatore per modificare direttamente l’oggetto nello scope delchiamante
{
    h->level++;
}

int main(void)
{
    hero_t h1 = hero_create("Frodo", "Non sono stato io!", "Paladino", 12);
    hero_t h2 = hero_create("Morgana", "Per l’Orda!","Maga", 15);

    printf("=== RUBRICA EROI RPG ===\n\n");

    hero_print(&h1);
    hero_print(&h2);

    printf("Arthas sale di livello!\n\n");
    hero_level_up(&h1);

    hero_print(&h1);

    return 0;
}
