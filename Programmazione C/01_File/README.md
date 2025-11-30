# Gestione dei File in C

In C, la gestione dei file avviene principalmente tramite la libreria standard `<stdio.h>`. 
Le operazioni sui file sono fondamentalmente:

- apertura,
- lettura,
- scrittura,
- chiusura.

Al momento dell'apertura, è indispensabile specificare la modalità in cui si intende aprire il file (di `accesso`'). Le modalità più comuni sono:

- lettura: `"r"`, ovvero non si può scrivere
- scrittura: `"w"`, sovrascrive il file o lo crea se non esiste
- append: `"a"`, aggiunge in coda (se il file non esiste, lo crea)

Alcune di queste modalità non permettono di leggere dal file (es. `"w"` e `"a"`).
Inoltre, possono essere combinate con il simbolo `+` per permettere sia la lettura che la scrittura (es. `"r+"`, `"w+"`, `"a+"`).
Oltre a queste modalità di accesso, è necessario specificare se il file è di tipo **testo** o **binario** (quest'ultimo si ottiene aggiungendo la lettera `b` alla modalità di accesso, es. `"rb"`, `"wb"`).

Seppure semplice, la gestione dei file passa attraverso **syscall** di basso livello, quindi è importante gestire correttamente errori e risorse allocate. Questo include:

- controllare che l'apertura del file sia andata a buon fine,
- chiudere sempre i file aperti con `fclose()` per evitare perdite di memoria e corruzione dei dati.
- verificare errori di lettura/scrittura con `ferror()` e `feof()`.

---

## 1. Apertura di un file

Si usa `fopen()`:
```c
FILE *f = fopen("dati.txt", "r");
if (!f) {
    perror("Errore apertura file");
}
```

Sintassi:
```
fopen(const char* file_path, const char* mode);
```
Restituisce un `FILE*` oppure `NULL` in caso di errore.

---

## 2. Modalità di accesso

### Modalità testo
| Modalità | Significato |
|----------|-------------|
| `"r"`  | lettura (file deve esistere) |
| `"w"`  | scrittura (sovrascrive il file) |
| `"a"`  | aggiunta in coda |
| `"r+"` | lettura e scrittura |
| `"w+"` | lettura/scrittura, sovrascrive |
| `"a+"` | lettura/scrittura, puntatore in coda |

### Modalità binarie
Aggiunta del carattere `b`:
- `"rb"`, `"wb"`, `"ab"`, `"rb+"`, `"wb+"`, `"ab+"`

Esempi:
```c
FILE *t = fopen("log.txt", "a");    // testo, append
FILE *b = fopen("raw.bin", "wb");    // binario, scrittura
```

---

## 3. Lettura da file

### `fscanf()` – Formattata (testo)
```c
int x;
fscanf(f, "%d", &x);
```

### `fgets()` – Una riga intera
```c
char buf[128];
fgets(buf, sizeof(buf), f);
```

### `fread()` – Binario
```c
size_t n = fread(buffer, 1, size, f);
```

---

## 4. Scrittura su file

### `fprintf()` – Formattata (testo)
```c
fprintf(f, "Valore = %d\n", x);
```

### `fputs()` – Testo semplice
```c
fputs("ciao\n", f);
```

### `fwrite()` – Binario
```c
fwrite(&x, sizeof(x), 1, f);
```

---

## 5. Chiusura del file

```c
fclose(f);
```
Obbligatorio per:
- svuotare il buffer di scrittura (allocato dal Sistema Operativo),
- liberare risorse associate al `descrittore` del file,
- evitare corruzione del file stesso (forza il flush dei dati ancora presenti nel buffer).

---

## 6. Controllo errori

### `ferror()`
```c
if (ferror(f)) printf("Errore I/O\n"); // dopo operazioni di lettura/scrittura ferror() restituisce un valore diverso da zero: codice di errore specifico, cui corrisponde un messaggio stampabile con perror()  
```

### `feof()` – fine file
```c
while (!feof(f)) { ... } // feof() ritorna 0 finché non si raggiunge la fine del file
```

### `perror()`
```c
if (!f) perror("Impossibile aprire file"); // stampa il messaggio di errore associato all'ultima operazione di I/O fallita
```

---

## 7. Esempio completo
```c
FILE *f = fopen("numeri.txt", "w");
if (!f) {
    perror("Errore apertura file: ");
    return 1;
}

for (int i = 0; i < 10; i++){
    fprintf(f, "%d\n", i);
    if (ferror(f)) {
        perror("Errore scrittura file: ");
        fclose(f);
        return 1;
    }
}

fclose(f);

f = fopen("numeri.txt", "r");
if (!f) {
    perror("Errore apertura file: ");
    return 1;
}

int x;
while (fscanf(f, "%d", &x) == 1)
    printf("%d ", x);

fclose(f);
```

---
