#include <assert.h>
#include "common.h"
#include "prads.h"
#include "cxt.h"
#include "sys_func.h"
#include "config.h"
#include "output-plugins/log.h"

extern globalconfig config;

uint64_t cxtrackerid;
connection *bucket[BUCKET_SIZE];
connState *conn_bucket[BUCKET_SIZE];
actionState *action_bucket[BUCKET_SIZE];

//+++
void connac_notify_flow_created()
{
    connac_stats.flows_active++;
}
//+++


void cxt_init()
{
    cxtrackerid = 0;
}



//+++
void showConnState(connState* conn_state){
    //struct sockaddr_in sa;
    char src_str[INET_ADDRSTRLEN];

   // now get it back and print it
    inet_ntop(AF_INET, &(conn_state->s_ip), src_str, INET_ADDRSTRLEN);
   
    //struct sockaddr_in sa;
    char dst_str[INET_ADDRSTRLEN];

   // now get it back and print it
    inet_ntop(AF_INET, &(conn_state->d_ip), dst_str, INET_ADDRSTRLEN);
    


    printf("---------------ConnState------------------\n");

    printf("src_ip %s\n", src_str);
    printf("ds_ip %s\n", dst_str);
    printf("mac_dst %u",conn_state->ether_dst[0]);
    printf(" %u",conn_state->ether_dst[1]);
    printf(" %u",conn_state->ether_dst[2]);
    printf(" %u",conn_state->ether_dst[3]);
    printf(" %u",conn_state->ether_dst[4]);
    printf(" %u\n",conn_state->ether_dst[5]);
    printf("mac_src %u",conn_state->ether_src[0]);
    printf(" %u",conn_state->ether_src[1]);
    printf(" %u",conn_state->ether_src[2]);
    printf(" %u",conn_state->ether_src[3]);
    printf(" %u",conn_state->ether_src[4]);
    printf(" %u\n",conn_state->ether_src[5]);
    printf("s_port %u\n",conn_state->s_port);
    printf("d_port %u\n",conn_state->d_port);
    printf("cxid  %lu\n",conn_state->cxid);
    printf("reversed %u\n",conn_state->reversed);
    printf("---------------ConnState------------------\n");

}

//+++

//+++
void showConnection(connection* cxt){

     //struct sockaddr_in sa;
    char src_str[INET_ADDRSTRLEN];

   // now get it back and print it
    inet_ntop(AF_INET, &(cxt->s_ip), src_str, INET_ADDRSTRLEN);
   
    //struct sockaddr_in sa;
    char dst_str[INET_ADDRSTRLEN];

   // now get it back and print it
    inet_ntop(AF_INET, &(cxt->d_ip), dst_str, INET_ADDRSTRLEN);
    


    printf("---------------Connection------------------\n");
    //printf("mac_dst %u\n",cxt->ether_dst[0]);
    //printf("mac_src %u\n",cxt->sip->__int_u);
    printf("src_ip %s\n", src_str);
    printf("dst_ip %s\n", dst_str);
    printf("s_port %u\n",cxt->s_port);
    printf("d_port %u\n",cxt->d_port);
    printf("cxid  %lu\n",cxt->cxid);
    printf("reversed %u\n",cxt->reversed);
    printf("start_time %lu\n",cxt->start_time );
    printf("last_pkt_time %lu\n", cxt->last_pkt_time);
    printf("reversed: %u\n",cxt->reversed);
    printf("af %u\n",cxt->af);
    printf("hw_proto %u\n",cxt->hw_proto);
    printf("proto %u\n",cxt->proto);
    printf("s_total_pkts  %lu\n",cxt->s_total_pkts);
    printf("s_total_bytes %lu\n",cxt->s_total_bytes);
    printf("d_total_pkts %lu\n",cxt->d_total_pkts);
    printf("d_total_bytes %lu\n",cxt->d_total_bytes);
    printf("s_tcpFlags %u\n",cxt->s_tcpFlags);
    printf("d_tcpFlags  %u\n",cxt->d_tcpFlags);
    printf("check %u\n",cxt->check);
    printf("---------------Connection------------------\n");

}

//+++

//+++
void showActionState(actionState* action_state){


    printf("---------------actionState------------------\n");
    printf("start_time %lu\n",action_state->start_time );
    printf("last_pkt_time %lu\n", action_state->last_pkt_time);
    printf("cxid: %lu\n",action_state->cxid);
    printf("reversed: %u\n",action_state->reversed);
    printf("af %u\n",action_state->af);
    printf("hw_proto %u\n",action_state->hw_proto);
    printf("proto %u\n",action_state->proto);
    printf("s_total_pkts  %lu\n",action_state->s_total_pkts);
    printf("s_total_bytes %lu\n",action_state->s_total_bytes);
    printf("d_total_pkts %lu\n",action_state->d_total_pkts);
    printf("d_total_bytes %lu\n",action_state->d_total_bytes);
    printf("s_tcpFlags %u\n",action_state->s_tcpFlags);
    printf("d_tcpFlags  %u\n",action_state->d_tcpFlags);
    printf("check %u\n",action_state->check);
    printf("---------------actionState------------------\n");

}



