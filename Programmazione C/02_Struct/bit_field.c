#include <stdio.h>
#include <stdint.h>

/*
 * RADIO_STATUS REGISTER (16 bit)
 * ------------------------------
 * Questo è un esempio realistico di un registro di stato di una piccola radio
 * integrata in un dispositivo IoT. Molti chip radio BLE/Sub-GHz espongono
 * registri simili per comunicare al firmware lo stato della trasmissione,
 * ricezione, livello del segnale e modalità operative.
 *
 * Nel nostro esempio, il registro è largo 16 bit. I bit sono suddivisi così:
 *
 *  - powered_on : 1 bit   → la radio è alimentata
 *  - tx_busy    : 1 bit   → trasmissione in corso
 *  - rx_busy    : 1 bit   → ricezione in corso
 *  - error      : 1 bit   → errore generico segnalato dall'hardware
 *
 *  - channel    : 4 bit   → numero del canale radio (0–15)
 *  - rssi_level : 3 bit   → livello RSSI quantizzato (0–7)
 *  - modulation : 2 bit   → tipo di modulazione
 *                          0 = FSK, 1 = GFSK, 2 = LoRa, 3 = OFDM
 *
 *  - (unnamed)  : 3 bit   → bit non utilizzati (riservati a futuri ampliamenti)
 *
 * Totale: 1 + 1 + 1 + 1 + 4 + 3 + 2 + 3 = 16 bit
 *
 * Nota importante:
 *   Il layout dei bitfield è implementation-defined: questo esempio va bene per
 *   uso didattico o interno, ma non è adatto per protocolli su filo o strutture
 *   binarie portabili.
 */

typedef struct {
    unsigned powered_on : 1;
    unsigned tx_busy    : 1;
    unsigned rx_busy    : 1;
    unsigned error      : 1;

    unsigned channel    : 4;
    unsigned rssi_level : 3;
    unsigned modulation : 2;

    unsigned            : 3;  // bit non usati
} radio_status_t;

static const char *modulation_name[] = {
    "FSK", "GFSK", "LoRa", "OFDM"
};

void radio_status_print(radio_status_t st)
{
    printf("RADIO STATUS REGISTER\n");
    printf("----------------------\n");
    printf("  Powered on   : %s\n", st.powered_on ? "YES" : "NO");
    printf("  TX busy      : %s\n", st.tx_busy ? "YES" : "NO");
    printf("  RX busy      : %s\n", st.rx_busy ? "YES" : "NO");
    printf("  Error flag   : %s\n", st.error ? "YES" : "NO");
    printf("  Channel      : %u\n", st.channel);
    printf("  RSSI level   : %u\n", st.rssi_level);
    printf("  Modulation   : %s\n",
           (st.modulation < 4 ? modulation_name[st.modulation] : "UNKNOWN"));

    
    uint16_t raw = *(uint16_t *)&st; //il casting rimuove la vista della struct
    printf("  Raw hex      : 0x%04X\n", raw); // Stampa il valore grezzo a 16 bit
}

int main(void)
{
    radio_status_t st = {0};

    /* Configurazione plausibile di stato radio */
    st.powered_on = 1;
    st.tx_busy = 0;
    st.rx_busy = 1;
    st.error = 0;

    st.channel = 7; //cosa succede se carichiamo valori fuori range? tipo = 25
    st.rssi_level = 3;
    st.modulation = 2;   // LoRa

    radio_status_print(st);

    return 0;
}