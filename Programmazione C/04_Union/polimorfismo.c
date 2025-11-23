#include <stdio.h>
#include <string.h>

// ============================================
// TAGGED UNION: un valore può essere 3 tipi
// ============================================

typedef enum { INT, FLOAT, STRING } Type;

typedef struct {
    Type type;          // TAG: che tipo contiene?
    union {
        int i;          // intero
        float f;        // decimale
        char s[32];     // stringa
    } data;
} Value;

// ============================================
// FUNZIONI DI CREAZIONE
// ============================================

Value make_int(int n) {
    Value v;
    v.type = INT;
    v.data.i = n;
    return v;
}

Value make_float(float n) {
    Value v;
    v.type = FLOAT;
    v.data.f = n;
    return v;
}

Value make_string(const char *str) {
    Value v;
    v.type = STRING;
    strncpy(v.data.s, str, 49);
    v.data.s[49] = '\0';
    return v;
}

// ============================================
// STAMPA (pattern matching sul tipo)
// ============================================

void print_value(Value v) {
    switch (v.type) {
        case INT:
            printf("INT: %d", v.data.i);
            break;
        case FLOAT:
            printf("FLOAT: %.2f", v.data.f);
            break;
        case STRING:
            printf("STRING: \"%s\"", v.data.s);
            break;
    }
}

// ============================================
// OPERAZIONI: somma intelligente
// ============================================

Value add(Value a, Value b) {
    // INT + INT
    if (a.type == INT && b.type == INT) {
        return make_int(a.data.i + b.data.i);
    }
    
    // Se uno è FLOAT, converti tutto a FLOAT
    if (a.type == FLOAT || b.type == FLOAT) {
        float fa = (a.type == INT) ? a.data.i : a.data.f;
        float fb = (b.type == INT) ? b.data.i : b.data.f;
        return make_float(fa + fb);
    }
    
    // STRING + STRING (concatenazione)
    if (a.type == STRING && b.type == STRING) {
        char result[50];
        snprintf(result, 50, "%s%s", a.data.s, b.data.s);
        return make_string(result);
    }
    
    //if ((a.type == STRING && b.type != STRING)||(b.type == STRING && a.type != STRING))
    // ...converto in stringa e concateno

    printf("Errore: tipi incompatibili!\n");
    return make_int(0);
}

// ============================================
// TEST
// ============================================

int main() {
    printf("=== MINI-INTERPRETE CON UNION ===\n\n");
    
    // Array di valori misti!
    Value vars[5] = {
        make_int(42),
        make_float(3.14),
        make_string("Ciao"),
        make_int(10),
        make_string(" Mondo")
    };
    
    printf("Variabili in memoria:\n");
    for (int i = 0; i < 5; i++) {
        printf("[%d] ", i);
        print_value(vars[i]);
        printf("\n");
    }
    
    printf("\n--- OPERAZIONI ---\n\n");
    
    // Somme diverse
    Value r1 = add(vars[0], vars[3]);  // 42 + 10
    printf("INT + INT = ");
    print_value(r1);
    printf("\n");
    
    Value r2 = add(vars[0], vars[1]);  // 42 + 3.14
    printf("INT + FLOAT = ");
    print_value(r2);
    printf("\n");
    
    Value r3 = add(vars[2], vars[4]);  // "Ciao" + " Mondo"
    printf("STRING + STRING = ");
    print_value(r3);
    printf("\n");
    
    // testa il caso STRING + INT o STRING + FLOAT

    printf("\n--- VANTAGGIO UNION ---\n");
    printf("sizeof(Value) = %zu bytes\n", sizeof(Value));
    printf("Senza union: %zu bytes (spreco!)\n", 
           sizeof(Type) + sizeof(int) + sizeof(float) + 50);
    
    return 0;
}

/* L'avvento del Polimorfismo e della Detipizzazione
La tagged union è il modo del C di ottenere polimorfismo (stessa funzione, comportamenti diversi) e 
type safety (controllo a runtime) senza OOP. È il ponte tra C puro e linguaggi moderni come Rust.
*/