void showAllState(){
 int h;
 uint64_t cxt_cxid[100];
 memset(cxt_cxid, 0, sizeof(cxt_cxid));
 uint64_t action[100];
 memset(action, 0, sizeof(action));
 uint64_t conn[100];
 memset(conn, 0, sizeof(conn));
 int count_cxt = 0;
 int count_action =0;
 int count_conn=0;
 for (h = 0; h < BUCKET_SIZE; h++)
    {        
        connection *cxt = bucket[h];
        actionState *action_state = action_bucket[h];
        connState *conn_state = conn_bucket[h];


        while (conn_state != NULL)
        { 
            printf("-----------conn----h%d------------\n",h);    
            showConnState(conn_state); 
            conn[count_conn] = conn_state->cxid; 
            count_conn++;     
            // Move on to next connection
            conn_state = conn_state->next;
        }   
	while (action_state != NULL)
        {     
            printf("-----------action---h%d------------\n",h);
	    showActionState(action_state); 
            action[count_action] = action_state->cxid; 
            count_action++;     
            // Move on to next connection
            action_state = action_state->next;
        }       
	while (cxt != NULL)
        {     
            printf("----------cxt----h%d------------\n",h);
	    showConnection(cxt);   
            cxt_cxid[count_cxt] = cxt->cxid;
            count_cxt++;    
            // Move on to next connection
            cxt = cxt->next;
        }           
    }
    printf("\n");
    printf("count_cxt %d\n",count_cxt);
    printf("------------------------------------\n");
    int i,m,n;
    for(i = 0; i<= count_cxt; i++){
	printf("%lu,",cxt_cxid[i]);
    }
    printf("\n");
    printf("count_conn%d\n",count_conn);
    printf("------------------------------------\n");
    for(m = 0; m<= count_conn; m++){
	printf("%lu,",conn[m]);
    }
    printf("\n");
    printf("count_action%d\n",count_action);
    printf("------------------------------------\n");
    
    for(i = 0; n<= count_action; n++){
	printf("%lu,",action[n]);
    }


}

void showAllCxid(){
 int h;
 uint64_t cxt_cxid[100];
 uint64_t action[100];
 uint64_t conn[100];
 int count_cxt = 0;
 int count_action =0;
 int count_conn=0;
 for (h = 0; h < BUCKET_SIZE; h++)
    {        
        connection *cxt = bucket[h];
        actionState *action_state = action_bucket[h];
        connState *conn_state = conn_bucket[h];


        while (conn_state != NULL)
        { 
               
       
            conn[count_conn] = conn_state->cxid; 
            count_conn++;     
            // Move on to next connection
            conn_state = conn_state->next;
        }   
	while (action_state != NULL)
        {     
            
            action[count_action] = action_state->cxid; 
            count_action++;     
            // Move on to next connection
            action_state = action_state->next;
        }       
	while (cxt != NULL)
        {     
            cxt_cxid[count_cxt] = cxt->cxid;
            count_cxt++;    
            // Move on to next connection
            cxt = cxt->next;
        }           
    }
    
    printf("----------------cxtrackerid:%lu--------------------\n",cxtrackerid);
    printf("count_cxt %d\n",count_cxt);
    int i,m,n;
    for(i = 0; i<= count_cxt; i++){
	printf("%lu,",cxt_cxid[i]);
    }
    printf("\n");
    printf("count_conn%d\n",count_conn);
    
    for(m = 0; m<= count_conn; m++){
	printf("%lu,",conn[m]);
    }
    printf("\n");
    printf("count_action%d\n",count_action);
    
    for(i = 0; n<= count_action; n++){
	printf("%lu,",action[n]);
    }
    printf("\n");
    printf("----------------cxtrackerid:%lu--------------------\n",cxtrackerid);
    

}



connState *conn_cxt_new(packetinfo *pi){
   
    struct in6_addr ips;
    struct in6_addr ipd;
    connState *conn_state;
    cxtrackerid++;
    conn_state = (connState *) calloc(1, sizeof(connState));
    assert(conn_state);
    conn_state->cxid = cxtrackerid;
//+++
    connac_notify_flow_created();
//+++
   
    if(pi-> af== AF_INET6){
        conn_state->s_ip = PI_IP6SRC(pi);
        conn_state->d_ip = PI_IP6DST(pi);
    }else {
        ips.s6_addr32[0] = pi->ip4->ip_src;
        ipd.s6_addr32[0] = pi->ip4->ip_dst;
        conn_state->s_ip = ips;
        conn_state->d_ip = ipd;
    }

    conn_state->s_port = pi->s_port;
    conn_state->d_port = pi->d_port;
    pi->cxid = cxtrackerid;

    
    //uint8_t *ether_dst = (uint8_t*)malloc(6);
    conn_state->ether_dst[0] = pi->eth_hdr->ether_dst[0];        /* destination MAC */
    conn_state->ether_dst[1] = pi->eth_hdr->ether_dst[1];        /* destination MAC */
    conn_state->ether_dst[2] = pi->eth_hdr->ether_dst[2];        /* destination MAC */
    conn_state->ether_dst[3] = pi->eth_hdr->ether_dst[3];        /* destination MAC */
    conn_state->ether_dst[4] = pi->eth_hdr->ether_dst[4];        /* destination MAC */
    conn_state->ether_dst[5] = pi->eth_hdr->ether_dst[5];        /* destination MAC */ 
    
    //uint8_t *ether_src = (uint8_t*)malloc(6);
    
    conn_state->ether_src[0] = pi->eth_hdr->ether_src[0];        /* src MAC */
    conn_state->ether_src[1] = pi->eth_hdr->ether_src[1];        /* src MAC */
    conn_state->ether_src[2] = pi->eth_hdr->ether_src[2];        /* src MAC */
    conn_state->ether_src[3] = pi->eth_hdr->ether_src[3];        /* src MAC */
    conn_state->ether_src[4] = pi->eth_hdr->ether_src[4];        /* src MAC */
    conn_state->ether_src[5] = pi->eth_hdr->ether_src[5];        /* src MAC */

    
    conn_state->reversed = 0;

    //showConnState(conn_state);

    return conn_state;
 

}
//+++

