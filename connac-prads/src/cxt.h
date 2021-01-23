#ifndef CXT_H
#define CXT_H

/* the connection hash does not care whether you pass src:sp,dst:dp
 * or dst:dp,src:sp, it returns the same hashvalue! */
#define CXT_HASH4(src,dst,sp,dp,pr) \
   (( src + dst + sp + dp + pr) % BUCKET_SIZE)

#define CXT_HASH6(src,dst,sp,dp,pr) \
 (( \
  (src)->s6_addr32[0] + (src)->s6_addr32[1] + \
  (src)->s6_addr32[2] + (src)->s6_addr32[3] + \
  (dst)->s6_addr32[0] + (dst)->s6_addr32[1] + \
  (dst)->s6_addr32[2] + (dst)->s6_addr32[3] + \
  sp + dp + pr ) % BUCKET_SIZE)

enum { CX_NONE, CX_HUMAN, CX_NEW, CX_ENDED, CX_EXPIRE, CX_EXCESSIVE };
void end_sessions();
void end_connac_sessions();

void cxt_init();

int action_cx_track(packetinfo *pi);
int conn_cx_track(packetinfo *pi);
int cx_track(packetinfo *pi);

/*struct in6_addr *ip_src, uint16_t src_port,
             struct in6_addr *ip_dst, uint16_t dst_port, uint8_t ip_proto,
             uint16_t p_bytes, uint8_t tcpflags, time_t tstamp, int af);
*/
void del_connection(connection *, connection **);
void del_conn_state(connState * conn_state, connState ** bucket_ptr);
void del_action_state(actionState * action_state, actionState ** bucket_ptr);


void cxt_write(connection *, FILE *fd, int human);
void cxt_write_all();
void cxt_log_buckets(int dummy);

int conn_tracking(packetinfo *pi);
int action_tracking(packetinfo *pi);
int connection_tracking(packetinfo *pi);

void reverse_pi_cxt(packetinfo *pi);
void reverse_pi_conn_action(packetinfo *pi);

void showAllCxid();
void showAllState();

#endif // CXT_H
