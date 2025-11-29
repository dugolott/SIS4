# Le `struct` in C
Le `struct` (strutture) in C sono tipi di dato composti che permettono di raggruppare variabili di tipi diversi sotto un unico nome. Sono utili per rappresentare entità complesse con più attributi.

Anche dette "record" o "tipi di dato definiti dall'utente", le `struct` sono fondamentali per organizzare i dati in modo logico e coerente.

La struct è formata da **campi** (membri) che possono essere di qualsiasi tipo di dato, inclusi altri tipi di struct o array.
Per accedere ai campi di una struct, si usa l'operatore punto (`.`) se si ha una variabile struct, o l'operatore freccia (`->`) se si ha un puntatore a struct.


## 1. Dichiarazione e `typedef`
```c
struct Punto {  //definizione della struct
    int x;  //campo x
    int y;  //campo y
};

typedef struct {  //definizione della struct con typedef
    int giorno;
    int mese;
    int anno;
} Data_t;  //Data_t è ora un alias per questa struct: un nuovo tipo di dato
```

---
## 2. Inizializzazione
```c
struct Punto p1 = {10, 20};
struct Punto p2 = {.x = 5, .y = 7};
Data d1 = {25, 12, 2024};
```

---
## 3. Accesso ai campi

```c
struct Punto p = {3, 4};
p.x = 10;
int y = p.y;
```

---
## 4. Puntatori a struct

```c
struct Punto p = {1, 2};
struct Punto *pp = &p;
pp->x = 50;
int t = pp->y;
```

---
## 5. Struct e funzioni

### Passaggio per valore

```c
int distanza2(struct Punto a, struct Punto b) {
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    return dx*dx + dy*dy;
}
```

### Passaggio per riferimento
```c
void trasla(struct Punto *p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
}
```

### Ritorno di una struct
```c
struct Punto crea(int x, int y) {
    struct Punto r = {x, y};
    return r;
}
```

---
## 6. Bitfield
Le bitfield permettono di definire campi di una struct che occupano un numero specifico di bit, utile per risparmiare spazio quando si hanno molti flag booleani o piccoli interi. Trovano applicazione in contesti come protocolli di rete, formati di file binari, e hardware interfacing.
```c
typedef struct Flag {
    unsigned int attivo : 1;
    unsigned int errore : 3;
    unsigned int codice : 12;
} Flag_t;

Flag_t f;
f.attivo = 1;
f.errore = 5;  // Valido solo se rientra nei 3
f.codice = 2048; // Valido solo se rientra nei 12

```

---

## 7. Dimensione struct e allineamento

- Ogni campo è allineato al multiplo del suo tipo.
- Possono esserci padding tra campi e alla fine della struct.

```c
struct A {
    char c;   // 1 byte
    int x;    // 4 byte, riallineato
    char d;   // 1 byte
};
sizeof(struct A); // tipicamente 12 (dipende dall'ABI)
```

Uso di `#pragma pack` (non portabile) per forzare l'impacchettamento:
```c
#pragma pack(push, 1)
struct B {
    char c;
    int x;
    char d;
};
#pragma pack(pop)
```

---

## 8.  Serializzazione di Struct Complesse in C

Vediamo come serializzare e deserializzare una struct complessa in C, confrontando due metodi principali: la serializzazione completa tramite puntatore a struct e la serializzazione manuale campo per campo.

---

### Struct complessa

```c
#define MAX_ESAMI 8

typedef struct {
    char nome[32];
    int  cfu;
    float voto;
} Esame;

typedef struct {
    char nome[32];
    char cognome[32];
    unsigned int matricola;
    unsigned int anno_iscrizione;

    Esame esami[MAX_ESAMI];
    unsigned int num_esami;

    unsigned int attivo     : 1;
    unsigned int in_regola  : 1;
    unsigned int riservato  : 1;
} Libretto;
```

---

### Serializzazione completa tramite puntatore a struct (metodo "potente")

```c
int salva_libretto_binario(const Libretto *l, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) return 0;

    size_t written = fwrite(l, sizeof(*l), 1, f);
    fclose(f);

    return (written == 1);
}
```

Vantaggi:

- Una singola chiamata scrive tutta la struct.
- Se la struct cambia (es. si aggiunge un campo), questa funzione **continua a funzionare senza modifiche**.
- Codice estremamente compatto.

Limiti:

- Richiede stessa architettura ed endianness. (grande limite per la portabilità)
- Non deve contenere puntatori (copierebbe solo l'indirizzo, non i dati).
- Non portabile come formato file a lungo termine, perchè dipende dalla disposizione in memoria.

---

### Serializzazione manuale campo per campo

```c
int salva_libretto_binario_manual(const Libretto *l, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) return 0;

    fwrite(l->nome,          sizeof(l->nome),          1, f);
    fwrite(l->cognome,       sizeof(l->cognome),       1, f);
    fwrite(&l->matricola,    sizeof(l->matricola),     1, f);
    fwrite(&l->anno_iscrizione, sizeof(l->anno_iscrizione), 1, f);

    fwrite(&l->num_esami, sizeof(l->num_esami), 1, f);

    for (unsigned int i = 0; i < l->num_esami && i < MAX_ESAMI; ++i) {
        fwrite(l->esami[i].nome, sizeof(l->esami[i].nome), 1, f);
        fwrite(&l->esami[i].cfu, sizeof(l->esami[i].cfu), 1, f);
        fwrite(&l->esami[i].voto, sizeof(l->esami[i].voto), 1, f);
    }

    unsigned int flags = 0;
    flags |= (l->attivo    & 1u) << 0;
    flags |= (l->in_regola & 1u) << 1;
    flags |= (l->riservato & 1u) << 2;
    fwrite(&flags, sizeof(flags), 1, f);

    fclose(f);
    return 1;
}
```

Svantaggi:

- Codice molto più lungo e fragile.
- Ogni aggiunta/modifica alla struct richiede modifiche sia in scrittura che in lettura.
- L'ordine delle operazioni **deve rimanere identico** alla lettura, pena corruzione del file.

---