//+++

/* freshly smelling connection :d */
actionState *action_cxt_new(packetinfo *pi)
{


    actionState *action_state;
    
    action_state = (actionState *) calloc(1, sizeof(actionState));
    assert(action_state);
    action_state->cxid = cxtrackerid;
//+++
    //connac_notify_flow_created();
//+++
    action_state->af = pi->af;
    if(pi->tcph) action_state->s_tcpFlags = pi->tcph->t_flags;
    //cxt->s_tcpFlags |= (pi->tcph ? pi->tcph->t_flags : 0x00);//why??
    //cxt->d_tcpFlags = 0x00;
    action_state->s_total_bytes = pi->packet_bytes;
    action_state->s_total_pkts = 1;
    action_state->start_time = pi->pheader->ts.tv_sec;
    action_state->last_pkt_time = pi->pheader->ts.tv_sec; 
   
    action_state->proto = pi->proto;
    action_state->hw_proto = ntohs(pi->eth_type);

    action_state->check = 0x00;
    action_state->c_asset = NULL;
    action_state->s_asset = NULL;
    action_state->reversed = 0;

   
    //showActionState(action_state);
     
    
    return action_state;
}

//+++

/* freshly smelling connection :d */
connection *cxt_new(packetinfo *pi)
{

    struct in6_addr ips;
    struct in6_addr ipd;
    connection *cxt;
    cxtrackerid++;
    cxt = (connection *) calloc(1, sizeof(connection));
    assert(cxt);
    cxt->cxid = cxtrackerid;
//+++
    connac_notify_flow_created();
//+++
    cxt->af = pi->af;
    if(pi->tcph) cxt->s_tcpFlags = pi->tcph->t_flags;
    //cxt->s_tcpFlags |= (pi->tcph ? pi->tcph->t_flags : 0x00);//why??
    //cxt->d_tcpFlags = 0x00;
    cxt->s_total_bytes = pi->packet_bytes;
    cxt->s_total_pkts = 1;
    cxt->start_time = pi->pheader->ts.tv_sec;
    cxt->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi-> af== AF_INET6){
        cxt->s_ip = PI_IP6SRC(pi);
        cxt->d_ip = PI_IP6DST(pi);
    }else {
        ips.s6_addr32[0] = pi->ip4->ip_src;
        ipd.s6_addr32[0] = pi->ip4->ip_dst;
        cxt->s_ip = ips;
        cxt->d_ip = ipd;
    }

    cxt->s_port = pi->s_port;
    cxt->d_port = pi->d_port;
    cxt->proto = pi->proto;
    cxt->hw_proto = ntohs(pi->eth_type);

    cxt->check = 0x00;
    cxt->c_asset = NULL;
    cxt->s_asset = NULL;
    cxt->reversed = 0;

    //showConnection(cxt);
    showAllCxid();

    return cxt;
}

//+++
int action_tracking(packetinfo *pi)
{
    //static char ip_addr_s[INET6_ADDRSTRLEN];
    //static char ip_addr_d[INET6_ADDRSTRLEN];
    action_cx_track(pi);

    return 0;
}
//+++

//+++
int conn_tracking(packetinfo *pi)
{
    //static char ip_addr_s[INET6_ADDRSTRLEN];
    //static char ip_addr_d[INET6_ADDRSTRLEN];
    conn_cx_track(pi);

    return 0;
}
//+++


int connection_tracking(packetinfo *pi)
{
    static char ip_addr_s[INET6_ADDRSTRLEN];
    static char ip_addr_d[INET6_ADDRSTRLEN];
    cx_track(pi);
    
    if(config.cflags & CONFIG_CONNECT){
	//log_connection(pi->cxt, CX_EXCESSIVE);
    }
    return 0;
}

//+++
int action_update_client(actionState *action_state, packetinfo *pi)
{
    action_state->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi->tcph) action_state->s_tcpFlags |= pi->tcph->t_flags;
    action_state->s_total_bytes += pi->packet_bytes;
    action_state->s_total_pkts += 1;

    pi->action_state = action_state;
    if(!action_state->c_asset)
        action_state->c_asset = pi->asset; // connection client asset
    if (action_state->s_total_bytes > MAX_BYTE_CHECK
        || action_state->s_total_pkts > MAX_PKT_CHECK) {
        return 0;   // Dont Check!
    }
    //printf("action------SC_CLIENT ----------------------------\n");
    //showActionState(action_state);
    return SC_CLIENT;
}
//+++

