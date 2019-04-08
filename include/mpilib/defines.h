#ifndef MANETSIMS_DEFINES_H
#define MANETSIMS_DEFINES_H

#ifndef BAUDRATE
#define BAUDRATE 34800
#endif

/* Id/Source */
#define CTRLR 0

/* Tags */
#define TX_PKT 1
#define TX_PKT_DATA 111

#define RX_PKT 2
#define RX_PKT_DURATION 22
#define RX_PKT_END 222
#define RX_PKT_DATA 2222

#define SLEEP 3
#define SLEEP_DURATION 33

#define INFORM 4

#define SET_LOCATION 5
#define UPDATE_LOCATION 55
#define UPDATE_LOCATION_DATA 555

#define NODE_INFO 7

#define LINK_MODEL 8
#define LINK_MODEL_LINK 88

#define HANDSHAKE 10
#define READY 110
#define DIE 101

/* Using declarations */
using octet = unsigned char;


#endif /* MANETSIMS_DEFINES_H */
