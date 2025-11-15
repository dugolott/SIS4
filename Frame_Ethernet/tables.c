/* =========================================================================
 *  tables.c  --  Lookup Table statiche per OUI (MAC vendor) e SAP (LLC)
 * ========================================================================= */

#include <stdint.h>
#include "tables.h"
#include <stddef.h>

/* -------------------------------------------------------------------------
 *  STRUTTURE DATI INTERNE
 * ------------------------------------------------------------------------- */

/* Entry per la tabella OUI → produttore */
typedef struct {
    uint32_t oui;          /* 24 bit più significativi del MAC */
    const char *vendor;    /* Nome produttore */
} oui_entry_t;

/* -------------------------------------------------------------------------
 *  LUT OUI (valori reali, subset significativo)
 * ------------------------------------------------------------------------- */

static const oui_entry_t oui_table[] = {
    {0x000C29, "VMware, Inc."},
    {0x3C5A37, "Apple, Inc."},
    {0x00163E, "Cisco Systems, Inc."},
    {0xF0DE71, "Intel Corporate"},
    {0xB827EB, "Raspberry Pi Foundation"},
    {0xD850E6, "Samsung Electronics"},
    {0x001E06, "Hewlett-Packard"},
    {0x00155D, "Dell Inc."},
    {0x000D93, "Hon Hai Precision (Foxconn)"},
    {0xF4F5A5, "Xiaomi Communications"},
    {0x70E284, "Google, Inc."},
    {0xBC305B, "ASUSTek Computer Inc."},
    {0x0013EF, "Sony Corporation"},
    {0x0009B0, "LG Electronics"},
    {0xC83A35, "Lenovo Mobile Communication"},
};

static const size_t oui_table_count = sizeof(oui_table) / sizeof(oui_table[0]);

/* -------------------------------------------------------------------------
 *  LUT SAP (Logical Link Control – DSAP/SSAP)
 *  Implementata come array diretto indicizzato da codice SAP (0–255)
 * ------------------------------------------------------------------------- */

static const char *sap_table[256] = {
    [0x00] = "Null LSAP",
    [0x02] = "LLC Sub-layer Management",
    [0x04] = "IBM SNA Path Control",
    [0x06] = "DOD IP",
    [0x08] = "PROWAY-LAN",
    [0x0E] = "PROWAY-LAN (IEC 955)",
    [0x42] = "IEEE 802.1 Bridge Spanning Tree",
    [0xAA] = "SNAP (SubNetwork Access Protocol)",
    [0xE0] = "NetBIOS",
    [0xF0] = "IBM NETBIOS",
    [0xFE] = "ISO Network Layer",
};

static const size_t sap_table_count = 256;

/* -------------------------------------------------------------------------
 *  LUT ETHERTYPE 
 *  Implementata come ...
 * ------------------------------------------------------------------------- */

//Codifica qui il dizionario/tabella Ethertype

//...

/* -------------------------------------------------------------------------
 *  FUNZIONI PUBBLICHE (da implementare)
 * ------------------------------------------------------------------------- */
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
const char *protocol_name(uint16_t value){

    // ...
}
const char *oui_lookup(uint32_t oui)
{
   // ...
}
const char *sap_lookup(uint8_t sap){
    // ...  
}