int cxt_update_client(connection *cxt, packetinfo *pi)
{
    cxt->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi->tcph) cxt->s_tcpFlags |= pi->tcph->t_flags;
    cxt->s_total_bytes += pi->packet_bytes;
    cxt->s_total_pkts += 1;

    //pi->cxt = cxt;
    pi->sc = SC_CLIENT;
    if(!cxt->c_asset)
        cxt->c_asset = pi->asset; // connection client asset
    if (cxt->s_total_bytes > MAX_BYTE_CHECK
        || cxt->s_total_pkts > MAX_PKT_CHECK) {
        return 0;   // Dont Check!
    }
    //printf("connection -----SC_CLIENT ----------------------------\n");
    //showConnection(cxt);
    return SC_CLIENT;
}

//+++
int action_update_server(actionState *action_state, packetinfo *pi)
{
    action_state->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi->tcph) action_state->d_tcpFlags |= pi->tcph->t_flags;
    action_state->d_total_bytes += pi->packet_bytes;
    action_state->d_total_pkts += 1;

    pi->action_state = action_state;
    if(!action_state->s_asset)
        action_state->s_asset = pi->asset; // server asset
    if (action_state->d_total_bytes > MAX_BYTE_CHECK
        || action_state->d_total_pkts > MAX_PKT_CHECK) {
        return 0;   // Dont check!
    }
    //printf("action------SC_SERVER ----------------------------\n");
    //showActionState(action_state);
    return SC_SERVER;

}
//+++


int cxt_update_server(connection *cxt, packetinfo *pi)
{
    cxt->last_pkt_time = pi->pheader->ts.tv_sec;

    if(pi->tcph) cxt->d_tcpFlags |= pi->tcph->t_flags;
    cxt->d_total_bytes += pi->packet_bytes;
    cxt->d_total_pkts += 1;

    //pi->cxt = cxt;
    pi->sc = SC_SERVER;
    if(!cxt->s_asset)
        cxt->s_asset = pi->asset; // server asset
    if (cxt->d_total_bytes > MAX_BYTE_CHECK
        || cxt->d_total_pkts > MAX_PKT_CHECK) {
        return 0;   // Dont check!
    }
    //printf("connection-------SC_SERVER ----------------------------\n");
    //showConnection(cxt);
    return SC_SERVER;

}




//+++
int conn_cx_track(packetinfo *pi){

  
    struct in6_addr *ip_src;
    struct in6_addr *ip_dst;
    struct in6_addr ips;
    struct in6_addr ipd;
    uint16_t src_port = pi->s_port;
    uint16_t dst_port = pi->d_port;
       
    connState *conn_state = NULL;
    connState *head = NULL;
    uint32_t hash;

    int af = pi->af;
    if(af== AF_INET6){
        ip_src = &PI_IP6SRC(pi);
        ip_dst = &PI_IP6DST(pi);
    }else {
        // ugly hack :(
        // the way we do ip4/6 is DIRTY
        ips.s6_addr32[0] = pi->ip4->ip_src;
        ipd.s6_addr32[0] = pi->ip4->ip_dst;
        ip_src = &ips;
        ip_dst = &ipd;
    }

    // find the right connection bucket
    if (af == AF_INET) {
        hash = CXT_HASH4(IP4ADDR(ip_src),IP4ADDR(ip_dst),src_port,dst_port,pi->proto);
    } else if (af == AF_INET6) {
        hash = CXT_HASH6(ip_src,ip_dst,src_port,dst_port,pi->proto);
    }
    pi->hash= hash;
    conn_state = conn_bucket[hash];
    head = conn_state;

    // search through the bucket
    // 
    uint64_t cxid = 0;
    while (conn_state != NULL) {
        // Two-way compare of given connection against connection table
        if (af == AF_INET) {
            if (CMP_CXT4(conn_state,IP4ADDR(ip_src),src_port,IP4ADDR(ip_dst),dst_port)){
                // Client sends first packet (TCP/SYN - UDP?) hence this is a client
		cxid = conn_state ->cxid;
                pi->sc = SC_CLIENT;
               //printf("this is client find the conn state\n");
            } else if (CMP_CXT4(conn_state,IP4ADDR(ip_dst),dst_port,IP4ADDR(ip_src),src_port)) {
                // This is a server (Maybe not when we start up but in the long run)
                cxid = conn_state ->cxid;
		pi->sc = SC_SERVER;
		//printf("this is server find the conn state\n");
            }
        } else if (af == AF_INET6) {
            if (CMP_CXT6(conn_state,ip_src,src_port,ip_dst,dst_port)){
                cxid = conn_state ->cxid;
		pi->sc = SC_CLIENT;
            } else if (CMP_CXT6(conn_state,ip_dst,dst_port,ip_src,src_port)){
                cxid = conn_state ->cxid;
		pi->sc = SC_SERVER;
            }
        }
        conn_state = conn_state->next;
    }
    pi->cxid = cxid; 
   // bucket turned upside down didn't yeild anything. new connection
    if(cxid == 0)
    {
	conn_state = conn_cxt_new(pi);
        //log_connection(conn_state, CX_NEW);

    	/* * New connections are pushed on to the head of bucket[s_hash] */
    	conn_state->next = head;
   	 if (head != NULL) 
	{
        	// are we doubly linked?
        	head->prev = conn_state;
    	}
    	conn_bucket[hash] = conn_state;
    	pi->conn_state = conn_state;
    }
    /* * Return value should be 1, telling to do client service fingerprinting */
    return 1;
}
//+++



