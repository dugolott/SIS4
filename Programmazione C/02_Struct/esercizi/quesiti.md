# Esercizi su struct, puntatori e sizeof in C

```c
 1 | #include <stdio.h>
 2 |
 3 | typedef struct {
 4 |     char name[20];
 5 |     int age;
 6 |     double salary;
 7 | } employee_t;
 8 |
 9 | int main(void){
10 |     employee_t empls[10] = {{"Jack", 43, 1956.8}};
11 |
12 |     employee_t* pE;
13 |
14 |     pE = empls;
15 |
16 |     pE++;
17 |
18 |     printf("%d\n", pE->age);
19 |     printf("%d\n", sizeof(pE));
20 |     printf("%d", sizeof(employee_t));
21 |
22 |     return 0;
23 | }
```

---

# Quesiti a risposta breve

Per ogni domanda, rispondi in **una frase o un numero**.

 1. Dopo l’istruzione alla riga **10**, cosa contiene l’elemento `empls[1]` dell’array?

 2. Dopo le istruzioni alle righe **14–16**, a quale elemento dell’array `empls` punta il puntatore `pE`?

 3. Alla riga **18**, quale valore verrà **probabilmente** stampato da `pE->age`?

 4. Alla riga **19**, che cosa rappresenta il valore restituito da `sizeof(pE)`?

 5. Alla riga **20**, cosa restituisce `sizeof(employee_t)`? perchè?

 6. Dopo la riga **16**, il campo a cui si riferisce `pE->salary` appartiene a quale elemento dell’array `empls`?

 7. Alla riga **14**, quale espressione è equivalente, come valore, a `pE`?

 8. Che tipo ha l’espressione `pE->salary`?

 9. Quante posizioni di array di tipo `employee_t` viene spostato `pE` dall’istruzione di riga **16**?

10. Tra `sizeof(pE)` e `sizeof(employee_t)`, quale dei due valori dipende dalla piattaforma (es. 32 bit vs 64 bit)?

