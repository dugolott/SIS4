# Parser di Frame Ethernet in Linguaggio C

---

### 🎯 Obiettivo
Realizzare un programma **modulare** in linguaggio C che decodifichi frame Ethernet in formato esadecimale, leggendo i dati da file di testo o da standard input.  
Il programma dovrà:
1. Leggere frame in formato esadecimale da tastiera o file di testo
2. Decodificare l'header Ethernet
3. Stampare a video le seguenti informazioni:
- Indirizzi MAC di sorgente e destinazione  (con decodifica MAC se decode=1)
- Decodifica dei successivi campi in base al tipo di frame:
- Tipo di frame (Ethernet II / 802.3 / SNAP)  
- Ethertype e nome del protocollo di livello superiore (ARP, IPv4, ICMP, ecc.)
- SAP e nome del protocollo LLC (se 802.3 LLC)

---

### 🧱 Struttura del progetto
Il progetto è composto da diversi moduli:

|   File     |  Descrizione |
|------------|--------------|
| `net_frame.h` | Tipi di dati e prototipi per il parsing Ethernet, LLC, SNAP (consegna)|
| `eth_frame.c` | Funzioni per il parsing e la stampa dei frame Ethernet (da implementare)|
| `tables.c / tables.h` | Tabelle statiche (OUI e SAP) e funzioni di lookup |
| `main.c` | Funzione principale e logica di esecuzione |
| `frames.txt` | File di test con frame di esempio |

---

### 🗺️ Roadmap di lavoro

#### 🔹 **Fase 1 – Decodifica Ethernet II (livello base)**
Partendo dai sorgenti del libro (pag.9 e pag. 12/13) e dal codice già visto a lezione, completare il modulo `eth_frame.c` per decodificare i frame Ethernet II.:

1. Implementare le funzioni **minime necessarie** per:
   - Leggere un frame da file di testo o da tastiera (`read_frame_from_text_file`)
   - convertire la stringa esadecimale in byte (`hex_to_bytes`);
   - estrarre l’header Ethernet (`parse_ethernet`);
   - stampare i campi con `print_eth_summary()`, `print_mac()` e `protocol_name()`.

2. Verificare il corretto riconoscimento del campo **Ethertype** e del protocollo incapsulato.

3. Testare la decodifica con i seguenti **frame Ethernet II**:

#### 🔹 **Fase 2 – Decodifica LLC e SNAP**
Il programma dovrà:

- leggere frame da file o da stdin
- distinguere Ethernet II e 802.3
- decodificare LLC > SNAP se necessario
- stampare un riepilogo completo dei livelli decodificati

#### Passi da seguire:

1. **Aggiungere il parsing dei parametri da linea di comando (CLI)**:
   - Nessun argomento → input da `stdin`
   - Un argomento → percorso file contenente i frame
   - `-h` o `--help` → mostra l’uso
   - Errore per più di un argomento
   - suggerimento:implementa una funzione `cli_parse()`

2. **Riconoscere frame 802.3 oltre a Ethernet II**:
   - `type_or_len >= 0x0600` → Ethernet II (già implementato)
   - `type_or_len < 0x0600` → 802.3  →  richiama `parse_llc()` (da implementare)
   - e di conseguenza `parse_snap()`

3. **Aggiornare il main** per gestire:
   ```
   CLI → lettura frame → parse_ethernet → parse_llc → parse_snap → stampa
   ```

4. **Completare e integrare strutture** in `tables.c`:
   - completare `sap_table` e `sap_lookup()`
   - se non ancora fatto, aggiungere opportuna struttura per Ethertype `ethertype_table`e conseguente funzione di lookup sglegliendo tra le tecniche illustrate
   - aggiornare funzioni per la stampa dei nomi LLC, SNAP e OUI

---

#### 🧩 Frame di test

##### **1️⃣ ARP (broadcast, Ethertype 0x0806)**

```
FF FF FF FF FF FF 00 11 22 33 44 55 08 06 00 01 08 00 06 04 00 01 00 11 22 33 44 55 C0 A8 01 0A 00 00 00 00 00 00 C0 A8 01 01
```

---

##### **2️⃣ IPv4 (Ethertype 0x0800)**

```
AA BB CC DD EE FF 00 11 22 33 44 55 08 00 45 00 00 14 00 00 40 00 40 06 00 00 C0 A8 01 0A C0 A8 01 01
```

---

##### **3️⃣ ICMP Echo Request (ping)**

```
11 22 33 44 55 66 00 11 22 33 44 55 08 00 45 00 00 1C 00 01 00 00 40 01 00 00 C0 A8 01 0A C0 A8 01 01 08 00 F7 FF 00 01 00 01 50 69 6E 67 21
```

---

##### **4️⃣ IPv6 (Ethertype 0x86DD)**

```
33 33 00 00 00 16 00 11 22 33 44 55 86 DD 60 00 00 00 00 08 3A FF FE 80 00 00 00 00 00 00 00 11 22 FF FE 33 44 55 FF 02 00 00 00 00 00 00 00 00 00 00 00 00 00 16
```

---

### 🚀 Consegna

- Implementare e testare le funzioni minime per la **fase 1**.  
- Il programma deve leggere un frame da:
  - file di testo (`frames.txt`) **oppure**
  - input da tastiera (tramite `stdin`).
- Stampare:
  - MAC sorgente e destinazione (con decodifica, se `decode=1`);
  - Ethertype (valore e protocollo noto);
  - eventuale tipo di frame (Ethernet II / 802.3).

---

### 🧩 Estensioni future (roadmap didattica)

| Fase | Obiettivo |
|------|------------|
| **2** | Aggiungere parsing 802.3 + LLC + SNAP e caricamento frame come parametri CLI |
| **3** | Integrare la LUT OUI per decodificare i vendor MAC |
| **4** | Estendere a protocolli superiori (ARP, IPv4, ICMP, ecc.) |

---

### 📦 Suggerimento
Nel file `frames.txt`, scrivi ogni frame su una sola riga, anche con spazi:
```text
# Frame di test IPv4
AA BB CC DD EE FF 00 11 22 33 44 55 08 00 45 00 00 14 ...
```

La funzione `read_frame_from_text_file()` ignorerà i commenti (`#`) e gli spazi.

---

### ✍️ Note
- Mantieni il codice modulare: ogni file ha un ruolo preciso.
- Documenta le funzioni con commenti in stile Doxygen.
- Puoi aggiungere nuovi Ethertype o SAP aggiornando le LUT in `tables.c`.

---
