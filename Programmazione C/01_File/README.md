# Gestione dei File in C

Questa pagina riassume l'uso dei file in C tramite la libreria standard `<stdio.h>`, con esempi chiari di:
- apertura,
- modalità di accesso (r/w/a, testo/binario),
- lettura e scrittura,
- chiusura,
- gestione errori.

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
fopen(nome_file, modalità);
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
- svuotare il buffer,
- liberare risorse,
- evitare corruzione del file.

---

## 6. Controllo errori

### `ferror()`
```c
if (ferror(f)) printf("Errore I/O\n");
```

### `feof()` – fine file
```c
while (!feof(f)) { ... }
```

### `perror()`
```c
if (!f) perror("Impossibile aprire file");
```

---

## 7. Esempio completo
```c
FILE *f = fopen("numeri.txt", "w");
if (!f) return 1;

for (int i = 0; i < 10; i++)
    fprintf(f, "%d\n", i);

fclose(f);

f = fopen("numeri.txt", "r");
if (!f) return 1;

int x;
while (fscanf(f, "%d", &x) == 1)
    printf("%d ", x);

fclose(f);
```

---

