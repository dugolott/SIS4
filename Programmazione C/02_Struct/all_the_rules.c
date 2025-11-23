#include <stdio.h>
#include <stddef.h>  // per offsetof()
char s[10];
// ============================================
// PARTE 1: NOTAZIONE . vs ->
// ============================================

typedef struct {
    int x;
    int y;
} Point;

void demo_notation() {
    printf("=== NOTAZIONE . vs -> ===\n\n");
    
    // Variabile normale: accesso ai membri con l'operatore .
    Point p1;
    p1.x = 10;
    p1.y = 20;
    
    printf("p1 (stack): x=%d, y=%d\n", p1.x, p1.y);
    
    // Puntatore a struct
    Point *ptr = &p1;
    
    // METODO 1: dereferenziare poi accedere con .
    (*ptr).x = 30;  // ← parentesi OBBLIGATORIE!
    (*ptr).y = 40;
    
    printf("Dopo (*ptr).x = 30: x=%d, y=%d\n", p1.x, p1.y);
    
    // METODO 2: notazione freccia (equivalente)
    ptr->x = 50;  // ← più leggibile, stessa cosa!
    ptr->y = 60;
    
    printf("Dopo ptr->x = 50: x=%d, y=%d\n", p1.x, p1.y);
    
    /* REGOLA:
    - variabile.campo   ← accesso diretto
    - puntatore->campo  ← accesso tramite puntatore
    - (*puntatore).campo ← equivalente ma scomodo
    */
   puts("\n Premi INVIO per continuare ...");
   scanf("%s", &s);
}

// ============================================
// PARTE 2: PADDING E ALLINEAMENTO
// ============================================



// Struct MAL progettata
struct Bad {
    char a;      // 1 byte
    int b;       // 4 bytes
    char c;      // 1 byte
    int d;       // 4 bytes
};

// Struct BEN progettata (stesso contenuto)
struct Good {
    int b;       // 4 bytes
    int d;       // 4 bytes
    char a;      // 1 byte
    char c;      // 1 byte
};

// Struct per visualizzare padding
struct ShowPadding {
    char a;     // 1 byte
                // [3 byte padding]
    int b;      // 4 bytes
    char c;     // 1 byte
                // [3 byte padding]
    double d;   // 8 bytes
};

void demo_alignment() {

    printf("=== ALLINEAMENTO E PADDING ===\n\n");
    printf("L'ordine dei MEMEBRI è importante! \n\n");
    printf("STRUCT MAL PROGETTATA:\n");
    printf("struct Bad { char, int, char, int }\n");
    printf("  Somma membri: 1 + 4 + 1 + 4 = 10 bytes\n");
    printf("  Dimensione reale: %zu bytes\n", sizeof(struct Bad));
    printf("  Spazio sprecato: %zu bytes\n\n", 
           sizeof(struct Bad) - 10);
    
    printf("STRUCT BEN PROGETTATA:\n");
    printf("struct Good { int, int, char, char }\n");
    printf("  Somma membri: 4 + 4 + 1 + 1 = 10 bytes\n");
    printf("  Dimensione reale: %zu bytes\n", sizeof(struct Good));
    printf("  Spazio sprecato: %zu bytes\n\n", 
           sizeof(struct Good) - 10);
    
    // Visualizza offset dei membri
    printf("OFFSET DEI MEMBRI (struct Bad):\n");
    printf("  a (char):  offset %zu\n", offsetof(struct Bad, a));
    printf("  b (int):   offset %zu  ← +3 byte padding!\n", 
           offsetof(struct Bad, b));
    printf("  c (char):  offset %zu\n", offsetof(struct Bad, c));
    printf("  d (int):   offset %zu  ← +3 byte padding!\n", 
           offsetof(struct Bad, d));
    
    printf("\nOFFSET DEI MEMBRI (struct Good):\n");
    printf("  b (int):   offset %zu\n", offsetof(struct Good, b));
    printf("  d (int):   offset %zu\n", offsetof(struct Good, d));
    printf("  a (char):  offset %zu\n", offsetof(struct Good, a));
    printf("  c (char):  offset %zu  ← NO padding!\n", 
           offsetof(struct Good, c));
    
    printf("\n");
    puts("\n Premi INVIO per continuare ...");
    scanf("%s", &s);
}

// ============================================
// PARTE 3: VISUALIZZAZIONE MEMORIA
// ============================================

void print_bytes(void *ptr, size_t size) {
    unsigned char *bytes = (unsigned char *)ptr; //vista a byte dell'oggetto passato -> serializzo
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
        if ((i + 1) % 8 == 0) printf(" ");
    }
    printf("\n");
}