/* return value: client or server?
 *** USED TO BE: 0 = dont check, 1 = client, 2 = server
 * now returns 0, SC_CLIENT(=1), SC_SERVER(=2)
 */

int cx_track(packetinfo *pi) {

   
    struct in6_addr *ip_src;
    struct in6_addr *ip_dst;
    struct in6_addr ips;
    struct in6_addr ipd;
    uint16_t src_port = pi->s_port;
    uint16_t dst_port = pi->d_port;
    int af = pi->af;
    connection *cxt = NULL;
    connection *head = NULL;
    uint32_t hash;


    if(af== AF_INET6){
        ip_src = &PI_IP6SRC(pi);
        ip_dst = &PI_IP6DST(pi);
    }else {
        // ugly hack :(
        // the way we do ip4/6 is DIRTY
        ips.s6_addr32[0] = pi->ip4->ip_src;
        ipd.s6_addr32[0] = pi->ip4->ip_dst;
        ip_src = &ips;
        ip_dst = &ipd;
    }

    // find the right connection bucket
    if (af == AF_INET) {
        hash = CXT_HASH4(IP4ADDR(ip_src),IP4ADDR(ip_dst),src_port,dst_port,pi->proto);
    } else if (af == AF_INET6) {
        hash = CXT_HASH6(ip_src,ip_dst,src_port,dst_port,pi->proto);
    }
    cxt = bucket[hash];
    head = cxt;

    // search through the bucket
    while (cxt != NULL) {
        // Two-way compare of given connection against connection table
        if (af == AF_INET) {
            if (CMP_CXT4(cxt,IP4ADDR(ip_src),src_port,IP4ADDR(ip_dst),dst_port)){
                // Client sends first packet (TCP/SYN - UDP?) hence this is a client
		//printf("connection---find the number SC-CLIENT\n");
                return cxt_update_client(cxt, pi);
            } else if (CMP_CXT4(cxt,IP4ADDR(ip_dst),dst_port,IP4ADDR(ip_src),src_port)) {
                // This is a server (Maybe not when we start up but in the long run)
		//printf("connection---find the number SC-SERVER\n");
                return cxt_update_server(cxt, pi);
            }
        } else if (af == AF_INET6) {
            if (CMP_CXT6(cxt,ip_src,src_port,ip_dst,dst_port)){
                return cxt_update_client(cxt, pi);
            } else if (CMP_CXT6(cxt,ip_dst,dst_port,ip_src,src_port)){
                return cxt_update_server(cxt, pi);
            }
        }
        cxt = cxt->next;
    }
    // bucket turned upside down didn't yeild anything. new connection
    cxt = cxt_new(pi);
    log_connection(cxt, CX_NEW);

    /* * New connections are pushed on to the head of bucket[s_hash] */
    cxt->next = head;
    if (head != NULL) {
        // are we doubly linked?
        head->prev = cxt;
    }
    bucket[hash] = cxt;
    //pi->cxt = cxt;
    printf("----------------------endcx_track---------------------------\n");
    /* * Return value should be 1, telling to do client service fingerprinting */
    return 1;
}


int action_cx_track(packetinfo *pi) {
    
    int af = pi->af;
    actionState *action_state = NULL;
    actionState *head = NULL;
    
    uint32_t hash;
    uint64_t cxid;

    hash = pi->hash;
    
    action_state = action_bucket[hash];
    head = action_state;

    // search through the bucket
    while (action_state != NULL) {
        // Two-way compare of given connection against connection table
        cxid = action_state->cxid;
        if (af == AF_INET) {
	    /*printf("action-----action_state cxid: %lu\n",cxid);
            printf("action-----packet cxid: %lu\n",pi->cxid);
            if(pi->sc ==  SC_SERVER){
		printf("action----packet is from SC_SERVER\n");
	    }
	    else{
		printf("action----packet is from SC_CLIENT\n");

		}
            */
            if ((pi->sc == SC_CLIENT) &(pi->cxid == cxid)){
                //printf("action---find the number SC-CLIENT, cxid: %lu\n",pi->cxid);
                // Client sends first packet (TCP/SYN - UDP?) hence this is a client
                return action_update_client(action_state, pi);
            } else if ((pi->sc == SC_SERVER)&(pi->cxid == cxid)) {
                // This is a server (Maybe not when we start up but in the long run)
		//printf("action---find the number SC-SERVER, cxid: %lu\n",pi->cxid);
                return action_update_server(action_state, pi);
            }
        } else if (af == AF_INET6) {
            if ((pi->sc == SC_CLIENT) &(pi->cxid == cxid)){
                return action_update_client(action_state, pi);
            } else if ((pi->sc = SC_SERVER)&(pi->cxid == cxid)){
                return action_update_server(action_state, pi);
            }
        }
        action_state = action_state->next;
    }
    // bucket turned upside down didn't yeild anything. new connection
    action_state = action_cxt_new(pi);
    //log_connection(cxt, CX_NEW);

    /* * New connections are pushed on to the head of bucket[s_hash] */
    action_state->next = head;
    if (head != NULL) {
        // are we doubly linked?
        head->prev = action_state;
    }
    action_bucket[hash] = action_state;
    pi->action_state = action_state;

    /* * Return value should be 1, telling to do client service fingerprinting */
    return 1;
}

