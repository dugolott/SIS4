# Scheda di Esercizi – Errori Tipici con `struct` in C

Per ciascun frammento di codice:
1. **Individua l'errore.**
2. **Spiegane la causa.**
3. **Propone una correzione.**

---

## **Esercizio 1**
```c
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Punto;

int main(void) {
    Punto p = {10, 20};

    printf("Coordinate: %d, %d\n", p->x, p->y);
    return 0;
}
```

---

## **Esercizio 2**
```c
#include <stdio.h>

struct Persona {
    char nome[32];
    int eta;
};

int main(void) {
    Persona p = {"Mario", 30};
    printf("%s ha %d anni\n", p.nome, p.eta);
    return 0;
}
```

---

## **Esercizio 3**
```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char codice[4];
    int quantita;
} Prodotto;

int main(void) {
    Prodotto pr;

    strcpy(pr.codice, "ABC123");
    pr.quantita = 10;

    printf("Codice: %s  Quantità: %d\n", pr.codice, pr.quantita);
    return 0;
}
```

---

## **Esercizio 4**
```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char *nome;
    int eta;
} Studente;

int main(void) {
    Studente s;

    strcpy(s.nome, "Mario Rossi");
    s.eta = 20;

    printf("%s ha %d anni\n", s.nome, s.eta);
    return 0;
}
```

---

## **Esercizio 5**
```c
#include <stdio.h>

typedef struct {
    int valore;
} Nodo;

int main(void) {
    Nodo *p = NULL;

    p->valore = 10;
    printf("Valore: %d\n", p->valore);
    return 0;
}
```

---

## **Esercizio 6**
```c
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Punto;

Punto *crea_punto(int x, int y) {
    Punto p;
    p.x = x;
    p.y = y;

    return &p;
}

int main(void) {
    Punto *pp = crea_punto(3, 4);
    printf("Punto: (%d, %d)\n", pp->x, pp->y);
    return 0;
}
```

---

## **Esercizio 7**
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[20];
    int eta;
} Persona;

int main(void) {
    int n = 10;

    Persona *v = malloc(n * sizeof(Persona*));
    if (!v) return 1;

    v[0].eta = 30;
    printf("Eta[0] = %d\n", v[0].eta);

    free(v);
    return 0;
}
```

---

## **Esercizio 8**
```c
#include <stdio.h>

typedef struct {
    int saldo;
} Conto;

void deposita(Conto c, int importo) {
    c.saldo += importo;
}

int main(void) {
    Conto conto = { .saldo = 100 };

    deposita(conto, 50);
    printf("Saldo finale: %d\n", conto.saldo);
    return 0;
}
```

---

## **Esercizio 9**

```c
#include <stdio.h>

typedef struct {
    char name[20];
    int age;
    double salary;
} employee_t;

void stampa_eta(employee_t empls[]) {
    int n = sizeof(empls) / sizeof(employee_t);  // ERRORE INTENZIONALE
    for (int i = 0; i < n; i++) {
        printf("%d\n", empls[i].age);
    }
}

int main(void) {
    employee_t empls[10] = {{"Jack", 43, 1956.8}};
    stampa_eta(empls);
    return 0;
}
```

---

## **Esercizio 10**

```c
#include <stdio.h>

typedef struct {
    char name[20];
    int age;
    double salary;
} employee_t;

int main(void) {
    employee_t empls[10] = {{"Jack", 43, 1956.8}};
    employee_t *pE = empls;

    pE = pE + 10;   // ERRORE INTENZIONALE

    printf("%d\n", pE->age);
    return 0;
}
```

---

## ## **Esercizio 11**

```c
#include <stdio.h>

typedef struct {
    char name[20];
    int age;
    double salary;
} employee_t;

int main(void) {
    employee_t *pE;     // ERRORE INTENZIONALE: puntatore non inizializzato

    pE->age = 40;       // uso di un puntatore non valido
    pE->salary = 2000;

    printf("%d - %.2f\n", pE->age, pE->salary);

    return 0;
}

```