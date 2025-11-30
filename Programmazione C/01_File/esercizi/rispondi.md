# Esercizio – Programma `safe_copy` semplificato

Leggi il seguente sorgente C e rispondi ai quesiti a seguire, senza testare il programma.

```c
  1  #include <stdio.h>
  2  #include <stdlib.h>
  3  #include <string.h>
  4
  5  typedef struct {
  6      long b;
  7      int rl;
  8      int rw;
  9  } S;
 10
 11  void z(S *p) {
 12      if (!p) return;
 13      p->b  = 0;
 14      p->rl = 0;
 15      p->rw = 0;
 16  }
 17
 18  int cpy(const char *s, const char *d, S *p) {
 19      FILE *f1, *f2;
 20      unsigned char buf[128];
 21      size_t n, m;
 22
 23      f1 = fopen(s, "rb");
 24      if (!f1) {
 25          perror("src");
 26          return 1;
 27      }
 28
 29      f2 = fopen(d, "wb");
 30      if (!f2) {
 31          perror("dst");
 32          fclose(f1);
 33          return 2;
 34      }
 35
 36      while ((n = fread(buf, 1, sizeof(buf), f1)) > 0) {
 37          m = fwrite(buf, 1, n, f2);
 38          if (m < n) {
 39              perror("write");
 40              if (p) p->rw++;
 41              fclose(f1);
 42              fclose(f2);
 43              return 3;
 44          }
 45          if (p) p->b += (long)m;
 46      }
 47
 48      if (ferror(f1)) {
 49          perror("read");
 50          if (p) p->rl++;
 51          fclose(f1);
 52          fclose(f2);
 53          return 4;
 54      }
 55
 56      fclose(f1);
 57      fclose(f2);
 58      return 0;
 59  }
 60
 61  int main(int argc, char *argv[]) {
 62      int i, q = 0;
 63      const char *s = NULL, *d = NULL;
 64      S st;
 65      int r;
 66
 67      if (argc < 3 || argc > 4) {
 68          fprintf(stderr, "uso: %s [-q] src dst\n", argv[0]);
 69          return 1;
 70      }
 71
 72      i = 1;
 73      if (argc == 4) {
 74          if (strcmp(argv[i], "-q") == 0) {
 75              q = 1;
 76              i++;
 77          }
 78      }
 79
 80      s = argv[i];
 81      d = argv[i + 1];
 82
 83      z(&st);
 84      r = cpy(s, d, &st);
 85      if (r != 0) {
 86          fprintf(stderr, "err: %d\n", r);
 87          return r;
 88      }
 89
 90      if (!q) {
 91          fprintf(stdout, "copiati: %ld\n", st.b);
 92      }
 93
 94      return 0;
 95  }
```

---

## Quesiti di verifica

Quando possibile, la risposta corretta dovrà essere esattamente l'output o il valore richiesto.

1. Alle righe **5–9** viene dichiarato il tipo `S`: che cosa rappresenta il campo `b`?
2. Alle righe **11–16** la funzione `z` cosa inizializza esattamente nella struct passata?
3. Alla riga **18**, quanti e quali parametri riceve la funzione `cpy`?
4. Alle righe **23–27**, su quale file viene usata `perror` e in quale caso viene chiamata?
5. Alle righe **29–34**, cosa succede ai file già aperti se fallisce l’apertura del file di destinazione?
6. Alla riga **36**, in che modalità viene effettuata la lettura: testuale o binaria? Perché?
7. Alle righe **36–46**, in quale campo della struct `S` viene accumulata la quantità di dati copiati?
8. Alle righe **48–54**, che tipo di errore controlla `ferror(f1)`?
9. Alle righe **67–70**, quali combinazioni di parametri da riga di comando sono considerate valide?
10. Alle righe **72–78**, che significato ha il flag `-q` e quale variabile viene modificata quando è presente?
11. Alle righe **80–81**, che cosa contengono le variabili `s` e `d` dopo il parsing dei parametri?
12. Alle righe **90–92**, su quale stream viene stampato il messaggio finale e in quali condizioni non viene stampato nulla?
13. Alla riga **91**, se la copia termina correttamente e sono stati copiati 2048 byte, cosa stampa esattamente il programma (includi newline e testo)?
14. Alla riga **86**, se l’apertura del file di destinazione fallisce (errore riga 29–34), quale valore numerico viene stampato dopo "err:"?
15. Alla riga **80**, se il programma viene invocato come: `./prog -q in.txt out.txt`
16. quale valore contiene la variabile s dopo il parsing dei parametri?
17. Alla riga **45**, dopo la prima iterazione del ciclo di copia, quale campo della struct S viene modificato e con quale quantità?
18. Alla riga **62**, subito dopo l’inizializzazione della variabile q a 0, quale valore contiene q se il programma viene lanciato senza il flag `-q`?

---