void reverse_pi_cxt(packetinfo *pi)
{
    uint8_t tmpFlags;
    uint64_t tmp_pkts;
    uint64_t tmp_bytes;
    struct in6_addr tmp_ip;
    uint16_t tmp_port;
    connection *cxt;

    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!reverse pi cxt\n");

    //cxt = pi->cxt;

    /* First we chang the cxt */
    /* cp src to tmp */
    tmpFlags = cxt->s_tcpFlags;
    tmp_pkts = cxt->s_total_pkts;
    tmp_bytes = cxt->s_total_bytes;
    tmp_ip = cxt->s_ip;
    tmp_port = cxt->s_port;

    /* cp dst to src */
    cxt->s_tcpFlags = cxt->d_tcpFlags;
    cxt->s_total_pkts = cxt->d_total_pkts;
    cxt->s_total_bytes = cxt->d_total_bytes;
    cxt->s_ip = cxt->d_ip;
    cxt->s_port = cxt->d_port;

    /* cp tmp to dst */
    cxt->d_tcpFlags = tmpFlags; 
    cxt->d_total_pkts = tmp_pkts;
    cxt->d_total_bytes = tmp_bytes;
    cxt->d_ip = tmp_ip;
    cxt->d_port = tmp_port;

    /* Not taking any chances :P */
    cxt->c_asset = cxt->s_asset = NULL;
    cxt->check = 0x00;

    /* Then we change pi */
    if (pi->sc == SC_CLIENT)
       pi->sc = SC_SERVER;
    else
       pi->sc = SC_CLIENT;
}


void reverse_pi_conn_action(packetinfo *pi)
{
    uint8_t tmpFlags;
    uint64_t tmp_pkts;
    uint64_t tmp_bytes;
    struct in6_addr tmp_ip;
    uint16_t tmp_port;
    actionState *action_state;
    connState *conn_state;

    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!reverse pi cxt\n");

    action_state = pi->action_state;
    conn_state = pi->conn_state;
    

    /* First we chang the cxt */
    /* cp src to tmp */
    tmpFlags = action_state->s_tcpFlags;
    tmp_pkts = action_state->s_total_pkts;
    tmp_bytes = action_state->s_total_bytes;
    tmp_ip = conn_state->s_ip;
    tmp_port = conn_state->s_port;

    /* cp dst to src */
    action_state->s_tcpFlags = action_state->d_tcpFlags;
    action_state->s_total_pkts = action_state->d_total_pkts;
    action_state->s_total_bytes = action_state->d_total_bytes;
    conn_state->s_ip = conn_state->d_ip;
    conn_state->s_port = conn_state->d_port;

    /* cp tmp to dst */
    action_state->d_tcpFlags = tmpFlags; 
    action_state->d_total_pkts = tmp_pkts;
    action_state->d_total_bytes = tmp_bytes;
    conn_state->d_ip = tmp_ip;
    conn_state->d_port = tmp_port;

    /* Not taking any chances :P */
    action_state->c_asset = action_state->s_asset = NULL;
    action_state->check = 0x00;

    /* Then we change pi */
    if (pi->sc == SC_CLIENT)
       pi->sc = SC_SERVER;
    else
       pi->sc = SC_CLIENT;
}


/*
 This sub marks sessions as ENDED on different criterias:

 XXX: May be the fugliest code in PRADS :-(
*/

