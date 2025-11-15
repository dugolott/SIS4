#ifndef TABLES_H
#define TABLES_H

#include <stdint.h>

/* ---------------- TABELLA ETHERTYPE / SNAP ------------------------------ */
/**
 * Restituisce il nome del protocollo associato a un Ethertype / protocol_id.
 *  - value : Ethertype (Ethernet II) oppure protocol_id (SNAP)
 *
 * Ritorna una stringa costante (es. "IPv4", "ARP", "IPv6") se noto,
 * altrimenti "Sconosciuto".
 *
 * L'implementazione userà internamente un array statico di proto_desc_t.
 */
const char *protocol_name(uint16_t value);

/* Ricerca del produttore OUI */
const char *oui_lookup(uint32_t oui);

/* Ricerca del nome SAP (LLC) */
const char *sap_lookup(uint8_t sap);

#endif /* TABLES_H */