void demo_memory_layout() {
    printf("=== LAYOUT IN MEMORIA ===\n\n");
    
    struct ShowPadding sp;
    sp.a = 'A';      // 0x41
    sp.b = 0x12345678;
    sp.c = 'B';      // 0x42
    sp.d = 3.14159;
    
    printf("struct ShowPadding sp = {\n");
    printf("  .a = 'A',\n");
    printf("  .b = 0x12345678,\n");
    printf("  .c = 'B',\n");
    printf("  .d = 3.14159\n");
    printf("};\n\n");
    
    printf("Byte in memoria (padding visibile):\n");
    printf("Offset:   0  1  2  3  4  5  6  7   8  9 10 11 12 13 14 15  16 17 18 19 20 21 22 23\n");
    printf("         ");
    print_bytes(&sp, sizeof(sp));
    
    printf("\nSpiegazione:\n");
    printf("  [00]       = 'A' (0x41)\n");
    printf("  [01-03]    = 3B padding (garbage)\n");
    printf("  [04-07]    = int 0x12345678\n");
    printf("  [08]       = 'B' (0x42)\n");
    printf("  [09-15]    = 7B padding (garbage)\n");
    printf("  [16-23]    = double 3.14159\n");
    
    printf("\nDimensione: %zu bytes (solo %zu utili!)\n", 
           sizeof(sp), sizeof(char) + sizeof(int) + sizeof(char) + sizeof(double));
    
    printf("\n\n ...sapresti otimizzare questa struct?\n");

    printf("\n");
    puts("\n Premi INVIO per continuare ...");
    scanf("%s", &s);
}

// ============================================
// PARTE 4: PACKED STRUCT (senza padding)
// ============================================

// GCC/Clang: rimuove padding
struct __attribute__((packed)) Packed {
    char a;
    int b;
    char c;
    int d;
};

void demo_packed() {
    printf("=== STRUCT PACKED (no padding) ===\n\n");
    
    printf("struct __attribute__((packed)) Packed\n");
    printf("  Dimensione: %zu bytes\n", sizeof(struct Packed));
    printf("  Somma membri: %zu bytes\n", 
           sizeof(char) + sizeof(int) + sizeof(char) + sizeof(int));
    printf("  → NESSUN padding!\n\n");
    
    printf("⚠️  ATTENZIONE:\n");
    printf("  - Accesso più LENTO (CPU deve fare più lavoro)\n");
    printf("  - Su alcune architetture: può causare CRASH\n");
    printf("  - Usare solo per: protocolli di rete, file binari\n");
    
    printf("\n");
}

// ============================================
// PARTE 5: ESEMPIO PRATICO
// ============================================

typedef struct {
    char name[20];
    int age;
    float salary;
} Employee;

void demo_practical() {
    printf("=== ESEMPIO PRATICO ===\n\n");
    
    // Array di struct
    Employee team[3] = {
        {"Alice", 28, 45000.0},
        {"Bob", 35, 52000.0},
        {"Carol", 42, 68000.0}
    };
    
    printf("Team (array di struct):\n");
    for (int i = 0; i < 3; i++) {
        // Accesso diretto con .
        printf("%d. %s, %d anni, %.2f€\n", 
               i + 1, team[i].name, team[i].age, team[i].salary);
    }
    
    printf("\n");
    
    // Puntatore che scorre l'array
    printf("Usando puntatore:\n");
    Employee *ptr = team;  // punta al primo elemento
    
    for (int i = 0; i < 3; i++) {
        // Accesso con ->
        printf("%d. %s, %d anni, %.2f€\n", 
               i + 1, ptr->name, ptr->age, ptr->salary);
        ptr++;  // avanza al prossimo Employee
    }
    
    printf("\nAritmetica puntatori:\n");
    printf("  &team[0] = %p\n", (void*)&team[0]);
    printf("  &team[1] = %p (diff: %td bytes = sizeof(Employee))\n", 
           (void*)&team[1], (char*)&team[1] - (char*)&team[0]);
    
    printf("\n");
}

// ============================================
// MAIN
// ============================================

int main() {
    demo_notation();
    demo_alignment();
    demo_memory_layout();
    demo_packed();
    demo_practical();
    
    printf("=== REGOLE D'ORO ===\n");
    printf("1. usa '.' per variabili, '->' per puntatori\n");
    printf("2. ordina membri: grandi prima, piccoli dopo\n");
    printf("3. padding esiste per velocità CPU\n");
    printf("4. __attribute__((packed)) solo se necessario\n");
    
    return 0;
}