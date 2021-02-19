#include "state.h"

connState *conn_bucket[BUCKET_SIZE];
actionState *action_bucket[BUCKET_SIZE];
int packet_number = 0;
int cxid = 0;
int action_flow = 0;
/*
 * Returns a string with the source and 
 * destination Ips and ports
 *
 */

int get_hash(packetinfo *pi){
    printf("get_hash function\n");
   
    uint32_t int32_saddr = get_int_ip(pi->h_ip->saddr);
    uint32_t int32_daddr = get_int_ip(pi->h_ip->daddr);


    return CXT_HASH4(int32_saddr, ntohs(pi->h_tcp->src_port), int32_daddr, ntohs(pi->h_tcp->dst_port),pi->h_ip->proto);
}

uint32_t get_int_ip(u_char* addr){
    uint8_t int8_addr[4]; 
    int n;
    for(n = 0; n<4;n++){
	 int8_addr[n] = (uint8_t)addr[n];
    }
    uint16_t int16_addr1 =  (uint16_t)(int8_addr[1] << 8) | (uint16_t)(int8_addr[0]);
    uint16_t int16_addr2 =  (uint16_t)(int8_addr[3] << 8) | (uint16_t)(int8_addr[2]);
    uint32_t int32_addr = (uint32_t)(int16_addr2 << 16) | (uint32_t)(int16_addr1);

    return int32_addr;
}

//add to bucket
void append_to_conn_list(connState* conn_state){
    printf("append to conn list function\n");
    int hash = conn_state->hash;
    connState * head = conn_bucket[hash];

    /* * New connections are pushed on to the head of bucket[s_hash] */
    conn_state->next = head;
    if (head != NULL) {
        // are we doubly linked?
        head->prev = conn_state;
    }
    conn_bucket[hash] = conn_state;

}

//add to bucket
void append_to_action_list(actionState* action_state){
    printf("append to action list function\n");
    int hash =action_state->hash;
    actionState* head = action_bucket[hash];

    /* * New connections are pushed on to the head of bucket[s_hash] */
    action_state->next = head;
    if (head != NULL) {
        // are we doubly linked?
        head->prev = action_state;
    }
    action_bucket[hash] = action_state;

}

void remove_conn_state_node(connState* conn_state, connState ** bucket_ptr)
{
    printf("remove-conn-state-node function\n");
    connState* prev = conn_state->prev;       /* OLDER connections */
    connState* next = conn_state->next;       /* NEWER connections */

    if (prev == NULL) {
        // beginning of list
        *bucket_ptr = next;
        // not only entry
        if (next)
            next->prev = NULL;
    } else if (next == NULL) {
        // at end of list!
        prev->next = NULL;
    } else {
        // a node.
        prev->next = next;
        next->prev = prev;
    }

    /*
     * Free and set to NULL 
     */
    free(conn_state);
    conn_state = NULL;
}

void remove_action_state_node(actionState* action_state, actionState ** bucket_ptr)
{
    printf("remove-action-state-node function\n");
    actionState* prev = action_state->prev;       /* OLDER connections */
    actionState* next = action_state->next;       /* NEWER connections */

    if (prev == NULL) {
        // beginning of list
        *bucket_ptr = next;
        // not only entry
        if (next)
            next->prev = NULL;
    } else if (next == NULL) {
        // at end of list!
        prev->next = NULL;
    } else {
        // a node.
        prev->next = next;
        next->prev = prev;
    }

    /*
     * Free and set to NULL 
     */
    free(action_state);
    action_state = NULL;
}

void remove_hash_conn_node(int cxid, int hash)
{
	printf("remove-hash-conn-node function\n");
	connState* conn_state = conn_bucket[hash];
	while (conn_state != NULL) {
	   	if (conn_state->cxid == cxid) {
			break;
            	}
        	conn_state = conn_state->prev;
	}

	/* remove from the hash */
        if (conn_state->prev)
        	conn_state->prev->next = conn_state->next;
        if (conn_state->next)
        	conn_state->next->prev = conn_state->prev;
        connState *tmp = conn_state;

        conn_state = conn_state->prev;

        remove_conn_state_node(tmp, &conn_bucket[hash]);
	if (conn_state == NULL) {
        	conn_bucket[hash] = NULL;
        }

}



void remove_hash_action_node(actionState* action_state, int hash)
{
	
	printf("remove-hash-action-node function\n");
	/* remove from the hash */
        if (action_state->prev)
        	action_state->prev->next = action_state->next;
        if (action_state->next)
        	action_state->next->prev = action_state->prev;
        actionState *tmp = action_state;

        action_state = action_state->prev;

        remove_action_state_node(tmp, &action_bucket[hash]);
	if (action_state == NULL) {
        	action_bucket[hash] = NULL;
        }

}

