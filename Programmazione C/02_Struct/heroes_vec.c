#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    printf("              Eroe: %s\n", h->name); //pei ipuntatori a struct si usa la freccia ->, non il punto .
    printf("            Classe: %s\n", h->role);
    printf("Grido di battaglia: ");

    if (h->battlecry[0] != '\0')
        printf("\"%s\"\n", h->battlecry);
    else
        printf("(none)\n");

    printf("           Livello: %d\n\n", h->level);
}

/* Aumenta il livello dell’eroe */
void hero_level_up(hero_t *h) //Uso del puntatore per modificare direttamente l’oggetto nello scope delchiamante
{
    h->level++;
}

int main(void)
{
    /* Ruoli come literali condivisi (puntatori a stringa costante) */
    const char *roles[] = { "Warrior", "Mage", "Rogue", "Paladin" };

    /* Array di struct hero_t: il party */
    hero_t party[5];    //Prova a creare un array dinamico con malloc()

    /* Inizializzazione usando hero_create() */
    party[0] = hero_create("Frodo",  "Per l’Orda!",roles[3], 12);  // Paladin
    party[1] = hero_create("Morgana", "By the arcane!",roles[1], 15);  // Mage
    party[2] = hero_create("Valeera", NULL, roles[2], 10);  // Rogue
    party[3] = hero_create("Garrosh", NULL, roles[0], 14);  // Warrior
    party[4] = hero_create("Jaina",  "For the Alliance!", roles[1], 16);  // Mage
    
    /* Imposto un battlecry a posteriori*/
    snprintf(party[2].battlecry, sizeof party[0].battlecry,
             "For the Lich King!");
            

    printf("=== PARTY MEMBERS ===\n\n");

    /* Stampa tutti i membri del party */
    for (int i = 0; i < 5; ++i) {
        hero_print(&party[i]);
    }

    return 0;
}