void end_sessions()
{
   printf("-------------------------------end sessions--------------------------------------\n");

    connection *cxt;
    int iter;
    int cxstatus = CX_NONE;
    int ended, expired = 0;
    uint32_t curcxt = 0;
    time_t check_time = time(NULL);

    log_rotate(check_time);
    for (iter = 0; iter < BUCKET_SIZE; iter++) {
        cxt = bucket[iter];
        while (cxt != NULL) {
            curcxt++;
            /* TCP */
            if (cxt->proto == IP_PROTO_TCP) {
                /* * FIN from both sides */
                if (cxt->s_tcpFlags & TF_FIN && cxt->d_tcpFlags & TF_FIN
                    && (check_time - cxt->last_pkt_time) > 5) {
                    cxstatus = CX_ENDED;
                } /* * RST from either side */
                else if ((cxt->s_tcpFlags & TF_RST
                          || cxt->d_tcpFlags & TF_RST)
                          && (check_time - cxt->last_pkt_time) > 5) {
                    cxstatus = CX_ENDED;
                }
                else if ((check_time - cxt->last_pkt_time) > TCP_TIMEOUT) {
                    cxstatus = CX_EXPIRE;
                }
            }
            /* UDP */
            else if (cxt->proto == IP_PROTO_UDP
                     && (check_time - cxt->last_pkt_time) > 60) {
                cxstatus = CX_EXPIRE;
            }
            /* ICMP */
            else if (cxt->proto == IP_PROTO_ICMP
                     || cxt->proto == IP6_PROTO_ICMP) {
                if ((check_time - cxt->last_pkt_time) > 60) {
                    cxstatus = CX_EXPIRE;
                }
            }
            /* All Other protocols */
            else if ((check_time - cxt->last_pkt_time) > TCP_TIMEOUT) {
                cxstatus = CX_EXPIRE;
            }

            if (cxstatus == CX_ENDED || cxstatus == CX_EXPIRE) {
                /* remove from the hash */
                if (cxt->prev)
                    cxt->prev->next = cxt->next;
                if (cxt->next)
                    cxt->next->prev = cxt->prev;
                connection *tmp = cxt;

                log_connection(cxt, cxstatus);
                cxstatus = CX_NONE;

                cxt = cxt->prev;

                del_connection(tmp, &bucket[iter]);
                if (cxt == NULL) {
                    bucket[iter] = NULL;
                }
            } else {
                cxt = cxt->prev;
            }
        } // end while cxt
    } // end for buckets
}


void end_connac_sessions()
{
   printf("-------------------------------end connac sessions--------------------------------------\n");

    connState *conn_state;
    actionState *action_state;
    int iter;
    int cxstatus = CX_NONE;
    int ended, expired = 0;
    uint32_t curcxt = 0;
    time_t check_time = time(NULL);

    log_rotate(check_time);
    for (iter = 0; iter < BUCKET_SIZE; iter++) {
        conn_state = conn_bucket[iter];
        action_state = action_bucket[iter];

        while (action_state != NULL) {
            curcxt++;
            /* TCP */
            if (action_state->proto == IP_PROTO_TCP) {
                /* * FIN from both sides */
                if (action_state->s_tcpFlags & TF_FIN && action_state->d_tcpFlags & TF_FIN
                    && (check_time - action_state->last_pkt_time) > 5) {
                    cxstatus = CX_ENDED;
                } /* * RST from either side */
                else if ((action_state->s_tcpFlags & TF_RST
                          || action_state->d_tcpFlags & TF_RST)
                          && (check_time - action_state->last_pkt_time) > 5) {
                    cxstatus = CX_ENDED;
                }
                else if ((check_time - action_state->last_pkt_time) > TCP_TIMEOUT) {
                    cxstatus = CX_EXPIRE;
                }
            }
            /* UDP */
            else if (action_state->proto == IP_PROTO_UDP
                     && (check_time - action_state->last_pkt_time) > 60) {
                cxstatus = CX_EXPIRE;
            }
            /* ICMP */
            else if (action_state->proto == IP_PROTO_ICMP
                     || action_state->proto == IP6_PROTO_ICMP) {
                if ((check_time - action_state->last_pkt_time) > 60) {
                    cxstatus = CX_EXPIRE;
                }
            }
            /* All Other protocols */
            else if ((check_time - action_state->last_pkt_time) > TCP_TIMEOUT) {
                cxstatus = CX_EXPIRE;
            }

            if (cxstatus == CX_ENDED || cxstatus == CX_EXPIRE) {
                 while (conn_state != NULL)
        	{ 
		if(conn_state->cxid == action_state->cxid){
			break;
		}            	    
			conn_state = conn_state->next;	
        	}   
		/* remove from the hash */
                if (conn_state->prev)
                    conn_state->prev->next = conn_state->next;
                if (conn_state->next)
                    conn_state->next->prev = conn_state->prev;
                connState *conn_tmp = conn_state;

                conn_state = conn_state->prev;

                del_conn_state(conn_tmp, &conn_bucket[iter]);
                if (conn_state == NULL) {
                    conn_bucket[iter] = NULL;
                }
                
                /* remove from the hash */
                if (action_state->prev)
                    action_state->prev->next = action_state->next;
                if (action_state->next)
                    action_state->next->prev = action_state->prev;
                actionState *tmp = action_state;

                
                cxstatus = CX_NONE;

                action_state = action_state->prev;

                del_action_state(tmp, &action_bucket[iter]);
                if (action_state == NULL) {
                    action_bucket[iter] = NULL;
                }
            } else {
                action_state = action_state->prev;
            }
        } // end while cxt
    } // end for buckets
}


void log_connection_all()
{
    int i;
    connection *cxt;
    if(! (config.cflags & CONFIG_CXWRITE))
        return;
    for(i = 0; i < BUCKET_SIZE; i++) {
        cxt = bucket[i];
        while(cxt) {
            log_connection(cxt, CX_HUMAN);
            cxt = cxt->next;
        }
    }
}