//todo
void state_expunge_expired()
{
    packet_number++;
    printf("\n\n");
    printf("packet_number %d\n", packet_number);

    //printf("state_expunge_expired function\n");
    time_t current = time(NULL);
    actionState* action_state;
    int iter;

    int ended, expired = 0;
    time_t check_time = time(NULL);

    for (iter = 0; iter < BUCKET_SIZE; iter++) {
        action_state = action_bucket[iter];
        while (action_state != NULL) {
	    //printf("out time not remove_hash_action_node\n");
            if (difftime(action_state->time, current) > EXPIRE_STATE) {
		//printf("out time real remove_hash_action_node\n");
        	remove_hash_action_node(action_state, iter);
		remove_hash_conn_node(action_state->cxid, iter);
            } else {
                action_state = action_state->prev;
            }
        } // end while cxt
    } // end for buckets
}



connState* create_conn_node(packetinfo *pi){
    printf("Creating conn Node\n");
    cxid++;
    printf("flow_number %d\n",cxid);
    connState* conn_state = (connState*)malloc(sizeof(connState));
    memcpy(conn_state->src_ip, pi->h_ip->saddr,4);
    conn_state->src_prt= pi->h_tcp->src_port;
    memcpy(conn_state->dst_ip, pi->h_ip->daddr,4);
    conn_state->dst_prt = pi->h_tcp->dst_port;
    
    conn_state->cxid = cxid;
    pi->cxid = cxid;
    conn_state->hash = pi->hash;
    conn_state->proto = (uint8_t)pi->h_ip->proto;

    //printf("Added to hash\n");
    append_to_conn_list(conn_state);

    return conn_state;
}

actionState* create_action_node(packetinfo *pi){
    printf("Creating action Node\n");
    action_flow++;
    printf("action_flow %d\n",action_flow);    

    actionState* action_state = (actionState*)malloc(sizeof(actionState));
    
    action_state->time = time(NULL);
    action_state->cxid = pi->cxid;
    
    action_state->hash = pi->hash;
    

    //printf("Added to hash\n");
    append_to_action_list(action_state);

    return action_state;
}

//Checks the state of the node if available
//and checks with the rules is necessary.
//Returns the action the firewall should take 
//for the packet.
void process_with_conn_state(packetinfo *pi){
        printf("process with conn state function\n");

        int hash = get_hash(pi);
    
        printf("HASH %d\n",hash);
	pi->hash = hash;
        //SYN ACK Packet
        connState* conn_state = find_conn_state(pi);
        if(conn_state == NULL){
   	    	conn_state = create_conn_node(pi);
	}
	else{
		pi->cxid = conn_state->cxid;
	} 	    
	    
}

//Checks the state of the node if available
//and checks with the rules is necessary.
//Returns the action the firewall should take 
//for the packet.
rule_type_t process_with_action_state(packetinfo *pi){
        printf("process with action state function\n");

        actionState* action_state = find_action_state(pi);
            
 
	    if(action_state == NULL){
   	    	action_state = create_action_node(pi);

	    	char* sadr = ip_string(pi->h_ip->saddr);
            	char* dadr = ip_string(pi->h_ip->daddr);
            	rule_type_t rt=  get_firewall_action(rule_list, sadr, dadr, ntohs(pi->h_tcp->src_port), ntohs(pi->h_tcp->dst_port));    
            	free(sadr);
            	free(dadr);
	    	if(rt==PASS){
			printf("update_state OPEN\n");
            		action_state->state = OPEN;
            	}
	    	else{
			printf("update_state CLOSED\n");
			action_state->state = CLOSED;
	    	}
	    	return rt;
	    } 	    
	    

	    state_t s = action_state->state;
            printf("STATE %i\n", s);
	    action_state->time = time(NULL);
            if(s==OPEN){
                return PASS;
            }
	    else{
		return BLOCK;
	    }    
    
}


connState* find_conn_state(packetinfo *pi){

	printf("find conn state\n");
	connState* conn_state = conn_bucket[pi->hash];
	char* sadr = ip_string(pi->h_ip->saddr);
        char* dadr = ip_string(pi->h_ip->daddr);
	u_short src_port = pi->h_tcp->src_port;
        u_short dst_port = pi->h_tcp->dst_port;

        while (conn_state != NULL) {
	   
	    if ((strcmp(ip_string(conn_state->src_ip), sadr) == 0)&& (strcmp(ip_string(conn_state->dst_ip), dadr) == 0) 
			&& (conn_state->src_prt == src_port) && (conn_state->dst_prt == dst_port)){
		return conn_state;
		//break;
            }else if((strcmp(ip_string(conn_state->src_ip), dadr) == 0)&& (strcmp(ip_string(conn_state->dst_ip), sadr) == 0) 
			&& (conn_state->src_prt == dst_port) && (conn_state->dst_prt == src_port)){
		return conn_state;
		//break;
	    }
           conn_state = conn_state->prev;
            
        } 
	return NULL;
}

actionState* find_action_state(packetinfo *pi){

	printf("find action state\n");
	actionState* action_state = action_bucket[pi->hash];

        while (action_state != NULL) {
	   
	    if (action_state->cxid == pi->cxid) {
		return action_state;
		//break;
            }
           action_state = action_state->prev;
            
        } 
	return NULL;
}







