#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include "packets.h"
#include "rules.h"

#define BUCKET_SIZE  31337
#define EXPIRE_STATE 1


#define CXT_HASH4(src,dst,sp,dp,pr) \
   (( src + dst + sp + dp + pr) % BUCKET_SIZE)



//OPEN=SYN, HALF=SYNACK, ESTABLISHED=ACK
//CLOSED=NOT in state table
typedef enum{OPEN, CLOSED} state_t;

//need to free ip_string when done with node

typedef struct _conn_state {
    u_char src_ip[4];
    u_short src_prt;
    u_char dst_ip[4];
    u_short dst_prt;
    int hash;
    int cxid;
    struct _conn_state* next;//The next state_node in the list
    struct _conn_state* prev;//the rpevious node in the list
}connState;

typedef struct _action_state {
    time_t time; //The last time this connection was active
    state_t state; //The current state of the node
    int hash;
    int cxid;
    struct _action_state* next;//The next state_node in the list
    struct _action_state* prev;//the rpevious node in the list
}actionState;

int get_hash(packetinfo *pi);
void append_to_conn_list(connState* conn_state);
void append_to_action_list(actionState* action_state);
void remove_conn_state_node(connState* conn_state, connState ** bucket_ptr);
void remove_action_state_node(actionState* action_state, actionState ** bucket_ptr);
void remove_hash_conn_node(int cxid, int hash);
void remove_hash_action_node(actionState* action_state, int hash);

void state_expunge_expired();
connState* create_conn_node(packetinfo *pi);
actionState* create_action_node(packetinfo *pi);
void process_with_conn_state(packetinfo *pi);
rule_type_t process_with_action_state(packetinfo *pi);
connState* find_conn_state(packetinfo *pi);
actionState* find_action_state(packetinfo *pi);



/*END GLOBALS*/
#endif