void del_conn_state(connState * conn_state, connState ** bucket_ptr)
{
    connState *prev = conn_state->prev;       /* OLDER connections */
    connState *next = conn_state->next;       /* NEWER connections */

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

void del_action_state(actionState * action_state, actionState ** bucket_ptr)
{
    actionState *prev = action_state->prev;       /* OLDER connections */
    actionState *next = action_state->next;       /* NEWER connections */

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


void del_connection(connection * cxt, connection ** bucket_ptr)
{
    connection *prev = cxt->prev;       /* OLDER connections */
    connection *next = cxt->next;       /* NEWER connections */

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
    free(cxt);
    cxt = NULL;
}

void end_all_sessions()
{
    connection *cxt;
    int cxkey;
    FILE *cxtFile = NULL;

    log_rotate(time(NULL));
    for (cxkey = 0; cxkey < BUCKET_SIZE; cxkey++) {
        cxt = bucket[cxkey];
        while (cxt != NULL) {
            connection *tmp = cxt;

            log_connection(cxt, CX_ENDED);
            cxt = cxt->next;
            del_connection(tmp, &bucket[cxkey]);
            if (cxt == NULL) {
                bucket[cxkey] = NULL;
            }
        }
    }
    if (cxtFile != NULL) {
        fclose(cxtFile);
    }
}

void cxt_log_buckets(int dummy)
{
    connection *cxt = NULL;
    FILE *logfile = NULL;
    int i;
    int len;

    logfile = fopen("/tmp/prads-buckets.log", "w");
    if (!logfile)
        return;

    dlog("Recieved SIGUSR1 - Dumping bucketlist to logfile\n");
    for (i = 0; i < BUCKET_SIZE; i++) {
        len = 0;
        for (cxt = bucket[i]; cxt; cxt = cxt->next)
            len++;
        if (len > 0)
            fprintf(logfile, "%d in bucket[%5d]\n", len, i);
    }

    fflush(logfile);
    fclose(logfile);
}



/* vector comparisons to speed up cx tracking.
 * meaning, compare source:port and dest:port at the same time.
 *
 * about vectors and potential improvements:
 * * all 64bit machines have at least SSE2 instructions * *BUT* there is no guarantee we won't loose time on
 * copying the vectors around.
 * ... indeed, a quick objdump shows us that
 * there is a shitton of mov instructions to align the addresses.
 *
 * Needs support to give improvements: 
 * the addresses should already be aligned as a 128-bit word
 * in the connection tracking bucket.
 *
 * note, we can employ the same technique for ipv6 addresses, but
 * one address at a time.
 */
#ifdef VECTOR_CXTRACKER
// vector fill: srcprt,dstprt,srcip,dstip = 96 bytes. rest is 0
#define VEC_FILL(vec, _ipsrc,_ipdst,_portsrc,_portdst) do {\
    vec.s[0] = (_portsrc); \
    vec.s[1] = (_portdst); \
    vec.w[1] = (_ipsrc); \
    vec.w[2] = (_ipdst); \
    vec.w[3] = 0; \
} while (0)

inline void cx_track_simd_ipv4(packetinfo *pi)
{
    printf("use cx_track_simd_ipv4\n");
    connection *cxt = NULL;
    connection *head = NULL;
    uint32_t hash;

    // add to packetinfo ? dont through int32 around :)
    hash = make_hash(pi);
    cxt = bucket[hash];
    head = cxt;

    ip6v incoming;
    ip6v compare;
    VEC_FILL(incoming,
        pi->ip_src.__u6_addr.__u6_addr32[0],
        pi->ip_dst.__u6_addr.__u6_addr32[0],
        pi->s_port,
        pi->d_port);
    while (cxt != NULL) {
        VEC_FILL(compare,
        cxt->s_ip.__u6_addr.__u6_addr32[0],
        cxt->d_ip.__u6_addr.__u6_addr32[0],
        cxt->s_port,
        cxt->d_port);

        // single-instruction compare -msse2
        compare.v = __builtin_ia32_pcmpeqd128(incoming.v,compare.v);
        // same thing, really. c == v iff c ^ v == 0
        //compare.v = compare.v ^ incoming.v;

        // 64-bit compare reduce
        if(!(compare.i[0] & compare.i[1])){
            //ok
            dlog("[*] Updating src connection: %lu\n",cxt->cxid);
            cxt_update_src(cxt,pi);
            return;
        }

        // compare the other direction
        VEC_FILL(compare,
        cxt->d_ip.__u6_addr.__u6_addr32[0],
        cxt->s_ip.__u6_addr.__u6_addr32[0],
        cxt->d_port,
        cxt->s_port);

        compare.v = __builtin_ia32_pcmpeqd128(incoming.v,compare.v);
        if(!(compare.i[0] & compare.i[1])){
            dlog("[*] Updating dst connection: %lu\n",cxt->cxid);
            cxt_update_dst(cxt,pi);
            return;
        }
        cxt = cxt->next;
    }
    if (cxt == NULL) {
        cxt = (connection *) connection_alloc();
        //cxt = (connection *) calloc(1, sizeof(connection));
        if (head != NULL) {
            head->prev = cxt;
        }
        cxt = cxt_new(pi);
        dlog("[*] New connection: %lu\n",cxt->cxid);
        cxt->next = head;
        bucket[hash] = cxt;
        return;
    }
    printf("[*] Error in session tracking...\n");
    exit (1);
}

#endif
