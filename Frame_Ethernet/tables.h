#ifndef TABLES_H
#define TABLES_H

#include <stdint.h>

/* Ricerca del produttore OUI */
const char *oui_lookup(uint32_t oui);

/* Ricerca del nome SAP (LLC) */
const char *sap_lookup(uint8_t sap);

#endif /* TABLES_H */